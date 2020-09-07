#define SDL_MAIN_HANDLED
#include <SDL2/SDL_vulkan.h>
#include <stdbool.h>
#include "VK2D/VK2D.h"
#include "VK2D/Validation.h"
#include <stdio.h>
#include <time.h>

/************************ Constants ************************/
const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;

const VK2DVertexColour SAMPLE_TRIANGLE[] = {
		{{125, 0.0, +0.0}, {1.0, 1.0, 0.5, 1}},
		{{250, 200, +0.0}, {1.0, 0.5, 1.0, 1}},
		{{0.0, 200, +0.0}, {0.5, 1.0, 1.0, 1}}
};
const uint32_t VERTICES = 3;

int main(int argc, const char *argv[]) {
	SDL_Window *window = SDL_CreateWindow("VK2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN);
	SDL_Event e;
	bool quit = false;
	bool drawnToTex = false;

	if (window == NULL)
		return -1;

	// For testing purposes, we just try to get the renderer to use the best possible settings
	VK2DRendererConfig config = {msaa_32x, sm_TripleBuffer, ft_Nearest};
	vec4 clear = {0.0, 0.5, 1.0, 1.0};
	int32_t error = vk2dRendererInit(window, config);

	if (error < 0)
		return -1;

	VK2DCamera cam = {0, 0, WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f, 1, 0};
	vk2dRendererSetCamera(cam);

	// Load test assets
	VK2DPolygon testPoly = vk2dPolygonShapeCreateRaw(vk2dRendererGetDevice(), (void *) SAMPLE_TRIANGLE, VERTICES);
	VK2DImage testImage = vk2dImageLoad(vk2dRendererGetDevice(), "assets/caveguy.png");
	VK2DTexture testTexture = vk2dTextureLoad(testImage, 0, 0, 16, 16);
	VK2DTexture drawTex = vk2dTextureCreate(vk2dRendererGetDevice(), 320, 240);

	// Delta and fps
	double lastTime = SDL_GetPerformanceCounter();
	double secondCounter = SDL_GetPerformanceCounter();
	double frameCounter = 0;

	// Testing values for fanciness
	float rot = 0;
	float scaleRot = 0;
	float xScale = 0;
	float yScale = 0;
	float camSpeed = 5;
	float camRotSpeed = 0.1;
	float camZoomSpeed = 0.15;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_D) {
				cam.x += camSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_A) {
				cam.x -= camSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_S) {
				cam.y += camSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_W) {
				cam.y -= camSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Q) {
				cam.rot += camRotSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_E) {
				cam.rot -= camRotSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_I) {
				cam.zoom += camZoomSpeed;
				vk2dRendererSetCamera(cam);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_O) {
				cam.zoom -= camZoomSpeed;
				vk2dRendererSetCamera(cam);
			}
			else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_8) {
				config.msaa = msaa_8x;
				vk2dRendererSetConfig(config);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_4) {
				config.msaa = msaa_4x;
				vk2dRendererSetConfig(config);
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_1) {
				config.msaa = msaa_1x;
				vk2dRendererSetConfig(config);
			}
		}


		// Fancy tweening and extremely basic delta timing
		double delta = ((double)SDL_GetPerformanceCounter() - lastTime) / (double)SDL_GetPerformanceFrequency();
		lastTime = SDL_GetPerformanceCounter();
		rot += VK2D_PI * 1.5 * delta;
		scaleRot += VK2D_PI * 3.25 * delta;
		xScale = cos(scaleRot) * 0.25;
		yScale = sin(scaleRot) * 0.25;

		vk2dRendererStartFrame(clear);

		if (!drawnToTex) {
			vk2dRendererSetTarget(drawTex);
			vk2dRendererClear();
			vk2dRendererDrawPolygon(testPoly, 0, 0, true, 1, 1, 1, 0, 0, 0);
			vk2dRendererSetTarget(VK2D_TARGET_SCREEN);
			drawnToTex = true;
		}
		vk2dDrawPolygon(testPoly, 0, 0);
		//vk2dRendererDrawTexture(drawTex, 0, 0, 1, 1, 0, 0, 0);
		vk2dRendererDrawTexture(testTexture, 80, 80, 4 + 3 * xScale, 4 + 3 * yScale, rot, 8, 8);
		vk2dRendererEndFrame();

		// Framerate is printed once per second
		frameCounter += 1;
		if (SDL_GetPerformanceCounter() - secondCounter >= SDL_GetPerformanceFrequency()) {
			vk2dLogMessage("FPS: %f", frameCounter / ((SDL_GetPerformanceCounter() - secondCounter) / (double)SDL_GetPerformanceFrequency()));
			secondCounter = SDL_GetPerformanceCounter();
			frameCounter = 0;
		}
	}

	vk2dRendererWait();
	vk2dTextureFree(testTexture);
	vk2dImageFree(testImage);
	vk2dPolygonFree(testPoly);
	vk2dTextureFree(drawTex);
	vk2dRendererQuit();
	SDL_DestroyWindow(window);
	return 0;
}
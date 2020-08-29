/// \file Constants.c
/// \author Paolo Mazzon
#include <vulkan/vulkan.h>
#include "VK2D/Structs.h"

const int32_t VK2D_DEVICE_BEST_FIT = -1;

const VkApplicationInfo VK2D_DEFAULT_CONFIG = {
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		VK_NULL_HANDLE,
		"VK2D",
		VK_MAKE_VERSION(1, 0, 0),
		"VK2D Renderer",
		VK_MAKE_VERSION(1, 0, 0),
		VK_MAKE_VERSION(1, 2, 0)
};

const uint32_t VK2D_DEFAULT_DESCRIPTOR_POOL_ALLOCATION = 10;

const uint32_t VK2D_DEFAULT_ARRAY_EXTENSION = 5;

const uint32_t VK2D_NO_LOCATION = UINT32_MAX;

const VK2DTexture VK2D_TARGET_SCREEN = NULL;

const vec4 VK2D_DEFAULT_COLOUR_MOD = {1, 1, 1, 1};
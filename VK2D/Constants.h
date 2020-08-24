/// \file Constants.h
/// \author Paolo Mazzon
/// \brief Defines some constants
#pragma once
#include "VK2D/Structs.h"
#include <vulkan/vulkan.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Tells vk2dPhysicalDeviceFind to use the best device it finds (basically just the first non-integrated it finds that meets criteria)
extern const int32_t VK2D_DEVICE_BEST_FIT;

/// Default configuration of this renderer
extern const VkApplicationInfo VK2D_DEFAULT_CONFIG;

/// How many sets to allocate in a pool at a time (10 should be a good amount)
extern const uint32_t VK2D_DEFAULT_DESCRIPTOR_POOL_ALLOCATION;

/// How many array slots to allocate at a time with realloc (to avoid constantly reallocating memory)
extern const uint32_t VK2D_DEFAULT_ARRAY_EXTENSION;

/// Used to specify that a variable is not present in a shader
extern const uint32_t VK2D_NO_LOCATION;

/// Draw to the screen and not a texture
extern const VK2DTexture VK2D_TARGET_SCREEN;

/// Number of command pools a device has to cycle through - You generally want this and VK2D_MAX_FRAMES_IN_FLIGHT to be the same
#define VK2D_DEVICE_COMMAND_POOLS ((uint32_t)3)

/// Maximum number of frames to be processed at once - You generally want this and VK2D_DEVICE_COMMAND_POOLS to be the same
#define VK2D_MAX_FRAMES_IN_FLIGHT 3

/// Not terribly difficult to figure out the usages of this
#define VK2D_PI 3.14159265358979323846264338327950

#ifdef __cplusplus
};
#endif
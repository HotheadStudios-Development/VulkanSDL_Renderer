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

// This is a preprocessor because variable size arrays cannot be used in structs
/// Number of command pools a device has to cycle through
#define VK2D_DEVICE_COMMAND_POOLS ((uint32_t)3)

/// Maximum number of frames to be processed at once
#define VK2D_MAX_FRAMES_IN_FLIGHT 3

#ifdef __cplusplus
};
#endif
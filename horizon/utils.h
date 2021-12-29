#pragma once
#include <vulkan/vulkan.hpp>
#include <spdlog/spdlog.h>
#define NOMINMAX

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif

// *******************************
// HANDLING A VULKAN ERROR RETURN:
// *******************************

struct errorcode
{
	VkResult	resultCode;
	std::string	meaning;
};

errorcode ErrorCodes[];

void printVkError(VkResult result, std::string prefix="");

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#pragma once

#include "dx12/stdafx.h"
#include <d3d12.h>

#include <runtime/core/log/Log.h>
#include <runtime/core/utils/Definations.h>
#include <runtime/function/rhi/vulkan/VulkanConfig.h>

namespace Horizon {

enum class RenderBackend {
    RENDER_BACKEND_NONE,
    RENDER_BACKEND_VULKAN,
    RENDER_BACKEND_DX12
};

enum CommandQueueType { GRAPHICS = 0, COMPUTE, TRANSFER };

// class CommandQueue {
// public:
//     CommandQueueType m_type;
//     u32 m_index;
// };

inline D3D12_COMMAND_LIST_TYPE ToDX12CommandQueueType(CommandQueueType type) {
    switch (type) {
    case Horizon::GRAPHICS:
        return D3D12_COMMAND_LIST_TYPE_DIRECT;
    case Horizon::COMPUTE:
        return D3D12_COMMAND_LIST_TYPE_COMPUTE;
    case Horizon::TRANSFER:
        return D3D12_COMMAND_LIST_TYPE_COPY;
    default:
        LOG_ERROR("invalid command queue type")
        return {};
    }
}

struct RenderContext {
    u32 width;
    u32 height;
    u32 swap_chain_image_count = 3;
};

enum class PipelineType { GRAPHICS = 0, COMPUTE, RAY_TRACING };

struct PipelineCreateInfo {
    PipelineType type;
};

inline VkPipelineBindPoint ToVkPipelineBindPoint(PipelineType type) {
    switch (type) {
    case Horizon::PipelineType::GRAPHICS:
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
    case Horizon::PipelineType::COMPUTE:
        return VK_PIPELINE_BIND_POINT_COMPUTE;
    case Horizon::PipelineType::RAY_TRACING:
        return VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
    default:
        LOG_ERROR("invalid pipeline type");
        return VK_PIPELINE_BIND_POINT_GRAPHICS;
    }
}

enum class DescriptorType {
    DESCRIPTOR_TYPE_UNIFORM_BUFFER = 0,
    DESCRIPTOR_TYPE_RW_BUFFER,
    DESCRIPTOR_TYPE_TEXTURE,
    DESCRIPTOR_TYPE_RW_TEXTURE
};

// using DescriptorType = u32;

enum class ShaderType {
    VERTEX_SHADER,
    PIXEL_SHADER,
    COMPUTE_SHADER,
    GEOMETRY_SHADER,
    // ray tracing related shader
};

enum ShaderStageFlags {
    SHADER_STAGE_VERTEX_SHADER = 1,
    SHADER_STAGE_PIXEL_SHADER = 2,
    SHADER_STAGE_COMPUTE_SHADER = 4,
};

enum PipelineStageFlags {
    PIPELINE_STAGE_TOP_OF_PIPE_BIT = 0x00000001,
    PIPELINE_STAGE_DRAW_INDIRECT_BIT = 0x00000002,
    PIPELINE_STAGE_VERTEX_INPUT_BIT = 0x00000004,
    PIPELINE_STAGE_VERTEX_SHADER_BIT = 0x00000008,
    PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT = 0x00000010,
    PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020,
    PIPELINE_STAGE_GEOMETRY_SHADER_BIT = 0x00000040,
    PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 0x00000080,
    PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT = 0x00000100,
    PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT = 0x00000200,
    PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400,
    PIPELINE_STAGE_COMPUTE_SHADER_BIT = 0x00000800,
    PIPELINE_STAGE_TRANSFER_BIT = 0x00001000,
    PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 0x00002000,
    PIPELINE_STAGE_HOST_BIT = 0x00004000,
    PIPELINE_STAGE_ALL_GRAPHICS_BIT = 0x00008000,
    PIPELINE_STAGE_ALL_COMMANDS_BIT = 0x00010000,
    PIPELINE_STAGE_NONE = 0,
    PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT = 0x01000000,
    PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT = 0x00040000,
    PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR = 0x02000000,
    PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR = 0x00200000,
    PIPELINE_STAGE_TASK_SHADER_BIT_NV = 0x00080000,
    PIPELINE_STAGE_MESH_SHADER_BIT_NV = 0x00100000,
    PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT = 0x00800000,
    PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00400000,
    PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV = 0x00020000,
    PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV =
        VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
    PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV =
        VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
    PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV =
        VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
    PIPELINE_STAGE_NONE_KHR = VK_PIPELINE_STAGE_NONE,
    PIPELINE_STAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

enum MemoryAccessFlags {
    ACCESS_INDIRECT_COMMAND_READ_BIT = 0x00000001,
    ACCESS_INDEX_READ_BIT = 0x00000002,
    ACCESS_VERTEX_ATTRIBUTE_READ_BIT = 0x00000004,
    ACCESS_UNIFORM_READ_BIT = 0x00000008,
    ACCESS_INPUT_ATTACHMENT_READ_BIT = 0x00000010,
    ACCESS_SHADER_READ_BIT = 0x00000020,
    ACCESS_SHADER_WRITE_BIT = 0x00000040,
    ACCESS_COLOR_ATTACHMENT_READ_BIT = 0x00000080,
    ACCESS_COLOR_ATTACHMENT_WRITE_BIT = 0x00000100,
    ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200,
    ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400,
    ACCESS_TRANSFER_READ_BIT = 0x00000800,
    ACCESS_TRANSFER_WRITE_BIT = 0x00001000,
    ACCESS_HOST_READ_BIT = 0x00002000,
    ACCESS_HOST_WRITE_BIT = 0x00004000,
    ACCESS_MEMORY_READ_BIT = 0x00008000,
    ACCESS_MEMORY_WRITE_BIT = 0x00010000,
    ACCESS_NONE = 0,
    ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT = 0x02000000,
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = 0x04000000,
    ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = 0x08000000,
    ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT = 0x00100000,
    ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = 0x00080000,
    ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR = 0x00200000,
    ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR = 0x00400000,
    ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT = 0x01000000,
    ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR = 0x00800000,
    ACCESS_COMMAND_PREPROCESS_READ_BIT_NV = 0x00020000,
    ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV = 0x00040000,
    ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV =
        VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR,
    ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV =
        VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR,
    ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV =
        VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR,
    ACCESS_NONE_KHR = VK_ACCESS_NONE,
    ACCESS_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
};

enum class TextureType {
    TEXTURE_TYPE_1D = 0,
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_3D,
};

enum class TextureFormat {
    // unsigned int
    TEXTURE_FORMAT_R8_UINT = 0,
    TEXTURE_FORMAT_RG8_UINT,
    TEXTURE_FORMAT_RGB8_UINT,
    TEXTURE_FORMAT_RGBA8_UINT,

    TEXTURE_FORMAT_R16_UINT,
    TEXTURE_FORMAT_RG16_UINT,
    TEXTURE_FORMAT_RGB16_UINT,
    TEXTURE_FORMAT_RGBA16_UINT,

    TEXTURE_FORMAT_R32_UINT,
    TEXTURE_FORMAT_RG32_UINT,
    TEXTURE_FORMAT_RGB32_UINT,
    TEXTURE_FORMAT_RGBA32_UINT,

    // normalized unsinged int
    TEXTURE_FORMAT_R8_UNORM,
    TEXTURE_FORMAT_RG8_UNORM,
    TEXTURE_FORMAT_RGB8_UNORM,
    TEXTURE_FORMAT_RGBA8_UNORM,

    TEXTURE_FORMAT_R16_UNORM,
    TEXTURE_FORMAT_RG16_UNORM,
    TEXTURE_FORMAT_RGB16_UNORM,
    TEXTURE_FORMAT_RGBA16_UNORM,

    // signed int
    TEXTURE_FORMAT_R8_SINT,
    TEXTURE_FORMAT_RG8_SINT,
    TEXTURE_FORMAT_RGB8_SINT,
    TEXTURE_FORMAT_RGBA8_SINT,

    TEXTURE_FORMAT_R16_SINT,
    TEXTURE_FORMAT_RG16_SINT,
    TEXTURE_FORMAT_RGB16_SINT,
    TEXTURE_FORMAT_RGBA16_SINT,

    TEXTURE_FORMAT_R32_SINT,
    TEXTURE_FORMAT_RG32_SINT,
    TEXTURE_FORMAT_RGB32_SINT,
    TEXTURE_FORMAT_RGBA32_SINT,

    // normalized signed int
    TEXTURE_FORMAT_R8_SNORM,
    TEXTURE_FORMAT_RG8_SNORM,
    TEXTURE_FORMAT_RGB8_SNORM,
    TEXTURE_FORMAT_RGBA8_SNORM,

    TEXTURE_FORMAT_R16_SNORM,
    TEXTURE_FORMAT_RG16_SNORM,
    TEXTURE_FORMAT_RGB16_SNORM,
    TEXTURE_FORMAT_RGBA16_SNORM,

    TEXTURE_FORMAT_R32_SNORM,
    TEXTURE_FORMAT_RG32_SNORM,
    TEXTURE_FORMAT_RGB32_SNORM,
    TEXTURE_FORMAT_RGBA32_SNORM,

    // signed float

    TEXTURE_FORMAT_R16_SFLOAT,
    TEXTURE_FORMAT_RG16_SFLOAT,
    TEXTURE_FORMAT_RGB16_SFLOAT,
    TEXTURE_FORMAT_RGBA16_SFLOAT,

    TEXTURE_FORMAT_R32_SFLOAT,
    TEXTURE_FORMAT_RG32_SFLOAT,
    TEXTURE_FORMAT_RGB32_SFLOAT,
    TEXTURE_FORMAT_RGBA32_SFLOAT,

    TEXTURE_FORMAT_D32_SFLOAT,

};

enum TextureUsage { TEXTURE_USAGE_R = 1, TEXTURE_USAGE_RW = 2 };

inline VkDescriptorType ToVkDescriptorType(DescriptorType type) noexcept {
    switch (type) {
    case DescriptorType::DESCRIPTOR_TYPE_UNIFORM_BUFFER:
        // return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    case DescriptorType::DESCRIPTOR_TYPE_RW_BUFFER:
        return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        // case DescriptorType::DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        //	return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    case DescriptorType::DESCRIPTOR_TYPE_TEXTURE:
        return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    case DescriptorType::DESCRIPTOR_TYPE_RW_TEXTURE:
        return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
    default:
        LOG_ERROR("invalid descriptor type");
        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
}

inline VkPipelineStageFlags ToVkPipelineStage(u32 flags) noexcept {
    return flags;
}

inline VkAccessFlags ToVkMemoryAccessFlags(u32 flags) noexcept { return flags; }

inline VkShaderStageFlags ToVkShaderStageFlags(u32 stage) noexcept {
    VkShaderStageFlags flags = 0;
    if (stage & SHADER_STAGE_VERTEX_SHADER) {
        flags |= VK_SHADER_STAGE_VERTEX_BIT;
    }
    if (stage & SHADER_STAGE_PIXEL_SHADER) {
        flags |= VK_SHADER_STAGE_FRAGMENT_BIT;
    }
    if (stage & SHADER_STAGE_COMPUTE_SHADER) {
        flags |= VK_SHADER_STAGE_COMPUTE_BIT;
    }
    if (flags == 0) {
        LOG_ERROR("invalid shader stage: ", stage);
    }
    return flags;
}

inline VkImageType ToVkImageType(TextureType type) noexcept {
    switch (type) {
    case Horizon::TextureType::TEXTURE_TYPE_1D:
        return VK_IMAGE_TYPE_1D;
    case Horizon::TextureType::TEXTURE_TYPE_2D:
        return VK_IMAGE_TYPE_2D;
    case Horizon::TextureType::TEXTURE_TYPE_3D:
        return VK_IMAGE_TYPE_3D;
    default:
        LOG_ERROR("invalid image type");
        return VK_IMAGE_TYPE_MAX_ENUM;
    }
}

inline VkFormat ToVkImageFormat(TextureFormat format) noexcept {
    switch (format) {
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_UINT:
        return VK_FORMAT_R8_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_UINT:
        return VK_FORMAT_R8G8_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_UINT:
        return VK_FORMAT_R8G8B8_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_UINT:
        return VK_FORMAT_R8G8B8A8_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_UINT:
        return VK_FORMAT_R16_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_UINT:
        return VK_FORMAT_R16G16_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_UINT:
        return VK_FORMAT_R16G16B16_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_UINT:
        return VK_FORMAT_R16G16B16A16_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_UINT:
        return VK_FORMAT_R32_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_UINT:
        return VK_FORMAT_R32G32_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_UINT:
        return VK_FORMAT_R32G32_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_UINT:
        return VK_FORMAT_R32G32B32A32_UINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_UNORM:
        return VK_FORMAT_R8_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_UNORM:
        return VK_FORMAT_R8G8_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_UNORM:
        return VK_FORMAT_R8G8B8_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_UNORM:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_UNORM:
        return VK_FORMAT_R16_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_UNORM:
        return VK_FORMAT_R16G16_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_UNORM:
        return VK_FORMAT_R16G16B16_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_UNORM:
        return VK_FORMAT_R16G16B16A16_UNORM;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_SINT:
        return VK_FORMAT_R8_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_SINT:
        return VK_FORMAT_R8G8_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_SINT:
        return VK_FORMAT_R8G8B8_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_SINT:
        return VK_FORMAT_R8G8B8A8_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_SINT:
        return VK_FORMAT_R16_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_SINT:
        return VK_FORMAT_R16G16_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_SINT:
        return VK_FORMAT_R16G16B16_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_SINT:
        return VK_FORMAT_R16G16B16A16_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_SINT:
        return VK_FORMAT_R32_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_SINT:
        return VK_FORMAT_R32G32_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_SINT:
        return VK_FORMAT_R32G32B32_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_SINT:
        return VK_FORMAT_R32G32B32A32_SINT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_SFLOAT:
        return VK_FORMAT_R16_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_SFLOAT:
        return VK_FORMAT_R16G16_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_SFLOAT:
        return VK_FORMAT_R16G16B16_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_SFLOAT:
        return VK_FORMAT_R16G16B16A16_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_SFLOAT:
        return VK_FORMAT_R32_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_SFLOAT:
        return VK_FORMAT_R32G32_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_SFLOAT:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_SFLOAT:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    case Horizon::TextureFormat::TEXTURE_FORMAT_D32_SFLOAT:
        return VK_FORMAT_D32_SFLOAT;
    default:
        LOG_ERROR("invalid format");
        return VK_FORMAT_MAX_ENUM;
    }
}

inline VkImageUsageFlags ToVkImageUsage(u32 usage) noexcept {
    VkImageUsageFlags flags = 0;
    if (usage & TextureUsage::TEXTURE_USAGE_R) {
        flags |= VK_IMAGE_USAGE_SAMPLED_BIT;
    }
    if (usage & TextureUsage::TEXTURE_USAGE_RW) {
        flags |= VK_IMAGE_USAGE_STORAGE_BIT;
        flags |= VK_IMAGE_USAGE_SAMPLED_BIT;
    }
    if (flags == 0) {
        LOG_ERROR("invalid image usage: ", usage);
        return {};
    }
    return flags;
}

inline VkImageLayout ToVkImageLayout(TextureUsage usage) noexcept {
    switch (usage) {
    case Horizon::TEXTURE_USAGE_R:
        return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        break;
    case Horizon::TEXTURE_USAGE_RW:
        return VK_IMAGE_LAYOUT_GENERAL;
        break;
    default:
        return VK_IMAGE_LAYOUT_MAX_ENUM;
        break;
    }
}

enum BufferUsage {
    BUFFER_USAGE_VERTEX_BUFFER = 1,
    BUFFER_USAGE_INDEX_BUFFER = 2,
    BUFFER_USAGE_UNIFORM_BUFFER = 4,
    BUFFER_USAGE_RW_BUFFER = 8,
    BUFFER_USAGE_TRANSFER_SRC = 16,
    BUFFER_USAGE_TRANSFER_DST = 32,
    BUFFER_USAGE_DYNAMIC_UPDATE = 64
};

enum class MemoryFlag { DEDICATE_GPU_MEMORY, CPU_VISABLE_MEMORY };

struct BufferCreateInfo {
    u32 buffer_usage_flags;
    u64 size;
    // void* data;
};

inline VkBufferUsageFlags ToVulkanBufferUsage(u32 buffer_usage) noexcept {
    VkBufferUsageFlags flags = 0;
    if (buffer_usage & BUFFER_USAGE_VERTEX_BUFFER) {
        flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    }
    if (buffer_usage & BUFFER_USAGE_INDEX_BUFFER) {
        flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    }
    if (buffer_usage & BUFFER_USAGE_UNIFORM_BUFFER) {
        flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    }
    if (buffer_usage & BUFFER_USAGE_RW_BUFFER) {
        flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    }
    if (buffer_usage & BUFFER_USAGE_TRANSFER_SRC) {
        flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    }

    if (buffer_usage & BUFFER_USAGE_TRANSFER_DST) {
        flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
    }

    return flags;
}

inline u32 UsageToPipelineStage(u32 buffer_usage) noexcept {}

inline D3D12_RESOURCE_FLAGS ToDX12BufferUsage(u32 buffer_usage) noexcept {
    D3D12_RESOURCE_FLAGS flags = D3D12_RESOURCE_FLAG_NONE;
    if (buffer_usage & BUFFER_USAGE_RW_BUFFER) {
        flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    }
    return flags;
}

struct TextureCreateInfo {
    TextureType texture_type;
    TextureFormat texture_format;
    TextureUsage texture_usage;
    u32 width, height, depth = 1;
};

inline DXGI_FORMAT ToDx12TextureFormat(TextureFormat format) {
    switch (format) {
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_UINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_UNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_SINT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R8_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG8_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB8_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA8_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_SNORM:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R16_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG16_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB16_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA16_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_R32_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RG32_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGB32_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_RGBA32_SFLOAT:
        break;
    case Horizon::TextureFormat::TEXTURE_FORMAT_D32_SFLOAT:
        break;
    default:
        LOG_ERROR("invalid texture format, use rgba8 format as default");
        return DXGI_FORMAT_R8G8B8A8_UNORM;
        break;
    }
    return DXGI_FORMAT_R8G8B8A8_UNORM;
}

inline D3D12_RESOURCE_DIMENSION ToDX12TextureDimension(TextureType type) {
    switch (type) {
    case Horizon::TextureType::TEXTURE_TYPE_1D:
        return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
        break;
    case Horizon::TextureType::TEXTURE_TYPE_2D:
        return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        break;
    case Horizon::TextureType::TEXTURE_TYPE_3D:
        return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
        break;
    default:
        LOG_ERROR("invalid image type, use texture2D as default");
        return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
        break;
    }
}

inline D3D12_RESOURCE_FLAGS ToDX12TextureUsage(TextureUsage usage) noexcept {
    switch (usage) {
    case Horizon::TEXTURE_USAGE_R:
        return D3D12_RESOURCE_FLAG_NONE;
    case Horizon::TEXTURE_USAGE_RW:
        return D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    default:
        return D3D12_RESOURCE_FLAG_NONE;
        break;
    }
}

} // namespace Horizon
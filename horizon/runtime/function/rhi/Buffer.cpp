#include "Buffer.h"

namespace Horizon
{
	namespace RHI
	{
		Buffer::Buffer(const BufferCreateInfo &buffer_create_info) noexcept : m_size(buffer_create_info.size), m_usage(buffer_create_info.buffer_usage_flags)
		{
		}
		u32 Buffer::GetBufferUsage() const noexcept
		{
			return m_usage;
		}
		u64 Horizon::RHI::Buffer::GetBufferSize() const noexcept
		{
			return m_size;
		}

	}
}
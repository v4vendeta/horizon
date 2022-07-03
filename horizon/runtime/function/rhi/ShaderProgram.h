#pragma once

#include <string>

#include <runtime/function/rhi/RHIUtils.h>

namespace Horizon::RHI {
class ShaderProgram {
  public:
    // ShaderProgram(ShaderType type, IDxcBlob* dxil_byte_code) noexcept;
    ShaderProgram(ShaderType type, const std::string &entry_point) noexcept;
    virtual ~ShaderProgram() noexcept = default;
    // virtual void* GetBufferPointer() const noexcept = 0;
    // virtual u64 GetBufferSize() const noexcept = 0;
    ShaderType GetType() const noexcept;
    const std::string &GetEntryPoint() const noexcept;

  private:
    const ShaderType m_type{};
    std::string m_entry_point{};
};

} // namespace Horizon::RHI
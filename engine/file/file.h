#include <error/engine_val.h>

namespace file{
    engine::error::EngineVal<void> GetFileBuffer(const char* file_name, char* buffer, size_t& size) noexcept;

    [[nodiscard]]
    engine::error::EngineVal<size_t> GetFileSize(const char* file_name) noexcept;
}
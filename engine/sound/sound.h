#include <error/engine_val.h>

#include <sound/miniaudio.h>
namespace engine::sound{
   engine::error::EngineVal<void> Init() noexcept;
   void PlayMainSound(const char*) noexcept;
   void Dealloc() noexcept;
   void PlayTempSound(const char*) noexcept;

   extern ma_engine _engine;
   extern bool _is_playing;
} 
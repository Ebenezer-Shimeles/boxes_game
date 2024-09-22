#define MINIAUDIO_IMPLEMENTATION
#include <sound/sound.h>

ma_engine engine::sound::_engine;


engine::error::EngineVal<void> engine::sound::Init() noexcept{
    ma_result result;
    
    result = ma_engine_init(NULL, &_engine);
    if (result != MA_SUCCESS) {
        return {{__LINE__, "Failed to initialize audio engine."}};
        
    }
    return {};
}

void engine::sound::PlayMainSound(const char* file) noexcept{

}

void engine::sound::PlayTempSound(const char* file_name) noexcept{
    auto res = ma_engine_play_sound(&_engine, file_name, nullptr);
    
    if (res != MA_SUCCESS) {
        printf("Error playin sound!");
    }
}

void engine::sound::Dealloc() noexcept{
    ma_engine_uninit(&_engine);
}
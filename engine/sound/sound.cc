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
bool engine::sound::_is_playing = false;
void engine::sound::PlayMainSound(const char* filename) noexcept{
   auto res = ma_engine_play_sound(&_engine, filename, nullptr);
    
    if (res != MA_SUCCESS) {
        printf("Error playin sound!");
    }
}

void engine::sound::PlayTempSound(const char* file_name) noexcept{
    if(_is_playing){
        return;
    }
    _is_playing = true;
    auto res = ma_engine_play_sound(&_engine, file_name, nullptr);
    
    if (res != MA_SUCCESS) {
        printf("Error playin sound!");
    }

    _is_playing = false;
}

void engine::sound::Dealloc() noexcept{
    ma_engine_uninit(&_engine);
}
#include <error/engine_val.h>
// #include <core/game_object.h>
#pragma once
#include <GLFW/glfw3.h>

#include <vector>
#include <texture/texture.h>

#ifndef ENGINE_CORE
#define ENGINE_CORE
namespace engine::core{
    engine::error::EngineVal<void> Init() noexcept;
    engine::error::EngineVal<void> MainLoop() noexcept;
    engine::error::EngineVal<void> Dealloc() noexcept;
   // std::vector<GameObject> objects{};

    extern int16_t _window_height, _window_width;
    
    extern GLFWwindow* _window;
}
#endif
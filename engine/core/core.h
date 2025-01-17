#include <error/engine_val.h>
#include <core/game_object.h>
#pragma once
#include <GLFW/glfw3.h>

#include <vector>


#ifndef ENGINE_CORE
#define ENGINE_CORE
namespace engine::core{
    engine::error::EngineVal<void> Init() noexcept;
    engine::error::EngineVal<void> MainLoop() noexcept;
    engine::error::EngineVal<void> Dealloc() noexcept;

    void SetWorldBackground( char*const) noexcept;
    
    void Instanciate(GameObject*) noexcept;
   // void Delete(const GameObject&) noexcept;

    extern std::vector<engine::core::GameObject*> _objects;

    extern int16_t _window_height, _window_width;
    
    extern GLFWwindow* _window;
    extern bool _is_background_set;
  

    extern char* __background;
}
#endif
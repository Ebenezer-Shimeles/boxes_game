#include <GLFW/glfw3.h>

#include <map>
#include <unordered_map>
#include <functional>
#include <tuple>
#include <unordered_set>

#pragma once
namespace engine::core{
    extern GLFWwindow *_window;
}

namespace engine::input{
    extern std::unordered_map<uint8_t, int> _bindings;
    extern std::map<int, std::function<void()>> _kbd_bindings;
    void ProcessKeys() noexcept;
    void Init() noexcept;
    void RegisterKeyAction(const uint8_t, std::function<void()>) noexcept;

}
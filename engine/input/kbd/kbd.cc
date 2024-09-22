#include <kbd/kbd.h>


#include <cstdio>

std::unordered_map<uint8_t, int> engine::input::_bindings = {
   
};
std::map<int, std::function<void()>> engine::input::_kbd_bindings = {};
void engine::input::ProcessKeys() noexcept{
    for(auto& [key, func] : _kbd_bindings){
       if( glfwGetKey(engine::core::_window, key) == GLFW_PRESS){
         func();
       }
    }
    
}
void engine::input::Init() noexcept{
    printf("Initalizing keyboard\n");
    engine::input::_bindings.emplace('W', GLFW_KEY_W);
    engine::input::_bindings.emplace('S', GLFW_KEY_S);
}

void engine::input::RegisterKeyAction(const uint8_t chr, std::function<void()> action) noexcept{
    printf("Registering action for %c\n", chr);
    engine::input::_kbd_bindings.emplace(
        engine::input::_bindings[chr],
        action
    );
}
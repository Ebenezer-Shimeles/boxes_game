#include <stddef.h>
#include <stdint.h>

#pragma once
namespace engine::error{
    struct EngineError{
        int16_t line;
        char error_message[255]{};
        
    };
}
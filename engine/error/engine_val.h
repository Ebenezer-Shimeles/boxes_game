#include "engine_error.h"
#pragma once

#include <memory>
namespace engine{
    namespace error{
        template<typename T>
        class EngineVal{
            private:
                bool m_is_error_ = false;

            public:
                EngineVal() = delete;
                EngineVal(const T& v): val(v){}; 
                EngineVal(T&& v) : val(std::move(v)){}
                EngineVal(const EngineError& e) : m_is_error_(true), err(e){}

                T val;
                EngineError err;
                bool IsError() const { return m_is_error_;};

        };

        template<>
        class EngineVal<void>{
            private:
                bool m_is_error_ = false;

            public:
                EngineVal(void) = default;
                EngineVal(const engine::error::EngineError& e): err(e){} ;
                EngineError err;
                bool IsError() const {return m_is_error_;};
        };
    }
}
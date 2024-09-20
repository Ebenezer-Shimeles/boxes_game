
#include <stddef.h>
#include <stdint.h>

#include <error/engine_val.h>
#pragma once
class Shader;
class ShaderBuilder{
private:



   uint32_t m_vertex_shader = 0;
   uint32_t m_frag_shader = 0;
  

public:
      
     engine::error::EngineVal<void>  SetVertexShaderFile(const char*) noexcept;
     
     engine::error::EngineVal<void>  SetFragmentShaderFile(const char*) noexcept;

      engine::error::EngineVal<void> SetVertexShaderBuffer(uint8_t[], const size_t&) noexcept;
      engine::error::EngineVal<void> SetFragmentShaderBuffer(uint8_t[], const size_t&) noexcept;



     [[nodiscard]]
     engine::error::EngineVal<Shader> Build() noexcept;
   
};
class Shader{
private:
       int32_t m_shader_id_ = 0;
       Shader();
public:
  
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    
    Shader(Shader&&);
    Shader& operator= ( Shader&&);
    ~Shader() noexcept;


    engine::error::EngineVal<void> m_Dealloc() noexcept;


    engine::error::EngineVal<void> Bind() noexcept;
    engine::error::EngineVal<void> Unbind() noexcept;

    GLuint GetId() const;

    friend  engine::error::EngineVal<Shader> ShaderBuilder::Build() noexcept;

};


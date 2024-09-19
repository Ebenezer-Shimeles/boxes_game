#include <glad/glad.h>

#include <memory>
#include <cstdio>

#include <error/engine_error.h>
#include <error/engine_val.h>
#include <file/file.h>
#include <gl_call.h>
#include "shader_program.h"

Shader::Shader(){}

Shader::Shader(Shader&& other){
    printf("Moving shader with id %i \n", other.m_shader_id_);
    this->m_shader_id_ = other.m_shader_id_;
  
    other.m_shader_id_ = 0;

}
Shader& Shader::operator=(Shader&& other){
    this->m_shader_id_ = other.m_shader_id_;
    other.m_shader_id_ = -1;
    return *this;
}

engine::error::EngineVal<void> Shader::Bind() noexcept{
    if(m_shader_id_ == 0){
        return {{__LINE__, "Using an improper shader!"}};
    }

    GL_CALL(glUseProgram(m_shader_id_));
    return {};
}

engine::error::EngineVal<void> Shader::Unbind() noexcept{
    glUseProgram(0);
}

engine::error::EngineVal<void> Shader::m_Dealloc() noexcept{
    printf("Removing shader with id  %i\n", m_shader_id_);
    if(m_shader_id_ == 0){
        return {};
    }
    Unbind();
    glDeleteProgram(m_shader_id_);
    m_shader_id_ = 0;

}

Shader::~Shader(){
    m_Dealloc();
}




engine::error::EngineVal<void>  ShaderBuilder::SetVertexShaderFile(const char* file) noexcept{
    size_t file_size;
    auto buffer_tpl = file::GetFileBuffer(file, file_size);
    if(buffer_tpl.IsError()){
        return {buffer_tpl.err};
    }
 
    auto buffer = buffer_tpl.val.get();
    SetVertexShaderBuffer(buffer, file_size);
    
    return {};

}

engine::error::EngineVal<void>  ShaderBuilder::SetFragmentShaderFile(const char* file) noexcept{
    size_t file_size;
   
    auto buffer_tpl = file::GetFileBuffer(file, file_size);
    if(buffer_tpl.IsError()){
        return {buffer_tpl.err};
    }
    auto buffer = buffer_tpl.val.get();

    SetFragmentShaderBuffer(buffer, file_size);
    
    return {};

}

engine::error::EngineVal<void> ShaderBuilder::SetVertexShaderBuffer(uint8_t buffer[], const size_t&) noexcept{
    
   m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   auto casted_buffer = reinterpret_cast<char*>(buffer);
  
   GL_CALL(glShaderSource(m_vertex_shader, 1,&casted_buffer , (GLint*)nullptr));

   GL_CALL(glCompileShader(m_vertex_shader));
    
   int32_t compileStatus;
   GL_CALL(glGetShaderiv(m_vertex_shader, GL_COMPILE_STATUS, &compileStatus));
   if(!compileStatus){
      char erro[255]{};
      GL_CALL(glGetShaderInfoLog(m_vertex_shader, 255, &compileStatus, erro));
      printf("Error compiling shader:: %s\n", erro);
      return {{__LINE__, "Error couldn't compile vertex shader"}};
   }
   return {};

}
engine::error::EngineVal<void> ShaderBuilder::SetFragmentShaderBuffer( uint8_t buffer[], const size_t&) noexcept{
        
   m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
   auto casted_buffer = reinterpret_cast<char*>(buffer);
   glShaderSource(m_frag_shader, 1,&casted_buffer , (GLint*)nullptr);
   glCompileShader(m_frag_shader);
   int32_t compileStatus;
   glGetShaderiv(m_frag_shader, GL_COMPILE_STATUS, &compileStatus);
   if(!compileStatus){
      char erro[255]{};
      glGetShaderInfoLog(m_frag_shader, 255, &compileStatus, erro);
      printf("Error compiling shader:: %s\n", erro);
      return {{__LINE__, "Error couldn't compile fragment shader"}};
   }
   return {};
}



engine::error::EngineVal<Shader> ShaderBuilder::Build() noexcept{
    auto shader = Shader();

    auto program = glCreateProgram();
    GL_CALL(glAttachShader(program, m_vertex_shader));
    GL_CALL(glAttachShader(program, m_frag_shader));
    GL_CALL(glLinkProgram(program));
   

    GL_CALL(glDeleteShader(m_vertex_shader));
    GL_CALL(glDeleteShader(m_frag_shader));
    shader.m_shader_id_ = program;
 
    return {std::move(shader)};
}
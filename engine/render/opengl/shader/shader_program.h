
#include <stddef.h>
#include <stdint.h>

#include <error/engine_val.h>
class Shader{
private:
       int32_t shader_id_;
       bool m_is_dealloced;
public:
    Shader() = default;
    Shader(const Shader&) = delete;
    Shader(Shader&&);
    ~Shader() noexcept;
    engine::error::EngineVal<void> m_Dealloc() noexcept;


    engine::error::EngineVal<void> Bind() noexcept;
    engine::error::EngineVal<void> Unbind() noexcept;

};

class ShaderBuilder{
private:

   const char* vertex_shader_src_;
   const char* fragment_shader_src_;
public:
     void SetVertexShaderFile(const char*) noexcept;
     void SetFragmentShaderFile(const char*) noexcept;

     [[nodiscard]]
     Shader Build() noexcept;
   
};
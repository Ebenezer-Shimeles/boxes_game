#include <shader/uniform.h>
#include <gl_call.h>
using namespace engine::render::opengl::shader;


Uniform::Uniform(const GLuint& shader_id, const char* name){
    m_location = GL_CALL(glGetUniformLocation(shader_id, name));
}

void Uniform::SetMat4fv(glm::f32 *val_ptr) noexcept{
   GL_CALL(glUniformMatrix4fv(m_location, 1, GL_FALSE, val_ptr));
}
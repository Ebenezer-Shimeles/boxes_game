#include <glad/glad.h>
#include <shader/shader_program.h>
#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
namespace engine::render::opengl::shader{
    class Uniform{
        private:
           char* m_name;
           GLuint m_location;

        public:
            Uniform(const GLuint& shader_id, const char* name);

            void SetMat4fv(glm::f32 *val_ptr) noexcept;
            
        
    };
}
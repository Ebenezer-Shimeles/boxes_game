#include <glad/glad.h>
#include <error/engine_val.h>

#pragma once
namespace engine::render::opengl{
    class VBO;
    class VBOBuilder{
        private:
            void* m_data;
            GLenum m_usage = GL_STATIC_DRAW;
            size_t m_buffer_size;
        public:
            VBO Build() noexcept;
            VBOBuilder& SetUsage(const GLenum& ) noexcept;
            VBOBuilder& SetData(void*) noexcept;
            VBOBuilder& SetBufferSize(const size_t&) noexcept;
            
    };
    class VBO{
        private:
            GLuint m_id;
            VBO();

            void m_Dispose() noexcept;
        public:
            void Bind() noexcept;
            void Unbind() noexcept;

            ~VBO();
            VBO(const VBO&) = delete;
            VBO& operator=(const VBO&) = delete;

            VBO(VBO&&);
            VBO& operator=(VBO&&);
            friend VBO  VBOBuilder::Build() noexcept;
             const GLuint& GetId() const;

    };

}
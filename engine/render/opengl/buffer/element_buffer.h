#include <glad/glad.h>
#include <error/engine_val.h>
#pragma once
namespace engine::render::opengl{
    class EBO;
    class EBOBuilder{
        private:
            void* m_data;
            GLenum m_usage = GL_STATIC_DRAW;
            size_t m_buffer_size;
        public:
            EBO Build() noexcept;
            EBOBuilder& SetUsage(const GLenum& ) noexcept;
            EBOBuilder& SetData(void*) noexcept;
            EBOBuilder& SetBufferSize(const size_t&) noexcept;
            
            
    };
    class EBO{
        private:
            GLuint m_id;
            EBO();

            void m_Dispose() noexcept;
        public:
            void Bind() noexcept;
            void Unbind() noexcept;

            ~EBO();
            EBO(const EBO&) = delete;
            EBO& operator=(const EBO&) = delete;

            EBO(EBO&&);
            EBO& operator=(EBO&&);
            friend EBO  EBOBuilder::Build() noexcept;

            const GLuint& GetId() const;

    };

}
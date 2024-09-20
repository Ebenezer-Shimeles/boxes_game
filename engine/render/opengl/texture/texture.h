#include <glad/glad.h>

#include <error/engine_val.h>

#pragma once
namespace render{
    namespace opengl{
        namespace texture{
            class Texture;
            class TextureBuilder{

                void * m_buffer;
                size_t m_image_width, m_image_height;
                public:
                    TextureBuilder& SetBuffer(void *) noexcept;
                    TextureBuilder& SetImageWidth(const size_t&) noexcept;
                    TextureBuilder& SetImageHeight(const size_t&) noexcept;

                    Texture  Build() noexcept;
            };
            class Texture{
                private:
                GLuint m_id;
                Texture();
                void m_Dispose() noexcept;
                
                public:
                    void Bind() noexcept;
                    void Unbind() noexcept;
                    ~Texture();
                    Texture(const Texture&) = delete;
                    Texture& operator=(const Texture&) = delete;

                    Texture(Texture&&);
                    Texture& operator=(Texture&&);
                    friend TextureBuilder;
                    friend engine::error::EngineVal<Texture>;
                    const GLuint& GetId() const;
                    
            
            };


            engine::error::EngineVal<Texture> TextureFromFile(const char*,  bool flip = false);
        }
    }
}
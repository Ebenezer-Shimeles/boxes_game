#include <texture/texture.h>
#include <gl_call.h>
// #include <file/file.h>


#include <cstdio>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace render::opengl::texture;

Texture::Texture(){};

void Texture::m_Dispose() noexcept{
    printf("Disposing texture with id %i\n", m_id);
    if(m_id == 0){
        return;
    }
    m_id = 0;
}

void Texture::Bind() noexcept{
    printf("Binding texture with id %i\n", m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind() noexcept{
    printf("Uninding texture with id %i\n", m_id);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture(){
  Unbind();
  m_Dispose();   
}


Texture::Texture(Texture&& other){
    printf("Moving texture with id %i\n", other.m_id);
    this->m_id = other.m_id;
    other.m_id = 0;
}
Texture& Texture::operator=(Texture&& other){
    printf("Moving texture with id %i\n", other.m_id);
   this->m_id = other.m_id;
   other.m_id = 0;
}
           
const GLuint& Texture::GetId() const
{
    return m_id;
}

TextureBuilder& TextureBuilder::SetBuffer(void *buffer) noexcept{
   this->m_buffer = buffer;
   return *this;
}
TextureBuilder& TextureBuilder::SetImageWidth(const size_t& val) noexcept{
   this->m_image_width = val;
   return *this;
}
TextureBuilder& TextureBuilder::SetImageHeight(const size_t& val) noexcept{
   this->m_image_height = val;
   return *this;
}
Texture  TextureBuilder::Build() noexcept{
    auto rv = Texture();
    GL_CALL(glGenTextures(1, &rv.m_id));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, rv.m_id));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_image_width, m_image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_buffer));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CALL(glActiveTexture(GL_TEXTURE1));
    rv.Unbind();
    return std::move(rv);
}
engine::error::EngineVal<Texture> render::opengl::texture::TextureFromFile(const char* file_name, bool flip ){
    // size_t file_size;
    // auto file_tpl = file::GetFileBuffer(file_name, file_size);
    // if(file_tpl.IsError()){
    //     return file_tpl.err;
    // } 
    stbi_set_flip_vertically_on_load(flip);
    
    int width, height, n_color;
    
    auto buffer = stbi_load(file_name, &width, &height, &n_color, 0);
    if(!buffer){
        engine::error::EngineError err = {__LINE__, "Error could not load image!"};
        return {err};
    }
   

    auto texutre = TextureBuilder().SetBuffer(buffer).SetImageHeight(height).SetImageWidth(width).Build();
    return {std::move(texutre)};
}
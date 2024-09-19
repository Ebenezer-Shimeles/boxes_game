#include <buffer/vertex_array_object.h>
#include <gl_call.h>

#include <algorithm>
using namespace engine::render::opengl;


VAO::VAO(){}

VAO::~VAO(){
    Unbind();
    m_Dispose();
}


VAO::VAO(VAO&& other){
    this->m_id = other.m_id;
    other.m_id = 0;
}
VAO& VAO::operator=(VAO&& other){
    this->m_id = other.m_id;
    other.m_id = 0;

}

void VAO::Bind() noexcept{
  GL_CALL(glBindVertexArray(m_id));
}
void VAO::Unbind() noexcept{
   GL_CALL(glBindVertexArray(0));
}

void VAO::m_Dispose() noexcept{
    if(m_id == 0){
        return;
    }
    printf("Removing vertex array with id %i\n", m_id);
    GL_CALL(glDeleteVertexArrays(1, &m_id));
}


VAOBuilder& VAOBuilder::AddAttribPointer(const AttribPointer& attrib){
   m_attribs.push_back(attrib);
   return *this;
}
// VAOBuilder& VAOBuilder::RemoveAttribPointer(const AttribPointer& attrib){
//    auto position = std::find(m_attribs.begin(), m_attribs.end(), attrib);
//    if (position != m_attribs.end()){
//        m_attribs.erase(position);
//    }
  
//    return *this;
// }
VAOBuilder& VAOBuilder::SetEBOID( const GLuint& val) noexcept{
    m_ebo_id = val;
    return *this;
}
VAOBuilder& VAOBuilder::SetVBOID( const GLuint& val) noexcept{
    m_vbo_id = val;
    return *this;
}

 VAO VAOBuilder::Build() noexcept{
    auto rv = VAO();
    GL_CALL(glGenVertexArrays(1, &rv.m_id));
    GL_CALL(glBindVertexArray(rv.m_id)); 
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id));
    for(auto& attrib: m_attribs){
        glVertexAttribPointer(attrib.location, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.pointer);
        glEnableVertexAttribArray(attrib.location);
    }
    rv.Unbind();
    return std::move(rv);
 }


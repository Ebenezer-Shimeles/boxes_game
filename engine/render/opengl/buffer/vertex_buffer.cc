#include <buffer/vertext_buffer.h>
#include <gl_call.h>

#include <memory>
using namespace engine::render::opengl;
VBO::VBO(){}

void VBO::m_Dispose() noexcept{
    printf("Disposing VBO with id %i\n", m_id);
    GL_CALL(glDeleteBuffers(1, &m_id));
    m_id = 0;
}
void VBO::Unbind() noexcept{
   printf("Unbinding VBO with id %i\n", m_id);
   GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void VBO::Bind() noexcept{
   printf("Binding VBO with id %i\n", m_id);
   GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

VBO::VBO(VBO&& other){
    fprintf(stdout, "Moving VBO with id %i\n", other.m_id);
    this->m_id = other.m_id;
    other.m_id =0;
}
VBO& VBO::operator=(VBO&& other){
    fprintf(stdout, "Moving VBO with id %i\n", other.m_id);
    this->m_id = other.m_id;
    other.m_id =0;
}
VBO::~VBO(){
    Unbind();
    m_Dispose();
    
}



VBOBuilder& VBOBuilder::SetUsage(const GLenum& u) noexcept{
    this->m_usage = u;
    return *this;
}


VBOBuilder& VBOBuilder::SetBufferSize(const size_t& buffer_size )noexcept{
    this->m_buffer_size = buffer_size;
    return *this;
}


VBOBuilder& VBOBuilder::SetData(void *data_ptr) noexcept{
    this->m_data = data_ptr;
    return *this;
}

VBO  VBOBuilder::Build() noexcept{
    auto rv = VBO();
    glGenBuffers(1, &rv.m_id);
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rv.m_id));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, m_buffer_size, m_data, m_usage));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return {std::move(rv)};
}
const GLuint& VBO::GetId() const{
    return m_id;
}

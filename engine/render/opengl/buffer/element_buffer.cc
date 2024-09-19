#include <buffer/element_buffer.h>
#include <gl_call.h>

#include <memory>
using namespace engine::render::opengl;
EBO::EBO(){}

void EBO::m_Dispose() noexcept{
    printf("Disposing EBO with id %i\n", m_id);
    GL_CALL(glDeleteBuffers(1, &m_id));
    m_id = 0;
}
void EBO::Unbind() noexcept{
   printf("Unbinding EBO with id %i\n", m_id);
   GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
void EBO::Bind() noexcept{
   printf("Binding EBO with id %i\n", m_id);
   GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

EBO::EBO(EBO&& other){
    fprintf(stdout, "Moving EBO with id %i\n", other.m_id);
    this->m_id = other.m_id;
    other.m_id =0;
}
EBO& EBO::operator=(EBO&& other){
    fprintf(stdout, "Moving EBO with id %i\n", other.m_id);
    this->m_id = other.m_id;
    other.m_id =0;
}
EBO::~EBO(){
    Unbind();
    m_Dispose();
    
}



EBOBuilder& EBOBuilder::SetUsage(const GLenum& u) noexcept{
    this->m_usage = u;
    return *this;
}


EBOBuilder& EBOBuilder::SetBufferSize(const size_t& buffer_size )noexcept{
    this->m_buffer_size = buffer_size;
    return *this;
}


EBOBuilder& EBOBuilder::SetData(void *data_ptr) noexcept{
    this->m_data = data_ptr;
    return *this;
}

EBO  EBOBuilder::Build() noexcept{
    auto rv = EBO();
    glGenBuffers(1, &rv.m_id);
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rv.m_id));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_buffer_size, m_data, m_usage));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    return {std::move(rv)};
}

const GLuint& EBO::GetId() const{
    return m_id;
}
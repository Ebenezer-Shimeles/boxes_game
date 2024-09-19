#include <glad/glad.h>

#include <buffer/element_buffer.h>
#include <buffer/vertext_buffer.h>
#include <error/engine_val.h>

#include <vector>
namespace engine::render::opengl{
   class VAO;
   struct AttribPointer{
       GLuint location;
       GLint size;
       GLenum type;
       GLboolean normalized;
       GLsizei stride;
       void *pointer;
   };
   class VAOBuilder{
       private:
           GLuint m_ebo_id;
           GLuint m_vbo_id;
           std::vector<AttribPointer> m_attribs;
       public:
            VAOBuilder(){}
            VAO Build() noexcept;
            
 
            VAOBuilder& SetVBOID(const GLuint&) noexcept;
            VAOBuilder& SetEBOID(const GLuint&) noexcept;
            VAOBuilder& AddAttribPointer(const AttribPointer&);
           // VAOBuilder& RemoveAttribPointer(const AttribPointer&);

          

   };
   class VAO{
      private:
          GLuint m_id;
          VAO();
          void m_Dispose() noexcept;
      public:
         ~VAO();
         VAO(const VAO&) = delete;
         VAO& operator=(const VAO&) = delete;

         VAO(VAO&&);
         VAO& operator=(VAO&&);

         void Bind() noexcept;
         void Unbind() noexcept;
         void EnablePointer(const uint32_t&);
         void DisablePointer(const uint32_t&);
        
         friend VAOBuilder;
        

   };
   
}


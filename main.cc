#include <glad/glad.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <memory>
#include <cstring>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <shader/shader_program.h>
#include <buffer/vertext_buffer.h>
#include <buffer/vertex_array_object.h>
#include <buffer/element_buffer.h>
#include <gl_call.h>

#include <shader/uniform.h>
#include <camera/camera.h>

#include <core/core.h>

int main(){
  
   auto engine_tpl = engine::core::Init();
   if(engine_tpl.IsError()){
      fprintf(stderr, "Error %s\n", engine_tpl.err.error_message);
      return-1;
   }
   auto x = render::opengl::texture::TextureFromFile("b.jpg", false);
   x.val.Bind();
   engine::core::MainLoop();
   engine::core::Dealloc();
}
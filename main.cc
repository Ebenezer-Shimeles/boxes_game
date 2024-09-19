#include <glad/glad.h>

#include <iostream>
#include <memory>
#include <cstring>
#include <GLFW/glfw3.h>
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

int main(){
   if(!glfwInit()){
      std::cerr << "Error could not init glfw!\n";
      return -1;
   }
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  

   auto window = glfwCreateWindow(800, 800, "Granny", nullptr, nullptr);
   if(!window){
     std::cerr << "Error could not create window!";
     glfwTerminate();
     return -1;
   }
   
   glfwMakeContextCurrent(window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return -1;
      
   }   
   GL_CALL(glEnable(GL_DEPTH_TEST));
 
   

  
   //
   float vertices[] = {
     1.0, -1.0,
     -1.0, -1.0,
     -1.0, 1.0,
      1.0, 1.0
   };
   // uint32_t VAO;
   // GL_CALL(glGenVertexArrays(1, &VAO));
   // GL_CALL(glBindVertexArray(VAO)); 


   // uint32_t VBO;
   // GL_CALL(glGenBuffers(1, &VBO));
   // GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
   // GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW));

   uint32_t indices[] = {0, 1, 2, 0, 2, 3};
   auto vbo = engine::render::opengl::VBOBuilder().SetBufferSize(8 * sizeof(float)).SetData(vertices).Build();
 //  vbo.Bind();

   auto ebo = engine::render::opengl::EBOBuilder().SetBufferSize(6 * sizeof(uint32_t)).SetData(indices).Build();
   //ebo.Bind();

   auto vao = engine::render::opengl::VAOBuilder().SetEBOID(ebo.GetId())
                                                  .SetVBOID(vbo.GetId())
                                                  .AddAttribPointer({
                                                   .location = 0,
                                                   .size = 2,
                                                   .type = GL_FLOAT,
                                                   .normalized = GL_FALSE, 
                                                   .stride = 2 * sizeof(float),
                                                   .pointer = nullptr
                                                   }).Build();
                                                
   vao.Bind();
  // vao.Unbind();
  // GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2 *sizeof(float),nullptr));
   

   auto shaderBuilder = ShaderBuilder();
   shaderBuilder.SetVertexShaderFile("vs.vs");
   shaderBuilder.SetFragmentShaderFile("fs.fs");

   auto shader_tpl = shaderBuilder.Build();
   if(shader_tpl.IsError()){
      fprintf(stderr, "Could not build shader! exiting\n");
      return -1;
   }
   auto shader = std::move(shader_tpl.val);
   shader.Bind();
  
   while(!glfwWindowShouldClose(window)){
       GL_CALL(glClearColor(0, 0, 0, 0));
       GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
       //
      // GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
      // GL_CALL(glEnableVertexAttribArray(0));
     //  GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       //
       glfwPollEvents();
       glfwSwapBuffers(window);
   }
   glfwDestroyWindow(window);
   glfwTerminate();
}
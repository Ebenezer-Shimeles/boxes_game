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
#include <texture/texture.h>
#include <shader/uniform.h>
#include <camera/camera.h>

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
     1, -1,    1.0, 0,
     -1, -1,   0, 0,
     -1, 1,    0, 1.0,
      1, 1,    1.0, 1.0
   };
   // uint32_t VAO;
   // GL_CALL(glGenVertexArrays(1, &VAO));
   // GL_CALL(glBindVertexArray(VAO)); 


   // uint32_t VBO;
   // GL_CALL(glGenBuffers(1, &VBO));
   // GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
   // GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW));

   uint32_t indices[] = {0, 1, 2, 0, 2, 3};
   auto vbo = engine::render::opengl::VBOBuilder().SetBufferSize(sizeof(vertices)).SetData(vertices).Build();
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
                                                   .stride = 4 * sizeof(float),
                                                   .pointer = nullptr
                                                   })
                                                   .AddAttribPointer({
                                                   .location = 1,
                                                   .size = 2,
                                                   .type = GL_FLOAT,
                                                   .normalized = GL_FALSE, 
                                                   .stride = 4 * sizeof(float),
                                                   .pointer = (void*)(sizeof(float)*2)

                                                   })
                                                   .Build();
                                                
   vao.Bind();
   
  // vao.Unbind();
  // GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2 *sizeof(float),nullptr));
   

   auto shaderBuilder = ShaderBuilder();
   auto vsresult_tpl = shaderBuilder.SetVertexShaderFile("vs.vs");
   if(vsresult_tpl.IsError()){
      fprintf(stderr, "Error %s\n", vsresult_tpl.err.error_message);
      return -1;
   }
   auto fsresult_tpl = shaderBuilder.SetFragmentShaderFile("fs.fs");
   if(fsresult_tpl.IsError()){
      fprintf(stderr, "Error %s\n", fsresult_tpl.err.error_message);
      return -1;
   }

   auto text_tpl = render::opengl::texture::TextureFromFile("a.jpg", true);
   if(text_tpl.IsError()){
      printf("Error could not load texture!\n");
      return -1;
   }
   text_tpl.val.Bind();

   auto shader_tpl = shaderBuilder.Build();
   if(shader_tpl.IsError()){
      fprintf(stderr, "Could not build shader! exiting\n");
      return -1;
   }
   auto shader = std::move(shader_tpl.val);
   shader.Bind();
   
   
   auto model_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "model");
   auto view_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "view");
   auto projection_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "projection");
   glViewport(0, 0, 800, 800);
   glm::mat4 model(1);
   model = glm::translate(model, glm::vec3(0, 0, 25));
   model =  glm::scale(model, glm::vec3(15, 15, 0));
   model_uniform.SetMat4fv(glm::value_ptr(model));
   
   engine::render::opengl::camera::Camera::LookAt({0,0});
   auto cm_val  = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 50), glm::vec3(0, 1,0)); //engine::render::opengl::camera::Camera::GetLookAtMatrix();
   auto cm_val_raw = glm::value_ptr(cm_val);
   view_uniform.SetMat4fv( cm_val_raw  );

   
   auto projection = glm::perspective(float(glm::radians(60.0)), (float)(800/800), 0.1f, 100.0f);
   projection_uniform.SetMat4fv(glm::value_ptr(projection));
   auto x = render::opengl::texture::TextureFromFile("b.jpg", true);
   while(!glfwWindowShouldClose(window)){
       GL_CALL(glClearColor(0, 0, 0, 0));
       GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
       x.val.Bind();
     
      
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       //
       glfwPollEvents();
       glfwSwapBuffers(window);
   }
   glfwDestroyWindow(window);
   glfwTerminate();
}
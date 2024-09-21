#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi



#include <core/core.h>
#include <gl_call.h>
#include <shader/uniform.h>
#include <buffer/element_buffer.h>
#include <buffer/vertext_buffer.h>
#include <shader/shader_program.h>
#include <buffer/vertex_array_object.h>


#include <cstdio>
#include <algorithm>

using namespace engine::core;
int16_t engine::core::_window_height=800;
int16_t engine::core::_window_width=800;
GLFWwindow *engine::core::_window;
std::vector<engine::core::GameObject> engine::core::_objects;

engine::error::EngineVal<void> engine::core::Init() noexcept{
    if(!glfwInit()){
      return{{__LINE__, "Error could not init glfw!\n"}};
   
   }
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  

   _window = glfwCreateWindow(800, 800, "Granny", nullptr, nullptr);
   if(!_window){
     puts("Error could not create window!\n");
     glfwTerminate();
     return {{__LINE__, "Error could not create window!"}};
   }
   
   glfwMakeContextCurrent(_window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      printf("Failed to initialize GLAD");
      glfwTerminate();
      return {{__LINE__, "Error could not init GLAD!"}};
      
   }   
   GL_CALL(glEnable(GL_DEPTH_TEST));
 
   return {};

  
}

engine::error::EngineVal<void> engine::core::MainLoop() noexcept{
      //
   float vertices[] = {
     1, -1,    1.0, 0,
     -1, -1,   0, 0,
     -1, 1,    0, 1.0,
      1, 1,    1.0, 1.0
   };
 
   uint32_t indices[] = {0, 1, 2, 0, 2, 3};
   auto vbo = engine::render::opengl::VBOBuilder().SetBufferSize(sizeof(vertices)).SetData(vertices).Build();


   auto ebo = engine::render::opengl::EBOBuilder().SetBufferSize(6 * sizeof(uint32_t)).SetData(indices).Build();


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
   
 
   

   auto shaderBuilder = ShaderBuilder();
   auto vsresult_tpl = shaderBuilder.SetVertexShaderFile("vs.vs");
   if(vsresult_tpl.IsError()){
       return vsresult_tpl.err;
   }
   auto fsresult_tpl = shaderBuilder.SetFragmentShaderFile("fs.fs");
   if(fsresult_tpl.IsError()){
      return fsresult_tpl.err;
    
   }



   auto shader_tpl = shaderBuilder.Build();
   if(shader_tpl.IsError()){
      return {{__LINE__, "Could not build shader! exiting"}};
      
   }
   auto shader = std::move(shader_tpl.val);
   shader.Bind();


   
   auto model_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "model");
   auto view_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "view");
   auto projection_uniform = engine::render::opengl::shader::Uniform(shader.GetId(), "projection");
   glViewport(0, 0, 800, 800);
   glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int w, int h){
         GL_CALL(glViewport(0, 0, w,h));
   });
   glm::mat4 model(1);
   model = glm::translate(model, glm::vec3(0, 0, 25));
   model =  glm::scale(model, glm::vec3(15, 15, 0));
   model_uniform.SetMat4fv(glm::value_ptr(model));
   

   auto cm_val  = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 50), glm::vec3(0, 1,0)); //engine::render::opengl::camera::Camera::GetLookAtMatrix();
   auto cm_val_raw = glm::value_ptr(cm_val);
   view_uniform.SetMat4fv( cm_val_raw  );

   
   auto projection = glm::perspective(float(glm::radians(60.0)), (float)(800/800), 0.1f, 100.0f);
   projection_uniform.SetMat4fv(glm::value_ptr(projection));
    

    GL_CALL(glClearColor(0, 0, 0, 0));
    while(!glfwWindowShouldClose(engine::core::_window)){
       
       GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

       for(auto& obj : _objects){
          obj.Update();
       }
      
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       //
       glfwPollEvents();
       glfwSwapBuffers(engine::core::_window);
   }
   
   return {};
}

engine::error::EngineVal<void> engine::core::Dealloc() noexcept{
    glfwDestroyWindow(engine::core::_window);
   glfwTerminate();
   return {};
}

void engine::core::Instanciate(const GameObject& obj) noexcept{
   _objects.push_back(obj);
}
void engine::core::Delete(const GameObject& obj) noexcept{
   //TODO need to remplement this with ID
   auto index = std::find(_objects.begin(), _objects.end(), obj);
   if(index != _objects.end()){
      _objects.erase(index);
   }
}
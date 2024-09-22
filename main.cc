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
#include <kbd/kbd.h>

#include <shader/uniform.h>
#include <camera/camera.h>


#include <game/dummy.h>

#include <core/core.h>
#include <core/game_object.h>

using namespace engine::core;
class Person :  public engine::core::GameObject{
    void Update() noexcept override{
        GameObject::Update(); //Base
    }
};

int main(){
  
   auto engine_tpl = engine::core::Init();
   if(engine_tpl.IsError()){
      fprintf(stderr, "Error %s\n", engine_tpl.err.error_message);
      return-1;
   }

   auto x = render::opengl::texture::TextureFromFile("b.jpg", true);
  
   auto c = Person();

   if(x.IsError()){
      puts(x.err.error_message);
      return -1;

   }
   puts("here\n");
   auto render = RenderProperty( std::move(x.val));
   c.AddProperty(render);
  // c.SetAccleration({0.000001, 0.000001});
   c.SetSize({5, 5});
   engine::input::RegisterKeyAction('W', [&c ](){
      //  c.AddDistance({1, 0});
      c.AddDistance({0.1, 0});

      // auto pos = c.GetPosition();
      // printf("Position is at x=%i y=%i\n", pos.x, pos.y);
   });
   engine::input::RegisterKeyAction('S', [&c ](){
      //  c.AddDistance({1, 0});
      c.AddDistance({ -0.1, 0});

      // auto pos = c.GetPosition();
      // printf("Position is at x=%i y=%i\n", pos.x, pos.y);
   });
   Instanciate(&c);
   puts("HERE\n");
   // c.AddDistance({10, 10});

   engine::core::MainLoop();
   engine::core::Dealloc();
}
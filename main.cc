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



#include <core/core.h>
#include <core/game_object.h>
#include <sound/sound.h>

#include <game/player.h>
#include <game/bomb_spawner.h>
#include <game/coin_spwaner.h>

using namespace engine::core;

int main(){
  
   auto engine_tpl = engine::core::Init();
   if(engine_tpl.IsError()){
      fprintf(stderr, "Error %s\n", engine_tpl.err.error_message);
      return-1;
   }

   auto x = render::opengl::texture::TextureFromFile("./assets/man.jpg", true);
  
  

   if(x.IsError()){
      puts(x.err.error_message);
      return -1;

   }
   auto player = Player();
   auto render_player = RenderProperty( std::move(x.val));
   player.AddProperty(render_player);
    engine::sound::PlayTempSound("./assets/GAME.mp3");
  // c.SetSize({8, 8});
   engine::input::RegisterKeyAction('W', [&player ](){
      //  c.AddDistance({1, 0});
      player.AddDistance({0, 0.064});
      engine::sound::PlayTempSound("./assets/jump.mp3");
      // auto pos = c.GetPosition();
      // printf("Position is at x=%i y=%i\n", pos.x, pos.y);
   });

   engine::input::RegisterKeyAction('D', [&player ](){
      //  c.AddDistance({1, 0});
      if(player.GetPosition().x > 15) return;
      player.AddDistance({0.04, 0});
     

      // auto pos = c.GetPosition();
      // printf("Position is at x=%i y=%i\n", pos.x, pos.y);
   });
   engine::input::RegisterKeyAction('A', [&player ](){
      //  c.AddDistance({1, 0});
      if(player.GetPosition().x < -15) return;
      player.AddDistance({-0.04, 0});
     

      // auto pos = c.GetPosition();
      // printf("Position is at x=%i y=%i\n", pos.x, pos.y);
   });

   auto g = GravityProperty();
   player.AddProperty(g);
   
   Instanciate(&player);

   int xu= 0;
     int score=0;
   auto col = ColliderProperty([&score](GameObject* o, GameObject*d){
       //printf("COllision! %i\n", xu++);
       if(d->GetType() == "BOMB"){
         puts("GAME ENDED!");
          engine::sound::PlayTempSound("./assets/bomb.mp3");
         exit(0);
       }
       if(d->GetType() == "COIN"){
         score++;
         printf("Score is %i\n", score);
         engine::sound::PlayTempSound("./assets/cha.mp3");
         d->SetType("OTHER");
       }
   });
   player.AddProperty(col);

   auto bomb_texture = render::opengl::texture::TextureFromFile("./assets/bomb.jpg", true);
   auto bomb_render = engine::core::RenderProperty( std::move(bomb_texture.val));
   auto b = Bomb();
   auto b_g = engine::core::GravityProperty(true);
    b.AddProperty(b_g);
    b.SetPosition({0, 10});
    b.AddProperty(bomb_render);
   auto bomb_spwn = BombSpwaner(b);
   Instanciate(&bomb_spwn);
   
   auto coin_texture = render::opengl::texture::TextureFromFile("./assets/money.jpg", true);
   auto coin_render = engine::core::RenderProperty( std::move(coin_texture.val));
   auto c = Coin();
   auto c_g = engine::core::GravityProperty(true);
    c.AddProperty(c_g);
    c.SetPosition({0, 10});
    c.AddProperty(coin_render);
    c.SetType("COIN");
 
   auto coin_spwn = CoinSpwaner(c);
   b.SetType("BOMB");
   Instanciate(&coin_spwn);

   puts("HERE\n");
   // c.AddDistance({10, 10});
   engine::core::SetWorldBackground("./assets/bkg.jpg");
   setInterval([&b]() {
            printf("Spawning bomb\n");
            b.SetPosition({(float)getRandomInt(-15, 15), 15});
            Instanciate(&b);
   }, 5000);
   setInterval([&c]() {
           // printf("Spawning coin\n");
           
            c.SetPosition({(float)getRandomInt(-15, 15), 15});
            c.SetType("COIN");
            Instanciate(&c);
   }, 4000);
      
   auto main_loop_tpl = engine::core::MainLoop();
   if(main_loop_tpl.IsError()){
      printf("Error in main loop %s\n", main_loop_tpl.err.error_message);
   }
   engine::core::Dealloc();
}
#include <core/game_object.h>
#include <core/core.h>
#include "bomb.h"
#include <util/util.h>
#include <vector>


class BombSpwaner : public engine::core::GameObject{
     Bomb m_bomb;
     bool m_started = false;
     void Update() noexcept{
         //for(int i=0;i< 3;i++){
            
            //Instanciate(&m_bomb);
         //}
  
     
        // Set an interval to print a message every second


     }
     std::vector<Bomb> m_bombs{};
     public:
     BombSpwaner(Bomb b) : m_bomb(b){
    //    m_bomb.SetPosition({0, 0});
        Instanciate(&m_bomb);
         
     }
};
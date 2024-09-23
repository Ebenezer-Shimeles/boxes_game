#include <core/game_object.h>
#include <core/core.h>
#include "coin.h"
#include <util/util.h>
#include <vector>


class CoinSpwaner : public engine::core::GameObject{
     Coin m_coin;
     bool m_started = false;
     void Update() noexcept{



     }
     std::vector<Coin> m_coins{};
     public:
     CoinSpwaner(Coin b) : m_coin(b){
    //    m_coin.SetPosition({0, 0});
        Instanciate(&m_coin);
         
     }
};
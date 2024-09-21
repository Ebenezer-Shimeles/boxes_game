#include <core/game_object.h>

#include <cstdio>
using namespace engine::core;


GameObject::GameObject(){
    puts("Game object constructed\n");
    m_id = "#GO" + m_count;
    m_count++;
}

void engine::core::Property::Update(const engine::core::GameObject&){
    
}

void engine::core::GameObject::Update() noexcept{
    printf("Update called on GameObject Id %s\n", m_id.c_str());
    for(auto& prop: m_properties){
        prop.Update(*this);
    }
}
void engine::core::GameObject::AddProperty(const Property& prop) noexcept{
   m_properties.push_back(prop);
}


bool engine::core::GameObject::operator==(const GameObject& other){
    return this->m_id == other.m_id;
}

int32_t engine::core::GameObject::m_count =0;
#include <core/game_object.h>
#include <gl_call.h>

#include <cstdio>
#include <memory>
using namespace engine::core;


Property::Property(){

}

GameObject::GameObject(){
    puts("Game object constructed\n");
    m_id = "#GO" + m_count;
    m_id += '\0';
    m_count++;
}

void engine::core::Property::Update(const engine::core::GameObject&){
     printf("Updating Property\n");
} 

void engine::core::GameObject::Update() noexcept{
    printf("Update called on GameObject Id %s\n", m_id.c_str());
    for(auto& prop: m_properties){
     //   printf("Update going to be called on prop\n");
        prop->Update(*this);
    }
}
void engine::core::GameObject::AddProperty( Property& prop) noexcept{
   m_properties.push_back(&prop);
}


bool engine::core::GameObject::operator==(const GameObject& other){
    return this->m_id == other.m_id;
}

int32_t engine::core::GameObject::m_count =0;

engine::core::RenderProperty::RenderProperty( Texture&& t) : Property(){
  
   printf("Moving to renderpoperty\n");
   printf("m_texture has this to 0x%x\n", &m_texture);
//    m_texture = (Texture&&)t;
   m_texture.m_id = t.m_id;
   t.m_id = 0;

}

void engine::core::RenderProperty::Update(const engine::core::GameObject& object){
    printf("RenderPropety is drawing!\n");
    m_texture.Bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
   
}
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

void engine::core::Property::Update( engine::core::GameObject&){
     //printf("Updating Property\n");
     
} 
void engine::core::GravityProperty::Update( engine::core::GameObject& obj) {
    obj.AddVelocity({0.0, -0.00007});
    //obj.GetAccleration();
   
}
engine::vector::Vector2 engine::core::GameObject::GetPosition() const  noexcept{
    return m_pos;
}
engine::vector::Vector2 engine::core::GameObject::GetAccleration() const noexcept{
    return m_accleration;
}
engine::vector::Vector2 engine::core::GameObject::GetVelocity() const noexcept{
    return m_velocity;
}

Size engine::core::GameObject::GetSize() const noexcept{
    return m_size;
}



void engine::core::GameObject::SetVelocity(const vector::Vector2 velo)noexcept{
    m_velocity = velo;
}
void engine::core::GameObject::SetPosition(const vector::Vector2 pos)noexcept{
    m_pos = pos; 
}
void engine::core::GameObject::SetAccleration(const vector::Vector2 acc)noexcept{
    m_accleration = acc;
}
void engine::core::GameObject::Update() noexcept{
   // printf("Update called on GameObject Id %s\n", m_id.c_str());
    m_pos.x += m_accleration.x * (0.5) + m_velocity.x;
    m_pos.y += m_accleration.y * (0.5) + m_velocity.y;

    m_velocity.x += m_accleration.x;
    m_velocity.y += m_accleration.y;

    for(auto& prop: m_properties){
     //   printf("Update going to be called on prop\n");
        prop->Update(*this);
    }
}
void engine::core::GameObject::AddProperty( Property& prop) noexcept{
   m_properties.push_back(&prop);
}

void engine::core::GameObject::AddAcclerate( const vector::Vector2& obj) noexcept{
    m_accleration.x += obj.x;
    m_accleration.y += obj.y;
}

void engine::core::GameObject::AddVelocity( const vector::Vector2& obj) noexcept{
    m_velocity.x += obj.x;
    m_velocity.y += obj.y;
}


void GameObject::AddDistance( const vector::Vector2& val) noexcept{
    m_pos.x += val.x;
    m_pos.y += val.y;
}
void engine::core::GameObject::SetSize(const Size& sz) noexcept{
    m_size = sz;
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

void engine::core::RenderProperty::Update( engine::core::GameObject& object){
    //printf("RenderPropety is drawing!\n");
    m_texture.Bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
   
}
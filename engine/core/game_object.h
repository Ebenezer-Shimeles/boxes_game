#include <string>
#include <vector>
#include <functional>

#include <vector/vector2.h>
#include <render/opengl/texture/texture.h>


#pragma once
using namespace render::opengl::texture;
namespace engine::core
{
    extern engine::error::EngineVal<void> MainLoop() noexcept;
    class GameObject;
    class Property{
        public:
           Property();
        
        protected:
            virtual void Update( engine::core::GameObject&);
            friend GameObject;
    };
    class GravityProperty: public Property{
        public:
           GravityProperty(bool dont = false, float acc=0.01) : m_acc(acc){
             this->m_dont = dont;
           }
        private:
            float m_acc;
            bool m_dont = false;
            void Update(  engine::core::GameObject&) override;

    };

    class RenderProperty : public Property{
        public:
            RenderProperty(Texture&& text);
        private:
            Texture  m_texture = Texture();
            void Update( engine::core::GameObject&) override;

    };
    class ColliderProperty : public Property{
        private:
            void Update( engine::core::GameObject&) override;
            std::function<void(GameObject *me, GameObject* other)> m_OnCollide;
        public:
            ColliderProperty(std::function<void(GameObject *me, GameObject* other)> func) :m_OnCollide(func){}
    };
    struct  Size{
         float width,height;
    };
    class GameObject{
        public:
            GameObject();
             bool operator==(const GameObject&);
             void AddProperty( Property&) noexcept;
             
             void SetVelocity(const vector::Vector2) noexcept;
             void SetPosition(const vector::Vector2) noexcept;
             void SetAccleration(const vector::Vector2) noexcept;
             void SetSize(const Size&) noexcept;
             void AddDistance( const vector::Vector2&) noexcept;
             void AddAcclerate( const vector::Vector2&) noexcept;
             void AddVelocity( const vector::Vector2&) noexcept;

             Size GetSize() const noexcept;
             vector::Vector2 GetAccleration() const noexcept;
             vector::Vector2 GetPosition() const noexcept;
             vector::Vector2 GetVelocity() const noexcept;

             std::string GetId() const{return m_id;}
             std::string GetType() const{ return m_type;}
             void SetType( const std::string& t)  {m_type=t;}
        private:
           std::string m_id;
           std::string m_type;
           vector::Vector2 m_pos = {0, 0};
           vector::Vector2 m_velocity ={0, 0};
           vector::Vector2 m_accleration ={0, 0};
           Size m_size = {1,1};

           std::vector<Property*> m_properties;

          
           static int32_t m_count;

        protected:
            virtual void Update() noexcept;
            

            friend engine::error::EngineVal<void> engine::core::MainLoop() noexcept;
            
    };
} 

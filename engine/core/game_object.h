#include <string>
#include <vector>

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
            virtual void Update(const engine::core::GameObject&);
            friend GameObject;
    };

    class RenderProperty : public Property{
        public:
            RenderProperty(Texture&& text);
        private:
            Texture  m_texture = Texture();
            void Update(const engine::core::GameObject&) override;

    };
    class GameObject{
        public:
            GameObject();
             bool operator==(const GameObject&);
             void AddProperty( Property&) noexcept;
        private:
           std::string m_id;
           
           vector::Vector2 m_pos;
           vector::Vector2 m_velocity;
           vector::Vector2 accleration;

           std::vector<Property*> m_properties;

          
           static int32_t m_count;

        protected:
            virtual void Update() noexcept;
            

            friend engine::error::EngineVal<void> engine::core::MainLoop() noexcept;
            
    };
} 

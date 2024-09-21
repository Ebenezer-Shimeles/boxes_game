#include <string>
#include <vector>

#include <vector/vector2.h>
#include <render/opengl/texture/texture.h>
using namespace render::opengl::texture;
namespace engine::core
{
    
    class GameObject;
    class Property{
        
        
        protected:
            virtual void Update(const engine::core::GameObject&);
            friend GameObject;
    };

    class RenderProperty : Property{
        private:


            Texture  x;
            void Update(const engine::core::GameObject&) override;

    };
    class GameObject{
        public:
            GameObject();
             bool operator==(const GameObject&);
        private:
           std::string m_id;
           
           vector::Vector2 m_pos;
           vector::Vector2 m_velocity;
           vector::Vector2 accleration;

           std::vector<Property> m_properties;

          
           static int32_t m_count;

        protected:
            virtual void Update() noexcept;
            void AddProperty(const Property&) noexcept;


            
    };
} 

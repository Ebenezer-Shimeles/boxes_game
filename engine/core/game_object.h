#include <string>
#include <vector>
#pragma once
#include <vector/vector2.h>
#include <core/property.h>
namespace engine::core
{
    class GameObject{
        private:
           std::string m_id;
           
           vector::Vector2 m_pos;
           vector::Vector2 m_velocity;
           vector::Vector2 accleration;

           std::vector<Property> m_properties;

        protected:
            virtual void Update();
            void AddProperty(const Property&);

            
    };
} 

#pragma once
#include <core/game_object.h>
#include <texture/texture.h>

namespace engine::core{

    class Property{
        protected:
            virtual void Update(const GameObject&);
    };

    class RenderProperty : Property{
        private:
            render::opengl::texture::Texture m_texture;
            void Update(const GameObject&) override;
    };
}


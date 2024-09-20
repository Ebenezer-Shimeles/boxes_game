#include <vector/vector2.h>
#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>
namespace engine::render::opengl::camera{
   class Camera{
       private:
           Camera() = delete;
           
           static glm::vec3 m_camera_pos;

           
       public:
           static void LookAt(const engine::vector::Vector2&  ) noexcept;
           
           static const glm::vec3& GetCameraPos() noexcept;

           static glm::highp_mat4 GetLookAtMatrix() noexcept;
   };
 
   
}
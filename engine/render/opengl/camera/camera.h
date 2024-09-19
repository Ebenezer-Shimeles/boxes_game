#include <vector/vector2.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/gtc/matrix_transform.hpp>
namespace engine::render::opengl::camera{
   class Camera{
       private:
           Camera();
           static Camera m_instance;
           glm::vec3 m_camera_pos = glm::vec3(0, 0, -3);

           
       public:
           void LookAt(const engine::vector::Vector2&  ) noexcept;
           static const Camera&  GetInstance() noexcept;
           const glm::vec3& GetCameraPos() noexcept;

           glm::mat4x4 GetLookAtMatrix() noexcept;
   };

}
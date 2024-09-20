#include <camera/camera.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
using namespace engine::render::opengl::camera;



glm::vec3 Camera::m_camera_pos  = glm::vec3(0, 0, -3);
void Camera::LookAt(const engine::vector::Vector2& pos ) noexcept{
    Camera::m_camera_pos = glm::vec3(pos.x, pos.y, 0);
}

const glm::vec3& Camera::GetCameraPos() noexcept{
    return m_camera_pos;
}

glm::highp_mat4 Camera::GetLookAtMatrix() noexcept{
    const glm::vec3 dist(0, 0, 1.0);
    const glm::vec3 z_axis(0, 0, 1.0);
    return glm::lookAt(GetCameraPos(), GetCameraPos() + dist,  z_axis);
}
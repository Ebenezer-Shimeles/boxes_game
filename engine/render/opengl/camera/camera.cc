#include <camera/camera.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
using namespace engine::render::opengl::camera;


Camera::Camera(){}

void Camera::LookAt(const engine::vector::Vector2& pos ) noexcept{
    m_camera_pos = glm::vec3(pos.x, pos.y, 0);
}
const engine::render::opengl::camera::Camera&  Camera::GetInstance() noexcept{
    return engine::render::opengl::camera::Camera::m_instance;
}
const glm::vec3& Camera::GetCameraPos() noexcept{
    return m_camera_pos;
}

glm::mat4x4 Camera::GetLookAtMatrix() noexcept{
    const glm::vec3 dist(0, 0, 1.0);
    const glm::vec3 z_axis(0, 0, 1.0);
    return glm::lookAt(GetCameraPos(), GetCameraPos() + dist,  z_axis);
}
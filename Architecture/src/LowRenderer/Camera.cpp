#include <glm/gtc/matrix_transform.hpp>

#include <LowRenderer/Camera.h>
#include <Context/Window.h>

using namespace LowRenderer;

Camera::Camera(GAMEOBJECT_INIT_PARAMS) : GAMEOBJECT_INIT(Camera),
m_projection(glm::perspective(glm::radians(90.f), 1280 / 720.f, 1.0f, 10.0f))
{
}


Camera::~Camera()
{
}

void Camera::UseOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_projection = glm::ortho(left,right,bottom,top,zNear,zFar);
}

void Camera::UsePerspective(float fov, float aspect, float zNear, float zFar)
{
	m_projection = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::GetView() const
{
	return glm::inverse(GetComponent<Physics::Transform>()->GetTransform());
}

const glm::mat4& Camera::GetProjection() const
{
	return m_projection;
}
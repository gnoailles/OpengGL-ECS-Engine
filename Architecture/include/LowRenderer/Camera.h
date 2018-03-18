#pragma once
#include "ECS/Entity/GameObject.h"

namespace LowRenderer
{
	class Camera : public GameObject<Camera>
	{
	private:
		glm::mat4 m_projection;
	public:
		Camera(GAMEOBJECT_INIT_PARAMS);
		~Camera();

		void UseOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
		void UsePerspective(float fov, float aspect, float zNear, float zFar);

		glm::mat4 GetView() const;
		const glm::mat4& GetProjection() const;
	};
}

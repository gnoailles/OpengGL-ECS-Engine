#pragma once
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "ECS/Component/Component.h"

namespace Physics
{
	class Transform : public ECS::Component<Transform>
	{
	private:
		glm::mat4 m_translation, m_scaling;
		glm::quat m_rotation;
		glm::vec3 m_position, m_scale, m_orientation;
		bool m_hasChanged;
	public:
		Transform(COMPONENT_INIT_PARAMS);
		~Transform();

		void operator=(const Transform& p_other);

		void SetTransform(const Transform& p_other);

		void Translate(const float x, const float y, const float z);
		void Translate(const glm::vec3 &p_dir);

		void SetPosition(const float x, const float y, const float z);
		void SetPosition(const glm::vec3 &p_pos);

		void SetXPosition(const float &p_pos);
		void SetYPosition(const float &p_pos);
		void SetZPosition(const float &p_pos);

		void Rotate(float x, float y, float z);
		void Rotate(const glm::vec3 &p_rotation);

		void SetOrientation(const float x, const float y, const float z);
		void SetOrientation(const glm::vec3& p_rotation);

		void LookAt(const glm::vec3& p_targetPosition);

		void Scale(float p_scale);
		void Scale(float x, float y, float z);
		void Scale(const glm::vec3& p_scale);

		void SetScale(float x, float y, float z);
		void SetScale(const glm::vec3& p_scale);

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetScale() const;
		const glm::vec3& GetOrientation() const;

		glm::vec3 Up();
		glm::vec3 Right();
		glm::vec3 Forward();

		const glm::mat4& GetTranslation();
		const glm::mat4 GetRotation();
		const glm::mat4& GetScaling();
		const glm::mat4 GetTransform();

		bool hasChanged() const;
	};
}

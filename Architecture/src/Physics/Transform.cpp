#include <glm/gtc/matrix_transform.hpp>
#include <Physics/Transform.h>

using namespace Physics;

Transform::Transform(COMPONENT_INIT_PARAMS):
	COMPONENT_INIT(Transform), 
	m_scale(1.f,1.f,1.f), m_hasChanged(true)
{
}

Transform::~Transform()
{
}

void Transform::operator=(const Transform& p_other)
{
	this->SetTransform(p_other);
}

void Transform::SetTransform(const Transform& p_other)
{
	this->m_position	= p_other.m_position;
	this->m_scale		= p_other.m_scale;
	this->m_orientation = p_other.m_orientation;

	this->m_translation = p_other.m_translation;
	this->m_scaling		= p_other.m_scaling;
	this->m_rotation	= p_other.m_rotation;

	this->m_hasChanged	= p_other.m_hasChanged;
}

void Transform::Translate(const float x, const float y, const float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
	m_hasChanged = true;
}
void Transform::Translate(const glm::vec3& p_dir)
{
	m_position += p_dir;
	m_hasChanged = true;
}

void Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	m_hasChanged = true;
}

void Transform::SetPosition(const glm::vec3& p_pos)
{
	m_position = p_pos;
	m_hasChanged = true;
}


void Transform::SetXPosition(const float& p_pos)
{
	m_position.x = p_pos;
	m_hasChanged = true;
}

void Transform::SetYPosition(const float& p_pos)
{
	m_position.y = p_pos;
	m_hasChanged = true;
}

void Transform::SetZPosition(const float& p_pos)
{
	m_position.z = p_pos;
	m_hasChanged = true;
}


void Transform::Rotate(float x, float y, float z)
{
	m_orientation.x += x;
	m_orientation.y += y;
	m_orientation.z += z;
	m_hasChanged = true;
}

void Transform::Rotate(const glm::vec3& p_rotation)
{
	m_orientation += p_rotation;
	m_hasChanged = true;
}

void Transform::SetOrientation(const float x, const float y, const float z)
{
	m_orientation.x = x;
	m_orientation.y = y;
	m_orientation.z = z;
	m_hasChanged = true;
}

void Transform::SetOrientation(const glm::vec3& p_rotation)
{
	m_orientation = p_rotation;
	m_hasChanged = true;
}

void Transform::LookAt(const glm::vec3& p_targetPosition)
{
	m_rotation = glm::toQuat(glm::lookAt(m_position, p_targetPosition, Up()));
	m_orientation = glm::eulerAngles(m_rotation);
}


void Transform::Scale(float n)
{
	m_scale *= n;
	m_hasChanged = true;
}

void Transform::Scale(float x, float y, float z)
{
	m_scale.x *= x;
	m_scale.y *= y;
	m_scale.z *= z;
	m_hasChanged = true;
}

void Transform::Scale(const glm::vec3& p_scale)
{
	m_scale.x *= p_scale.x;
	m_scale.y *= p_scale.y;
	m_scale.z *= p_scale.z;
	m_hasChanged = true;
}

void Transform::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
	m_hasChanged = true;
}

void Transform::SetScale(const glm::vec3& p_scale)
{
	m_scale = p_scale;
	m_hasChanged = true;
}

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

const glm::vec3& Transform::GetOrientation() const
{
	return m_orientation;
}

glm::vec3 Transform::Up()
{
	glm::mat4 transform = GetTransform();
	return transform[1];
}

glm::vec3 Transform::Right()
{
	glm::mat4 transform = GetTransform();
	return transform[0];
}

glm::vec3 Transform::Forward()
{
	glm::mat4 transform = GetTransform();
	return -transform[2];
}

const glm::mat4& Transform::GetTranslation()
{
	if (m_hasChanged)
	{
		m_translation = glm::translate(glm::mat4(1.0f), m_position);
	}
	return m_translation;
}

const glm::mat4 Transform::GetRotation()
{
	if (m_hasChanged)
	{
		m_rotation = glm::quat(m_orientation);
	}
	return glm::toMat4(m_rotation);
}

const glm::mat4& Transform::GetScaling()
{
	if (m_hasChanged)
	{
		m_scaling = glm::scale(glm::mat4(1.0f), m_scale);
	}
	return m_scaling;
}

const glm::mat4 Transform::GetTransform()
{
	return GetTranslation() * GetRotation() * GetScaling();
}

bool Transform::hasChanged() const
{
	return m_hasChanged;
}

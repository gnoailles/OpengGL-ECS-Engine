#pragma once
#include <Core/Maths/vec3.h>
#include <Core/Maths/vec2.h>

namespace LowRenderer
{
	class Vertex
	{
	private:
		Core::Maths::vec3f m_position;
		Core::Maths::vec3f m_normal;
		Core::Maths::vec2f m_textureCoordinate;
	public:
		Vertex(const Core::Maths::vec3f& p_position = Core::Maths::vec3f(), const Core::Maths::vec3f& p_normal = Core::Maths::vec3f(), const Core::Maths::vec2f& p_textureCoordinate = Core::Maths::vec2f(0,0));
		Vertex(const Core::Maths::vec3f& p_position, const Core::Maths::vec2f& p_textureCoordinate);

		Core::Maths::vec3f& Position();
		const Core::Maths::vec3f& Position() const;
		Core::Maths::vec3f& Normal();
		const Core::Maths::vec3f& Normal() const;
		Core::Maths::vec2f& TextureCoordinate();
		const Core::Maths::vec2f& TextureCoordinate() const;
	};
}

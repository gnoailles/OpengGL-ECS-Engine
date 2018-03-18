#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ECS/System/System.h>
#include <LowRenderer/Camera.h>

namespace Rendering
{
	class Renderer : public ECS::System<Renderer>
	{
	private:
		GLFWwindow* m_window;
		LowRenderer::Camera* m_activeCamera;

		void InitOpenGL();
	public:
		Renderer(GLFWwindow* p_window);
		~Renderer();

		void PreUpdate(double dt) override;

		void Update(double dt) override;

		void PostUpdate(double dt) override;

		void SetCamera(LowRenderer::Camera* p_camera);
	};
}

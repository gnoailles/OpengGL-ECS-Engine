#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Resources/ResourcesManager.h>
#include <Resources/Scene.h>

namespace LowRenderer {
	class Camera;
}

namespace Graphics
{
	class Window
	{
	private:
		GLFWwindow* m_window;
		Resources::ResourcesManager m_resources;
		Resources::Scene* m_scene;
		LowRenderer::Camera* m_camera;;

		void InitGLFW();
	public:

		Window();
		~Window();

		void Init();
		void Run();
		void Close();

		static void FramebufferSize(GLFWwindow* window, int width, int height);
	};
}

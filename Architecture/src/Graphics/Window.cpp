#include <sstream>

#include <Graphics/Window.h>

#include <ECS/Engine.h>

#include <ECS/Managers/EntityManager.h>
#include <ECS/Managers/SystemManager.h>

#include <Rendering/Renderer.h>

#include "ECS/Entity/Player.h"
#include "LowRenderer/Mesh.h"

#include "Core/Debug/Log.h"
#include "Utils/Timer.h"

using namespace Graphics;
using namespace ECS;
using namespace Resources;
using namespace Core::Debug;
using namespace Rendering;
using namespace LowRenderer;
using namespace Utils;

void Window::InitGLFW()
{
	if (glfwInit())
	{
		m_window = glfwCreateWindow(1280, 720, "OpenGL Architecture", nullptr, nullptr);
		if (m_window) 
			return;

		LOG(Core::Debug::Log::Error(), "GLFW Error creating window");
		glfwTerminate();
	}
	LOG(Core::Debug::Log::Error(), "GLFW Error initializing glfw");
		
}

Window::Window(): m_window(nullptr), m_scene(nullptr), m_camera(nullptr)
{
}


Window::~Window()
{
}

void Window::Init()
{
	InitGLFW();
	ECS::ECS_Engine = new ECS::ECSEngine;
	m_scene = ECS::ECS_Engine->GetSystemManager()->AddSystem<Scene>();
	Renderer* renderer = ECS::ECS_Engine->GetSystemManager()->AddSystem<Renderer>(this->m_window);
	m_camera = &m_scene->AddGameObject<Camera>(nullptr);
	renderer->SetCamera(m_camera);
}

void Window::Run()
{
	m_camera->GetComponent<Physics::Transform>()->SetPosition(glm::vec3(0.f, 0.f, -1.f));
	m_camera->GetComponent<Physics::Transform>()->LookAt(glm::vec3(0.0f, 0.0f, 1.0f));
	m_camera->UseOrtho(-2, 2, -1.5, 1.5, 1, 10);

	auto& cube = m_scene->AddGameObject<Mesh>(nullptr,
					m_resources.LoadModel("cube", "cube.obj"),
					&m_resources.LoadShader("texture","texture.glsl"),
					&m_resources.LoadTexture("paint", "paint047.jpg"));

	auto& cube2 = m_scene->AddGameObject<Mesh>((Core::DataStructure::Graph*)(&cube),
					m_resources.GetModel("cube"),
					&m_resources.GetShader("texture"),
					&m_resources.GetTexture("paint"));

	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		Timer::PreUpdate();

		while (Timer::accumulator >= Timer::fixedDeltaTime)
		{
			//FixedUpdate()
			Timer::FixedUpdate();
			cube2.GetComponent<Physics::Transform>()->Rotate(0.01f, 0.f, 0.f);
			cube2.GetComponent<Physics::Transform>()->SetPosition(1.0f, 0.f, 1.f);

			cube.GetComponent<Physics::Transform>()->Rotate(0.f, 0.01f, 0.0f);
			cube.GetComponent<Physics::Transform>()->SetPosition(-1.f, 0.0f, 1.0f);
		}
		ECS::ECS_Engine->Update(Timer::deltaTime.count());
	}
}

void Window::Close()
{
	delete ECS_Engine;
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::FramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

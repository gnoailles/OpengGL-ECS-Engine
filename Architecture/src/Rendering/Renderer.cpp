#include <sstream>

#include <Rendering/Renderer.h>

#include <Graphics/Window.h>
#include <ECS/Managers/ComponentManager.h>

#include <Rendering/RenderableComponent.h>
#include "LowRenderer/MaterialComponent.h"

#include <Inputs/InputSystem.h>

#include "Core/Debug/Log.h"
#include "ECS/Engine.h"
#include "Resources/Model.h"

namespace LowRenderer {
	class MaterialComponent;
}

using namespace Rendering;

Renderer::Renderer(GLFWwindow* p_window) : m_window(p_window)
{
	InitOpenGL();
}


Renderer::~Renderer()
{
}

void Renderer::InitOpenGL()
{
	glfwMakeContextCurrent(m_window);

	const GLenum err = glewInit();
	if (err == GLEW_OK)
	{
		LOG(Core::Debug::Log::Info(), "OpenGL Version:" << glGetString(GL_VERSION));
		glfwSetKeyCallback(m_window, InputSystem::HandleInputs);
		glfwSetFramebufferSizeCallback(m_window, Graphics::Window::FramebufferSize);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	else
	{
		LOG(Core::Debug::Log::Error(), "GLEW Error initializing glew :" << glewGetErrorString(err));
	}
}


void Renderer::PreUpdate(double dt)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::PostUpdate(double dt)
{
	glfwSwapBuffers(m_window);
}

void Renderer::SetCamera(LowRenderer::Camera* p_camera)
{
	m_activeCamera = p_camera;
}

void Renderer::Update(double dt)
{
	if (m_activeCamera)
	{
		ECS::ComponentManager* Cm = ECS::ECS_Engine->GetComponentManager();
		for (auto renderableIt = Cm->GetComponentContainer<RenderableComponent>()->GetTComponentContainer().begin();
			renderableIt != Cm->GetComponentContainer<RenderableComponent>()->GetTComponentContainer().end();
			++renderableIt)
		{
			RenderableComponent* renderable = reinterpret_cast<RenderableComponent*>(renderableIt->second.get());

			if (renderable->IsActive())
			{
				Resources::Model* model = renderable->GetModel();
				if (model)
				{
					LowRenderer::MaterialComponent* material = Cm->GetComponent<LowRenderer::MaterialComponent>(renderable->GetOwnerID());
					if (material)
					{
						Resources::Shader* shader = material->GetShader();
						if (shader)
						{
							Physics::Transform* transform = Cm->GetComponent<Physics::Transform>(renderable->GetOwnerID());
							shader->Bind();

							shader->SetUniform("u_model", transform->GetTransform());
							shader->SetUniform("u_view", m_activeCamera->GetView());
							shader->SetUniform("u_proj", m_activeCamera->GetProjection());

							shader->SetUniform("u_viewPos", m_activeCamera->GetComponent<Physics::Transform>()->GetPosition());

							shader->SetUniform("u_light.position", Core::Maths::vec3f(1.2f, 1.0f, 2.0f));
							shader->SetUniform("u_light.ambient", Core::Maths::vec3f(0.2f, 0.2f ,0.2f));
							shader->SetUniform("u_light.diffuse", Core::Maths::vec3f(0.5f, 0.5f, 0.5f));
							shader->SetUniform("u_light.specular", Core::Maths::vec3f(1.0f, 1.0f, 1.0f));

							shader->SetUniform("u_material.ambient", material->GetAmbient());
							shader->SetUniform("u_material.diffuse", material->GetDiffuse());
							shader->SetUniform("u_material.specular", material->GetSpecular());
							shader->SetUniform("u_material.shininess", material->GetShininess());
						}
					}
					renderable->GetVertexArray().Bind();

					model->GetIndexBuffer().Bind();

					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glDrawElements(GL_TRIANGLES, model->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
				}
			}
		}
	}
	else
	{
		LOG(Core::Debug::Log::Error(), "No active camera set !");
	}
}

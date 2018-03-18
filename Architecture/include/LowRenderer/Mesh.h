#pragma once
#include <ECS/Entity/GameObject.h>

#include <Resources/Model.h>
#include "MaterialComponent.h"
#include "Rendering/RenderableComponent.h"

namespace LowRenderer
{
	class Mesh : public GameObject<Mesh>
	{
	public:
		Mesh(GAMEOBJECT_INIT_PARAMS, Resources::Model& p_model, Resources::Shader* p_shader = nullptr, Resources::Texture* p_texture = nullptr) : GAMEOBJECT_INIT(Mesh)
		{
			auto& render = AddComponent<Rendering::RenderableComponent>(&p_model);
			auto& model = AddComponent<MaterialComponent>(p_shader, p_texture);

		}
		~Mesh();
	};
}

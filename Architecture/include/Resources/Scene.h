#pragma once
#include "Core/DataStructure/Graph.h"
#include "ECS/System/System.h"
#include "Physics/Transform.h"
#include "ECS/Engine.h"
#include "ECS/Managers/EntityManager.h"
#include "ECS/Entity/GameObject.h"

namespace Resources
{
	class Scene : public ECS::System<Scene>, public Core::DataStructure::Graph
	{
	public:
		Scene();
		~Scene() override;

		
		template<class T, class... Args>
		T& AddGameObject(Graph* p_parent, Args&&... args)
		{
			Graph* parent = (p_parent) ? p_parent : this;
			GameObject<T>& entity = ECS::ECS_Engine->GetEntityManager()->CreateEntity<T>(parent,std::forward<Args>(args)...);

			return reinterpret_cast<T&>(entity);
		}

	};
}

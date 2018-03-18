#pragma once
#include <Physics/Transform.h>
#include <ECS/Entity/Entity.h>
#include "Core/DataStructure/Graph.h"

#define GAMEOBJECT_INIT_PARAMS const ECS::EntityID& p_id, ECS::ComponentManager* p_componentManager, Core::DataStructure::Graph_ptr& p_parent
#define GAMEOBJECT_INIT(Type) GameObject<Type>(p_id,p_componentManager, p_parent)


template<class T>
class GameObject : public ECS::Entity<T>, public Core::DataStructure::Graph
{
public:
	GameObject(GAMEOBJECT_INIT_PARAMS): ECS::Entity<T>(p_id, p_componentManager), Graph(p_parent)
	                                                                             
	{
		ECS::IEntity::AddComponent<Physics::Transform>();
	}

	virtual ~GameObject()
	{
	}

};

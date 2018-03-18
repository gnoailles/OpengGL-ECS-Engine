#include <ECS/Engine.h>

//#include "ECS/Event/EventHandler.h"

#include <ECS/Managers/EntityManager.h>
#include <ECS/Managers/ComponentManager.h>
#include <ECS/Managers/SystemManager.h>

#include "Utils/Timer.h"

namespace ECS
{

	ECSEngine::ECSEngine()
	{
		ECS_SystemManager = new SystemManager();
		ECS_ComponentManager = new ComponentManager();
		ECS_EntityManager = new EntityManager(this->ECS_ComponentManager);
	}

	ECSEngine::~ECSEngine()
	{
		delete ECS_EntityManager;
		ECS_EntityManager = nullptr;

		delete ECS_ComponentManager;
		ECS_ComponentManager = nullptr;

		delete ECS_SystemManager;
		ECS_SystemManager = nullptr;
	}

	void ECSEngine::Update(double tick_ms)
	{
		ECS_SystemManager->Update(tick_ms);
	}

	EntityManager* ECSEngine::GetEntityManager() const
	{
		return ECS_EntityManager;
	}

	ComponentManager* ECSEngine::GetComponentManager() const
	{
		return ECS_ComponentManager;
	}

	SystemManager* ECSEngine::GetSystemManager() const
	{
		return ECS_SystemManager;
	}
}

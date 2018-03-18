#pragma once

namespace ECS
{
	namespace Util
	{
		class Timer;
	}

	class EntityManager;
	class SystemManager;
	class ComponentManager;



	class ECSEngine
	{
		friend class IEntity;
		friend class IComponent;
		friend class ISystem;

	private:

		EntityManager*				ECS_EntityManager;
		ComponentManager*			ECS_ComponentManager;
		SystemManager*				ECS_SystemManager;


		ECSEngine(const ECSEngine&) = delete;
		ECSEngine& operator=(ECSEngine&) = delete;

	public:

		ECSEngine();

		~ECSEngine();

		void Update(double tick_ms);


		EntityManager* GetEntityManager() const;
		ComponentManager* GetComponentManager() const;
		SystemManager* GetSystemManager() const;
	};

	extern ECSEngine* ECS_Engine;
}

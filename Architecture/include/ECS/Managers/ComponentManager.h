#pragma once
#include <memory>
#include <unordered_map>

#include <ECS/Component/Component.h>
#include <Core/Debug/Assertion.h>
#include "Core/Debug/Log.h"

namespace ECS
{	
	using IComponent_ptr = std::shared_ptr<IComponent>;

	class ComponentManager
	{
	private:
		class IComponentContainer
		{
		public:
			virtual ~IComponentContainer()
			{}

//			virtual const char* GetEntityContainerTypeName() const = 0;
			virtual void DestroyComponent(const ComponentID& p_componentID) = 0;
		}; //IComponentContainer

		template<typename T>
		class ComponentContainer : public IComponentContainer
		{
			using TComponentContainer = std::unordered_map<ComponentID, std::shared_ptr<Component<T>>>;

		private:
			TComponentContainer m_typedContainer;

		public:
			ComponentContainer() {}
			TComponentContainer& GetTComponentContainer() { return m_typedContainer; }
			void DestroyComponent(const ComponentID& p_componentID) override
			{
				this->m_typedContainer.erase(p_componentID);
			}
		}; //ComponentContainer<T>

	private:
		using IComponentContainer_ptr = std::unique_ptr<IComponentContainer>;

		std::unordered_map<ComponentTypeID, IComponentContainer_ptr> m_componentTypedTables;
		std::unordered_map<ComponentID, IComponent_ptr> m_componentTable;
		std::unordered_map<EntityID, std::unordered_map<ComponentTypeID, ComponentID>> m_entityComponentTable;

	public:
		ComponentManager();
		~ComponentManager();

		template<typename T, typename ...Args>
		T& AddComponent(const EntityID& p_entityID, Args&&... p_params)
		{
			const ComponentTypeID CTID = T::COMPONENT_TYPE_ID;
			ComponentID newID = Utils::FamilyObjectID<IComponent>::Get();
			std::shared_ptr<T> newComponent = std::make_shared<T>(p_entityID, newID, std::forward<Args>(p_params)...);

			m_entityComponentTable[p_entityID][CTID] = newID;

			auto result = m_componentTable.try_emplace(newID, newComponent);
			ASSERT(result.second, "Error creating new Component !");

			auto result2 = GetComponentContainer<T>()->GetTComponentContainer().try_emplace(newID, newComponent);
			ASSERT(result2.second, "Error inserting Component in typed containers !");
			return *newComponent.get();
		}

		template<typename T>
		void RemoveComponent(const EntityID& p_entityID)
		{
			const ComponentTypeID CTID = T::COMPONENT_TYPE_ID;
			const ComponentID componentID = this->m_entityComponentTable.at(p_entityID).at(CTID);

			m_componentTypedTables[CTID]->DestroyComponent(p_entityID);
			m_componentTable.erase(componentID);
			m_entityComponentTable.at(p_entityID).erase(CTID);
		}

		void RemoveAllComponents(const size_t p_entityId);

		template<typename T>
		T* GetComponent(const EntityID p_entityID)
		{
			const ComponentTypeID CTID = T::COMPONENT_TYPE_ID;

			const ComponentID componentID = this->m_entityComponentTable.at(p_entityID).at(CTID);
			return reinterpret_cast<T*>(m_componentTable[componentID].get());
		}

		template<typename T>
		ComponentContainer<T>* GetComponentContainer()
		{
			try
			{
				ComponentTypeID EID = T::COMPONENT_TYPE_ID;

				auto result = this->m_componentTypedTables.find(EID);
				if (result != m_componentTypedTables.end())
					return reinterpret_cast<ComponentContainer<T>*>(result->second.get());

				auto result2 = this->m_componentTypedTables.try_emplace(EID, std::make_unique<ComponentContainer<T>>());
				ASSERT(result2.second, "Failed to create EntityContainer<T>!");
				return reinterpret_cast<ComponentContainer<T>*>(result2.first->second.get());
			}
			catch (Core::Debug::Assertion e)
			{
				e.LogError();
				return nullptr;
			}
		}
	};
}


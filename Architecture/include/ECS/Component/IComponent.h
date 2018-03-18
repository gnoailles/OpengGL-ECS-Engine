#pragma once
#include <ECS/Types.h>

namespace ECS
{

	class IComponent
	{
		friend class ComponentManager;
	protected:
		EntityID m_owner_ID;
		ComponentID m_component_ID;
		bool m_enabled;
	public:
		IComponent(const EntityID& p_owner_ID,
				const ComponentID& p_componentID) : 
					m_owner_ID(p_owner_ID),
					m_component_ID(p_componentID), 
					m_enabled(true)
		{
		}

		virtual ~IComponent() = default;

		inline const ComponentID& GetComponentID() const { return this->m_component_ID; }
		inline const EntityID& GetOwnerID() const { return this->m_owner_ID; }

		virtual const ComponentTypeID GetComponentTypeID() const = 0;


		// COMPARE ENTITIES

		inline bool operator==(const IComponent& p_other) const { return this->m_component_ID == p_other.m_component_ID; }
		inline bool operator!=(const IComponent& p_other) const { return this->m_component_ID != p_other.m_component_ID; }
		inline bool operator==(const IComponent* p_other) const { return this->m_component_ID == p_other->m_component_ID; }
		inline bool operator!=(const IComponent* p_other) const { return this->m_component_ID != p_other->m_component_ID; }


		inline void SetActive(const bool p_active) { this->m_enabled = p_active; }
		inline bool IsActive() const { return this->m_enabled; }
	};
}

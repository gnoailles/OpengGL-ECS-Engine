#pragma once

namespace ECS {
	class IEntity;
	class IComponent;
	class ISystem;
}

namespace Utils
{
	template<typename T>
	class FamilyTypeID
	{
	private:
		static TypeID s_count;
	public:
		template<typename U>
		static const TypeID Get()
		{
			static const TypeID STATIC_TYPE_ID = s_count++;
			return STATIC_TYPE_ID;
		}

		static const TypeID Get()
		{
			return s_count;
		}

	};

	template<typename T>
	class FamilyObjectID
	{
	private:
		static TypeID s_count;
	public:

		static const TypeID Get()
		{
			return s_count++;
		}
	};


	TypeID FamilyTypeID<ECS::IEntity>::s_count = 0u;
	TypeID FamilyTypeID<ECS::IComponent>::s_count = 0u;
	TypeID FamilyTypeID<ECS::ISystem>::s_count = 0u;

	TypeID FamilyObjectID<ECS::IEntity>::s_count = 0u;
	TypeID FamilyObjectID<ECS::IComponent>::s_count = 0u;
	TypeID FamilyObjectID<ECS::ISystem>::s_count = 0u;
}

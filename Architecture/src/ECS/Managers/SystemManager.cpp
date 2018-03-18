#include <functional>
#include <map>
#include <algorithm>

#include <ECS/Managers/SystemManager.h>
#include "Utils/algorithm.h"

using namespace ECS;

SystemManager::SystemManager()
{
}


ECS::SystemManager::~SystemManager()
{
}


void SystemManager::Update(double dt_ms)
{
	for (ISystem_ptr system : this->m_systemWorkOrder)
	{
		// increase interval since last update
		system->m_timeSinceLastUpdate = dt_ms;

		// check systems update state
		system->m_needsUpdate = (system->m_updateInterval < 0.0f) || ((system->m_updateInterval > 0.0f) && (system->m_timeSinceLastUpdate > system->m_updateInterval));

		if (system->m_enabled == true && system->m_needsUpdate == true)
		{
			system->PreUpdate(dt_ms);
		}
	}

	for (ISystem_ptr system : this->m_systemWorkOrder)
	{
		if (system->m_enabled == true && system->m_needsUpdate == true)
		{
			system->Update(dt_ms);

			// reset interval
			system->m_timeSinceLastUpdate = 0.0f;
		}
	}

	for (ISystem_ptr system : this->m_systemWorkOrder)
	{
		if (system->m_enabled == true && system->m_needsUpdate == true)
		{
			system->PostUpdate(dt_ms);
		}
	}
}


void SystemManager::UpdateSystemWorkOrder()
{

	const size_t systemsCount = this->m_systemDependencyTable.size();


	// create index array
	std::vector<int> indices(systemsCount);
	for (int i = 0; i < systemsCount; ++i)
		indices[i] = i;

	// determine vertex-groups
	std::vector<std::vector<SystemTypeID>>	vertexGroups;
	std::vector<SystemPriority>				groupPriority;

	while (!indices.empty())
	{
		SystemTypeID index = indices.back();
		indices.pop_back();

		if (index == -1)
			continue;

		std::vector<SystemTypeID> group;
		std::vector<SystemTypeID> member;

		SystemPriority currentGroupPriority = LOWEST_SYSTEM_PRIORITY;
		member.push_back(index);

		while (!member.empty())
		{
			index = member.back();
			member.pop_back();

			for (int i = 0; i < indices.size(); ++i)
			{
				if (indices[i] != -1 && (this->m_systemDependencyTable[i][index] == true || this->m_systemDependencyTable[index][i] == true))
				{
					member.push_back(i);
					indices[i] = -1;
				}
			}

			group.push_back(index);


			ISystem_ptr sys = this->m_systemTable[index];
			currentGroupPriority = std::max((sys != nullptr ? sys->m_priority : NORMAL_SYSTEM_PRIORITY), currentGroupPriority);
		}

		vertexGroups.push_back(group);
		groupPriority.push_back(currentGroupPriority);
	}

	const size_t vertexGroupsCount = vertexGroups.size();

	// do a topological sort on groups w.r.t. to groups priority!
	std::vector<int> vertex_states(systemsCount, 0);

	std::multimap<SystemPriority, std::vector<SystemTypeID>> sortedVertexGroups;


	for (int i = 0; i < vertexGroupsCount; ++i)
	{
		auto g = vertexGroups[i];

		std::vector<SystemTypeID> order;

		for (int j = 0; j < g.size(); ++j)
		{
			if (vertex_states[g[j]] == 0)
				Utils::algo::depthFirstSearch<SystemTypeID>(g[j], vertex_states, this->m_systemDependencyTable, order);
		}

		std::reverse(order.begin(), order.end());

		sortedVertexGroups.insert(std::pair<SystemPriority, std::vector<SystemTypeID>>(std::numeric_limits<SystemPriority>::max() - groupPriority[i], order));
	}



	LOG(Core::Debug::Log::Info(),"Update system work order:");

		// re-build system work order
	this->m_systemWorkOrder.clear();
	for (auto group : sortedVertexGroups)
	{
		for (auto m : group.second)
		{
			ISystem_ptr sys = this->m_systemTable[m];
			if (sys != nullptr)
			{
				this->m_systemWorkOrder.push_back(sys);
				LOG(Core::Debug::Log::Info(), "\t" << sys->GetSystemTypeName());
			}
		}
	}
}

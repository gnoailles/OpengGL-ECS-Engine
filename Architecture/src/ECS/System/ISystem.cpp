#include <ECS/System/ISystem.h>

using namespace ECS;

ISystem::ISystem(SystemPriority p_priority, double p_updateInterval_ms) :
	m_priority(p_priority),
	m_updateInterval(p_updateInterval_ms),
	m_enabled(true)
{}

ISystem::~ISystem()
{}
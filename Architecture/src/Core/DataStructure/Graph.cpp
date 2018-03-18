#include <Core/DataStructure/Graph.h>

using namespace Core::DataStructure;

Graph::Graph(Graph* p_parent) : m_parent(p_parent)
{
	if (this->m_parent)
		p_parent->AddChild(this);
}

Graph::~Graph()
{
}

const Graph* Graph::CreateChild()
{
	return m_childs.emplace_back(this);
}

void Graph::AddChild(Graph* p_child)
{
	m_childs.push_back(p_child);
	p_child->m_parent = this;
}

size_t Graph::ChildCount() const
{
	return m_childs.size();
}

const std::list<Graph*>& Graph::GetChilds() const
{
	return m_childs;
}

const Graph* Graph::GetChild(const unsigned int p_index)
{
	return *std::next(m_childs.begin(), p_index);
}

const Graph* Graph::GetLastChild()
{
	return m_childs.back();
}

void Graph::RemoveChild(Graph* p_child)
{
	m_childs.remove(p_child);
}

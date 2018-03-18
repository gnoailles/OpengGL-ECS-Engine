#pragma once
#include <list>

namespace Core
{
	namespace DataStructure
	{
		class Graph
		{
		protected:
			std::list<Graph*> m_childs;
			Graph* m_parent;
		public:
			Graph(Graph* p_parent);
			virtual ~Graph();

			const Graph* CreateChild();
			void AddChild(Graph* p_child);

			size_t ChildCount() const;

			const std::list<Graph*>& GetChilds() const;
			const Graph* GetChild(const unsigned int p_index);
			const Graph* GetLastChild();

			void RemoveChild(Graph* p_child);
		};
		using Graph_ptr = Graph*;
	}
}

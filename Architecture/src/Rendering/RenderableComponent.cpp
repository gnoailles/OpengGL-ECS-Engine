#include "Rendering/RenderableComponent.h"

using namespace Rendering;

Rendering::RenderableComponent::RenderableComponent(COMPONENT_INIT_PARAMS, Resources::Model * p_model) :
	COMPONENT_INIT(RenderableComponent), m_model(p_model)
{
	if (m_model) m_model->InitBuffers(m_va, m_layout);
}

void RenderableComponent::SetModel(Resources::Model* p_model)
{
	if (p_model)
	{
		m_model = p_model;
		m_model->InitBuffers(m_va, m_layout);
	}
}

Resources::Model* RenderableComponent::GetModel() const
{
	return m_model;
}

Resources::Buffers::VertexArray& RenderableComponent::GetVertexArray()
{
	return m_va;
}

Resources::Buffers::VertexBufferLayout& RenderableComponent::GetVertexLayout()
{
	return m_layout;
}

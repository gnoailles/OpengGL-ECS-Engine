#pragma once
#include "ECS/Component/Component.h"
#include "Resources/Buffers/VertexArray.h"
#include "Resources/Model.h"

namespace Rendering
{
	class RenderableComponent : public ECS::Component<RenderableComponent>
	{
	private:
		Resources::Buffers::VertexArray m_va;
		Resources::Buffers::VertexBufferLayout m_layout;
		Resources::Model* m_model;
	public:
		RenderableComponent(COMPONENT_INIT_PARAMS, Resources::Model* p_model = nullptr);

		inline void SetModel(Resources::Model* p_model);
		Resources::Model* GetModel() const;

		Resources::Buffers::VertexArray& GetVertexArray();
		Resources::Buffers::VertexBufferLayout& GetVertexLayout();
	};
}

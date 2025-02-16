#include "RenderComponent.h"
#include "Renderer.h"

void dae::RenderComponent::Update()
{

}

void dae::RenderComponent::FixedUpdate()
{

}

void dae::RenderComponent::Render() const
{
	if (m_texture != nullptr)
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_texture = texture;
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::BaseComponent::Type dae::RenderComponent::GetType() const
{
    return Type::Render;
}

#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* owner)
	: m_owner(owner), m_position{0, 0, 0}
{
}

void dae::RenderComponent::Update(float deltaTime)
{
	if (m_owner)
	{
		m_position = m_owner->GetWorldPosition() * deltaTime;
	}
	
}

void dae::RenderComponent::FixedUpdate()
{

}

void dae::RenderComponent::Render() const
{
	if (m_texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, m_position.x, m_position.y);
	}
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_texture = texture;
}





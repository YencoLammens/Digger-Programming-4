#include "SpriteRenderStateComponent.h"


dae::SpriteRenderStateComponent::SpriteRenderStateComponent(GameObject* owner)
	: BaseComponent(owner)
{
}

void dae::SpriteRenderStateComponent::SetRotation(float angle) 
{  
	m_rotation = angle;
}
float dae::SpriteRenderStateComponent::GetRotation() const 
{ 
	return m_rotation; 
}

void dae::SpriteRenderStateComponent::SetFlipX(bool flip) 
{ 
	m_flipX = flip; 
}
bool dae::SpriteRenderStateComponent::GetFlipX() const 
{ 
	return m_flipX; 
}

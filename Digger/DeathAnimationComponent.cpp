#include "DeathAnimationComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::DeathAnimationComponent::DeathAnimationComponent(GameObject* owner)
	:BaseComponent(owner)
{
}

void dae::DeathAnimationComponent::Update(float deltaTime)
{
	if (m_hasDied)
	{
		DeathAnimation(deltaTime);
		
	}
	

}

void dae::DeathAnimationComponent::DeathAnimation(float deltaTime)
{
	GetOwner()->GetComponent<RenderComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Gravestone.png"));
	m_animationTimer += deltaTime;

	if (m_animationTimer >= m_animationDuration)
	{
		m_animationTimer = 0.0f;
		GetOwner()->GetComponent<RenderComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Digger.png"));
		m_hasDied = false;
	}
	
}

void dae::DeathAnimationComponent::PlayerDeath()
{
	m_hasDied = true;
}

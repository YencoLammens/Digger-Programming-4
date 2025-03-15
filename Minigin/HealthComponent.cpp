#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner)
	:BaseComponent(owner), m_currentHealth(m_startHealth)
{
}

void dae::HealthComponent::Update(float elapsedSec)
{
}

int dae::HealthComponent::GetHealth() const
{
	return m_currentHealth;
}

void dae::HealthComponent::LoseHeart()
{
	//Seeing as the digger has 3 hearts, this subtracts one and sets the state to dead so when implemented the game CAN reset
	m_currentHealth -= 1;
	m_isDead = true;
}

void dae::HealthComponent::Resurrect()
{
	//Resurrect the player with their diminshed life for when a new life starts, as  long as above 0
	if (m_currentHealth > 0) m_isDead = false;
}



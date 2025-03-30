#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner)
	:BaseComponent(owner)
{
	m_currentHealth = m_startHealth;
}

void dae::HealthComponent::Update(float)
{
}

int dae::HealthComponent::GetHealth() const
{
	return m_currentHealth;
}

void dae::HealthComponent::LoseHeart()
{
	//Works but doesn't update the display
	//Seeing as the digger has 3 hearts, this subtracts one and sets the state to dead so when implemented the game CAN reset
	if (m_currentHealth > 0)
	{
		--m_currentHealth;
		GetOwner()->NotifyObservers(Event(EventId::HEALTH_CHANGED));
	}
	//To be implemented
	m_isDead = true;
}

void dae::HealthComponent::Resurrect()
{
	//Resurrect the player with their diminshed life for when a new life starts, as  long as above 0
	if (m_currentHealth > 0) m_isDead = false;
}



#include "HealthComponent.h"
#include "MoveComponent.h"
dae::HealthComponent::HealthComponent(GameObject* owner)
	:BaseComponent(owner)
{
	m_currentHealth = m_startHealth;
}

void dae::HealthComponent::Update(float deltaTime)
{
	if (m_isDead)
	{
		m_deathTimer += deltaTime;
	}

	if (m_deathTimer >= m_deathDuration)
	{
		Resurrect();
	}
	
}

void dae::HealthComponent::FixedUpdate(float)
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
		GetOwner()->NotifyObservers(GameEvent(EventId::HEALTH_CHANGED));
	}
	//To be implemented
}

void dae::HealthComponent::Death()
{
	m_isDead = true;
	LoseHeart();
	GetOwner()->GetComponent<MoveComponent>()->DisableMovement();
}

void dae::HealthComponent::Resurrect()
{
	//Resurrect the player with their diminshed life for when a new life starts, as  long as above 0
	if (m_currentHealth > 0) 
	{
		
		m_isDead = false;
		GetOwner()->GetComponent<MoveComponent>()->EnableMovement();
	}
}



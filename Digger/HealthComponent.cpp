#include "HealthComponent.h"
#include "MoveComponent.h"
#include "Event.h"
#include "GameObject.h"
#include "FireballLauncherComponent.h"
#include "ServiceLocator.h"
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
		if (m_deathTimer >= m_deathDuration)
		{
			Resurrect();
		}
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
	if (m_currentHealth > 0)
	{
		--m_currentHealth;
		GetOwner()->NotifyObservers(GameEvent(EventId::HEALTH_CHANGED));
	}
	
}

void dae::HealthComponent::Death()
{
	m_isDead = true;
	LoseHeart();
	GetOwner()->GetComponent<MoveComponent>()->DisableMovement();
	GetOwner()->GetComponent<FireballLauncherComponent>()->SetCanFire(false);
	ServiceLocator::get_SoundSystem().Play(0, 0.2f);
	ServiceLocator::get_SoundSystem().Play(1, 0.2f);
	
}

void dae::HealthComponent::Resurrect()
{
	//Resurrect the player with their diminshed life for when a new life starts, as  long as above 0
	if (m_currentHealth > 0) 
	{
		
		m_isDead = false;
		GetOwner()->GetComponent<MoveComponent>()->EnableMovement();
		GetOwner()->GetComponent<FireballLauncherComponent>()->SetCanFire(true);
	}
}
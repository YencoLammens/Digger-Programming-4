#include "EnemyComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "DeathAnimationComponent.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Fireball.h"

dae::EnemyComponent::EnemyComponent(GameObject* owner, GameObject* player)
	:BaseComponent(owner), m_player(player)
{
}

void dae::EnemyComponent::Update(float deltaTime)
{
	m_timerBeforeTransformation += deltaTime;

	if (m_timerBeforeTransformation >= m_timerDuration && m_currentType == EnemyType::Nobbin)
	{
		FormChange(EnemyType::Hobbin);
		m_timerBeforeTransformation = 0;
	
	}
	else if (m_timerBeforeTransformation >= m_timerDuration / 2 && m_currentType == EnemyType::Hobbin)
	{
		FormChange(EnemyType::Nobbin);
		m_timerBeforeTransformation = 0;
		
	}

}

void dae::EnemyComponent::FixedUpdate(float)
{
	if (m_player != nullptr)
	{
		if (utils::IsOverlapping(GetOwner()->GetComponent<HitboxComponent>()->GetHitbox(), m_player->GetComponent<HitboxComponent>()->GetHitbox()) && m_hasAttacked == false)
		{
			m_hasAttacked = true;
			m_player->NotifyObservers(GameEvent(EventId::PLAYER_DIED));
			m_player->GetComponent<HealthComponent>()->Death();
			m_player->GetComponent<DeathAnimationComponent>()->PlayerDeath();
			GetOwner()->MarkForDeletion();
			return;
		}
	}
}

void dae::EnemyComponent::FormChange(EnemyType newType)
{
	m_currentType = newType;

	if (newType == EnemyType::Hobbin)
	{
		GetOwner()->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Hobbin.png"));
	}
	else if (newType == EnemyType::Nobbin)
	{
		GetOwner()->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Nobbin.png"));
	}
}

void dae::EnemyComponent::OnNotify(const GameEvent& event, GameObject* go)
{
	if (event.Id == EventId::COLLIDED)
	{
		if (utils::IsOverlapping(GetOwner()->GetComponent<HitboxComponent>()->GetHitbox(), go->GetComponent<HitboxComponent>()->GetHitbox()))
		{
			if (go->GetComponent<Fireball>())
			{
				go->MarkForDeletion();
			}
			GetOwner()->MarkForDeletion();
		}
	}
}

#include "EnemyComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "DeathAnimationComponent.h"
#include "HealthComponent.h"

dae::EnemyComponent::EnemyComponent(GameObject* owner, GameObject* player, float speed)
	:BaseComponent(owner), m_player(player), m_speed(speed)
{
}

void dae::EnemyComponent::Update(float)
{
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

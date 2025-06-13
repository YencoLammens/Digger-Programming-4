#include "EnemyComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "DeathAnimationComponent.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Fireball.h"
#include "ServiceLocator.h"

dae::EnemyComponent::EnemyComponent(GameObject* owner, GameObject* player)
	:BaseComponent(owner), m_player(player)
{
	GetOwner()->AddObserver(this);
}

dae::EnemyComponent::~EnemyComponent()
{
	GetOwner()->RemoveObserver(this);
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
			KillEnemy();
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

void dae::EnemyComponent::KillEnemy()
{
	GetOwner()->NotifyObservers(GameEvent(EventId::ENEMY_DIED));
	GetOwner()->RemoveObserver(this);
	GetOwner()->MarkForDeletion();
	ServiceLocator::get_SoundSystem().Play(7, 0.3f);
}

void dae::EnemyComponent::OnNotify(const GameEvent& event, GameObject*)
{
	if (event.Id == EventId::COLLIDED)
	{
		
		KillEnemy();
		//Will kill it if it collides with anything, not just the fireball, bad
		
	}
}

#include "Fireball.h"
#include "utils.h"
#include "GameObject.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "EnemyComponent.h"
#include "Event.h"
#include "ServiceLocator.h"

dae::Fireball::Fireball(GameObject* owner, const glm::vec3& startPos, const glm::vec3& direction) 
	: BaseComponent(owner), m_startPosition(startPos), m_direction(direction)
{
	m_position = startPos ;
	ServiceLocator::get_SoundSystem().Play(2, 0.3f);
}

void dae::Fireball::Update(float deltaTime)
{
	m_position += m_direction * deltaTime * m_speed;
	GetOwner()->GetTransform()->SetLocalPosition(m_position);

	m_lifetimer += deltaTime;

	if (m_lifetimer >= m_lifetime)
	{
		KillProjectile();
	}

}

void dae::Fireball::FixedUpdate(float)
{
	
}

void dae::Fireball::OnNotify(const GameEvent& event, GameObject*)
{
	if (event.Id == EventId::COLLIDED)
	{
		ServiceLocator::get_SoundSystem().Play(3, 0.3f);
		KillProjectile();
		return;
	}


}

void dae::Fireball::KillProjectile()
{
	GetOwner()->MarkForDeletion();
	GetOwner()->RemoveObserver(this);
}


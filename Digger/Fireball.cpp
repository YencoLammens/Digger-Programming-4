#include "Fireball.h"
#include "utils.h"
#include "GameObject.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "EnemyComponent.h"
#include "Event.h"

dae::Fireball::Fireball(GameObject* owner, const glm::vec3& startPos, const glm::vec3& direction) 
	: BaseComponent(owner), m_startPosition(startPos), m_direction(direction)
{
	m_position = startPos ;
}

void dae::Fireball::Update(float deltaTime)
{
	m_position += m_direction * deltaTime * m_speed;
	GetOwner()->GetTransform()->SetLocalPosition(m_position);
	std::cout << m_position.x << ", " << m_position.y << ", " << m_position.z << std::endl;

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
		KillProjectile();
	}
}

void dae::Fireball::KillProjectile()
{
	this->MarkForDeletion();
}


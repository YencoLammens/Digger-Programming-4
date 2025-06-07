#include "MoveComponent.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* owner, float speed)
	:BaseComponent(owner), m_speed(speed), m_direction(0, 0, 0)
{
	
}

void dae::MoveComponent::Update(float elapsedSec)
{
	glm::vec3 newPosition = glm::vec3{ GetOwner()->GetTransform()->GetWorldPosition().x + m_direction.x * m_speed * elapsedSec, GetOwner()->GetTransform()->GetWorldPosition().y + m_direction.y * m_speed * elapsedSec, 0 };
	GetOwner()->GetTransform()->SetLocalPosition(newPosition);
}

void dae::MoveComponent::FixedUpdate(float)
{
}

void dae::MoveComponent::SetDirectionX(float directionX)
{
	m_direction.x = directionX;
}
void dae::MoveComponent::SetDirectionY(float directionY)
{
	m_direction.y = directionY;
}






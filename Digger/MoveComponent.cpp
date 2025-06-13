#include "MoveComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include <cmath> // std::fmod, std::round
#include "SpriteRenderStateComponent.h"

dae::MoveComponent::MoveComponent(GameObject* owner, float speed)
	: BaseComponent(owner), m_speed(speed), m_direction({1,0,0}), m_pendingDirection(0.f), m_previousDirection(m_direction)
{
}

void dae::MoveComponent::Update(float deltaTime)
{
	if (!m_canMove) return;

	auto* transform = GetOwner()->GetTransform();
	glm::vec3 currentPosition = transform->GetWorldPosition();

	if (!m_isMoving)
	{
		// Snap to grid
		currentPosition.x = std::round(currentPosition.x / m_tileSize) * m_tileSize;
		currentPosition.y = std::round(currentPosition.y / m_tileSize) * m_tileSize;
		transform->SetLocalPosition(currentPosition);

		// If no direction, stop
		if (m_pendingDirection == glm::vec3{ 0.f })
		{
			m_direction = glm::vec3{ 0.f };
			return;
		}

		// Calculate tentative target
		glm::vec3 target = currentPosition + m_pendingDirection * m_tileSize;

		// Check bounds
		if (target.x < m_movementBounds.x || target.x > m_movementBounds.x + m_movementBounds.width - m_tileSize ||
			target.y < m_movementBounds.y || target.y > m_movementBounds.y + m_movementBounds.height - m_tileSize)
		{
			// Outside bounds — cancel movement
			m_pendingDirection = glm::vec3{ 0.f };
			m_direction = glm::vec3{ 0.f };
			return;
		}

		m_direction = m_pendingDirection;
		m_targetPosition = target;
		m_isMoving = true;
	}

	// Move toward target
	glm::vec3 directionToTarget = glm::normalize(m_targetPosition - currentPosition);
	glm::vec3 velocity = directionToTarget * m_speed * deltaTime;

	if (glm::length(m_targetPosition - currentPosition) <= glm::length(velocity))
	{
		transform->SetLocalPosition(m_targetPosition);
		m_isMoving = false;
	}
	else
	{
		transform->SetLocalPosition(currentPosition + velocity);
	}
}

void dae::MoveComponent::SetDirection(const glm::vec3& direction)
{
	m_pendingDirection = direction;
	m_previousDirection = m_direction; // Store previous direction for potential use+

	auto* spriteState = GetOwner()->GetComponent<SpriteRenderStateComponent>();
	if (spriteState)
	{
		if (m_canMove)
		{
			if (direction.x < 0.f)
			{
				spriteState->SetFlipX(true);
				spriteState->SetRotation(0.f);
			}
			else if (direction.x > 0.f)
			{
				spriteState->SetFlipX(false);
				spriteState->SetRotation(0.f);
			}
			else if (direction.y < 0.f)
			{
				spriteState->SetFlipX(false);
				spriteState->SetRotation(270.f);
			}
			else if (direction.y > 0.f)
			{
				spriteState->SetFlipX(false);
				spriteState->SetRotation(90.f);
			}
		}
		else
		{
			spriteState->SetFlipX(false);
			spriteState->SetRotation(0.f);
		}
		
	}
}

void dae::MoveComponent::DisableMovement()
{
	m_canMove = false;
}

void dae::MoveComponent::EnableMovement()
{
	m_canMove = true;
}



//void dae::MoveComponent::SetDirection(const glm::vec3& direction)
//{
//	// Prevent diagonals
//	if ((direction.x != 0.f && direction.y != 0.f) || direction.z != 0.f)
//		return;
//
//	m_pendingDirection = direction;
//
//	// stop immediately if direction is zero
//	if (direction == glm::vec3{ 0.f })
//		m_direction = glm::vec3{ 0.f };
//}
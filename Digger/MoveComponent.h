#pragma once
#include "glm.hpp"
#include "BaseComponent.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		explicit MoveComponent(GameObject* owner, float speed = 200.0f);

		void Update(float deltaTime) override;
		void FixedUpdate(float) override {}

		void SetDirection(const glm::vec3& direction);
		const glm::vec3 GetDirection() const { return m_direction; };
		const glm::vec3 GetPreviousDirection() const { return m_previousDirection; };
		void DisableMovement();
		void EnableMovement();

	private:
		float m_speed;
		glm::vec3 m_direction;
		glm::vec3 m_pendingDirection;
		glm::vec3 m_previousDirection;
		const float m_tileSize{ 32.f};
		glm::vec3 m_targetPosition{ 0.f }; // where we're moving to
		bool m_isMoving = false;
		bool m_canMove = true;
	};
}


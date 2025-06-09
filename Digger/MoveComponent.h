#pragma once
#include "glm.hpp"
#include "BaseComponent.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		explicit MoveComponent(GameObject* owner, float speed = 100.0f);

		void Update(float deltaTime) override;
		void FixedUpdate(float) override {}

		void SetDirection(const glm::vec3& direction);

	private:
		float m_speed;
		glm::vec3 m_direction;
		glm::vec3 m_pendingDirection;
		const float m_tileSize{ 32.f};
		glm::vec3 m_targetPosition{ 0.f }; // where we're moving to
		bool m_isMoving = false;
	};
}


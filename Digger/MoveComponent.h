#pragma once
#include "glm.hpp"
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class MoveComponent : public BaseComponent
	{
	public:
		explicit MoveComponent(GameObject* owner, float speed = 100.0f);

		void Update(float elapsedSec) override;
		void FixedUpdate(float) override;
		void SetDirectionX(float directionX);
		void SetDirectionY(float directionY);

	private:
		float m_speed;
		glm::vec3 m_direction;
	};

}


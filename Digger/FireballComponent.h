#pragma once
#include "BaseComponent.h"
#include <glm.hpp>


namespace dae
{
	class FireballComponent : public BaseComponent
	{
	public:
		FireballComponent(GameObject* owner, const glm::vec3& direction, float speed);
		void Update(float deltaTime) override;
		void FixedUpdate(float) override;

	private:
		glm::vec3 m_direction;
		float m_speed{ 300.0f }; // Speed in pixels per second
		//float m_lifetime{ 2.0f }; // Lifetime in seconds, if needed
		//float m_elapsedTime{ 0.0f }; // Time since the fireball was created, if needed
	};
}



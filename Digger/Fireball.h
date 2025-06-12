#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <glm.hpp>

namespace dae
{
	class Fireball : public BaseComponent, public Observer
	{
	public:
		Fireball(GameObject* owner, const glm::vec3& startPos, const glm::vec3& direction);
		void Update(float deltaTime) override;
		void FixedUpdate(float /*fixedTimeStep*/) override;
	/*	void HandleCollider(GameObject* other);*/
		void OnNotify(const GameEvent& event, GameObject* go) override;
		void KillProjectile();
	private:
		const glm::vec3 m_startPosition;
		glm::vec3 m_direction;
		glm::vec3 m_position;
		const float m_speed{ 200.0f };
		float m_lifetime{ 5.0f };
		float m_lifetimer{ 0.0f };
	};
}



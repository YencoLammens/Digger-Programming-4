#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(GameObject* owner);
		void Update(float deltaTime) override;
		void FixedUpdate(float) override;
		int GetHealth() const;
		void LoseHeart();
		void Death();
		void Resurrect();
	private:
		int m_currentHealth;
		const int m_startHealth{ 3 };
		bool m_isDead{ false };

		float m_deathTimer{0};
		const float m_deathDuration{ 2.0f };
	};
}


#pragma once
#include "BaseComponent.h"


namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(GameObject* owner);
		void Update(float elapsedSec) override;
		int GetHealth() const;
		void LoseHeart();
		void Resurrect();

	private:
		int m_currentHealth;
		const int m_startHealth{ 3 };
		bool m_isDead{ false };
	};
}


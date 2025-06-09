#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class DeathAnimationComponent : public BaseComponent
	{
	public:
		DeathAnimationComponent(GameObject* owner);

		void Update(float deltaTime) override;
		void FixedUpdate(float) override {};
		void DeathAnimation(float deltaTime);
		void PlayerDeath();
	private:
		const float m_animationDuration{ 2.0f };
		float m_animationTimer{0};
		bool m_hasDied{ false };

	};

}

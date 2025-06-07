#pragma once
#include "BaseComponent.h"
#include "Rectf.h"

namespace dae
{
	class HitboxComponent : public BaseComponent
	{
	public:
		HitboxComponent(GameObject* owner, float width, float height);
		void Update(float elapsedSec) override;
		void FixedUpdate(float fixedTimeStep) override;
		dae::Rectf GetHitbox() const;
	private:
		Rectf m_hitbox;
	};
}

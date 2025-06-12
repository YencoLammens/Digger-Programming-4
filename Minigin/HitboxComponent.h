#pragma once
#include "BaseComponent.h"
#include "Rectf.h"

namespace dae
{
	class HitboxComponent : public BaseComponent
	{
	public:
		HitboxComponent(GameObject* owner, float width, float height);
		~HitboxComponent() override;
		void Update(float deltaTime) override;
		void FixedUpdate(float fixedTimeStep) override;
		const dae::Rectf GetHitbox() const;
		void OnCollision(GameObject* other);
	private:
		Rectf m_hitbox;
	};
}

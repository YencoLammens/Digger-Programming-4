#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
#include <memory>

namespace dae
{
	class FireballComponent;
	class GameObject;

	class FireballLauncherComponent : public BaseComponent
	{
	public:
		FireballLauncherComponent(GameObject* owner);

		void Fire(const glm::vec3& direction);
		void Update(float deltaTime) override;
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void SetCanFire(bool canFire) { m_canFire = canFire; }
	private:
		//std::unique_ptr<GameObject> m_pFireball;
		float m_CooldownTime{ 5.0f };
		float m_TimeSinceLastFire{ 5.0f };
		bool m_canFire{ true };
		bool m_spriteNeedsUpdate{ false };

		void CreateFireball(const glm::vec3& direction);
	};
}
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

	private:
		//std::unique_ptr<GameObject> m_pFireball;
		float m_CooldownTime{ 1.0f };
		float m_TimeSinceLastFire{ 1.0f };

		void CreateFireball(const glm::vec3& direction);
	};
}
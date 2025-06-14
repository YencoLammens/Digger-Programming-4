#pragma once
#include "ColliderSystem.h"
#include "GameObject.h"


namespace dae
{
	class basic_ColliderSystem final : public ColliderSystem
	{
	public:

		~basic_ColliderSystem() = default;
		basic_ColliderSystem(const basic_ColliderSystem&) = delete;
		basic_ColliderSystem& operator=(const basic_ColliderSystem&) = delete;
		basic_ColliderSystem(basic_ColliderSystem&&) = delete;
		basic_ColliderSystem& operator=(basic_ColliderSystem&&) = delete;

		void FixedUpdate(float fixedTimeStep) override;
		void AddGOwithHitbox(GameObject* gameObject) override;
		void RemoveGOwithHitbox(GameObject* gameObject) override;

	private:
		std::vector<GameObject*> gameObjects;
	};

}
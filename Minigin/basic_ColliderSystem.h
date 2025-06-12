#pragma once
#include "ColliderSystem.h"
#include "GameObject.h"


namespace dae
{
	class basic_ColliderSystem final : public ColliderSystem
	{
	public:

		~basic_ColliderSystem() = default;

		void FixedUpdate(float fixedTimeStep) override;
		void AddGOwithHitbox(GameObject* gameObject) override;
		void RemoveGOwithHitbox(GameObject* gameObject) override;

	private:
		std::vector<GameObject*> gameObjects;
	};

}
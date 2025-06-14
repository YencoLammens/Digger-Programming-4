#pragma once
#include <vector>
#include "GameObject.h"

namespace dae
{
	class ColliderSystem
	{
		/*ColliderSystem() = default;
		ColliderSystem(const ColliderSystem& other) = delete;
		ColliderSystem(ColliderSystem&& other) = delete;
		ColliderSystem& operator=(const ColliderSystem& other) = delete;
		ColliderSystem& operator=(ColliderSystem&& other) = delete;*/


	public:
		virtual ~ColliderSystem() = default;
		ColliderSystem(const ColliderSystem&) = delete;
		ColliderSystem& operator=(const ColliderSystem&) = delete;
		ColliderSystem(ColliderSystem&&) = delete;
		ColliderSystem& operator=(ColliderSystem&&) = delete;

		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void AddGOwithHitbox(GameObject* gameObject) = 0;
		virtual void RemoveGOwithHitbox(GameObject* gameObject) = 0;

	protected:
		ColliderSystem() = default;

	};
}
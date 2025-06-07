#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PickupComponent : public BaseComponent
	{
	public:
		PickupComponent(GameObject* owner, int value);

		virtual void Update(float elapsedSec) = 0;
		virtual void FixedUpdate(float elapsedSec) = 0;
		virtual void OnPickup() = 0;
	private:
		int m_value;
	};
}

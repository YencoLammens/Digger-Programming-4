#pragma once
#include "PickupComponent.h"
namespace dae
{
	class EmeraldPickupComponent : public BaseComponent
	{
	public:
		EmeraldPickupComponent(GameObject* owner, GameObject* player);
		void Update(float elapsedSec) override;
		void FixedUpdate(float) override {}

		void OnPickup();

	private:
		const int m_value{ 25 };
		GameObject* m_player;
	};
}



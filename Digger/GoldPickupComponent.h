#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae
{
	class GoldPickupComponent : public BaseComponent
	{
	public:
		GoldPickupComponent(GameObject* owner, GameObject* player);
		void Update(float elapsedSec) override;
		void FixedUpdate(float) override {}

		void OnPickup();

	private:
		GameObject* m_player;
		bool m_hasBeenPickedUp{ false };
	};
}



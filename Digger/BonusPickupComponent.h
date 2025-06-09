#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae
{
	class BonusPickupComponent : public BaseComponent
	{
	public:
		BonusPickupComponent(GameObject* owner, GameObject* player);
		void Update(float deltaTime) override;
		void FixedUpdate(float) override {}

		void OnPickup();

	private:
		GameObject* m_player;
		bool m_hasBeenPickedUp{ false };
	};
}


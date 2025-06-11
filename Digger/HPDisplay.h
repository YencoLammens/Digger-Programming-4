#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <vector>

namespace dae
{
	class GameObject;

	class HPDisplay final : public BaseComponent, public Observer
	{
	public:
		explicit HPDisplay(GameObject* goUI);
		void Update(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void SetHeartIcons(const std::vector<GameObject*>& heartIcons);

		void OnNotify(const GameEvent& event, GameObject* go) override;

	private:
		std::vector<GameObject*> m_HeartIcons;
	};
}
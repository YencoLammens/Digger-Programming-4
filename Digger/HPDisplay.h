#pragma once
#include "Observer.h"
#include "BaseComponent.h"

namespace dae
{
	class HPDisplay : public Observer, public BaseComponent
	{
	public:
		HPDisplay(GameObject* goUI);
		void OnNotify(const GameEvent& event, GameObject* go) override;

		void Update(float) override {};
		void FixedUpdate(float) override {};


	private:
		GameObject* m_goUI;

	};
}


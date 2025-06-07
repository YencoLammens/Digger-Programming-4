#pragma once
#include "Observer.h"
#include "BaseComponent.h"
namespace dae
{
	class ScoreDisplay : public Observer, public BaseComponent
	{
	public:
		ScoreDisplay(GameObject* goUI);
		void OnNotify(const GameEvent& event, GameObject* go) override;

		void Update(float) override {};
		void FixedUpdate(float) override {};


	private:
		GameObject* m_goUI;

	};
}


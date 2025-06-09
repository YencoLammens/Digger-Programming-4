#pragma once
#include "BaseComponent.h"


namespace dae
{
	class EnemyComponent : public BaseComponent
	{

	public:
		explicit EnemyComponent(GameObject* owner, GameObject* player, float speed = 100.0f);
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		
	private:
		float m_speed;
		GameObject* m_player;
		bool m_hasAttacked{ false };
	};

}


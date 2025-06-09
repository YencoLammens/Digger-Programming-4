#pragma once
#include "BaseComponent.h"

namespace dae
{
	class EnemyComponent : public BaseComponent
	{

	public:
		explicit EnemyComponent(GameObject* owner, float speed = 100.0f);
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		
	private:
		float m_speed;
	};

}


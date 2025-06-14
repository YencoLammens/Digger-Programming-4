#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Event.h"

namespace dae
{
	enum class EnemyType
	{
		Nobbin,
		Hobbin
	};

	class EnemyComponent : public BaseComponent, public Observer
	{

	public:
		explicit EnemyComponent(GameObject* owner, GameObject* player);
		~EnemyComponent() override;
		EnemyComponent(const EnemyComponent&) = delete;
		EnemyComponent& operator=(const EnemyComponent&) = delete;
		EnemyComponent(EnemyComponent&&) = delete;
		EnemyComponent& operator=(EnemyComponent&&) = delete;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override;
		void OnNotify(const GameEvent& event, GameObject* go) override;
		void FormChange(EnemyType newType);
	private:
		float m_speed{100.0f};
		GameObject* m_player;
		bool m_hasAttacked{ false };
		float m_timerBeforeTransformation{ 0 };
		const float m_timerDuration{ 10.0f };
		EnemyType m_currentType{ EnemyType::Nobbin };
		void KillEnemy();

		

	};

}


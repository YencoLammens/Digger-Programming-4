#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae 
{
	class ScoreComponent : public BaseComponent, public Observer
	{
	public:
		ScoreComponent(GameObject* owner);
		void Update(float deltaTime) override;
		void FixedUpdate(float) override;
		int GetScore() const;
		void AddScore(int score);
		void ResetScore();

		void PickUpEmerald();
		void PickUpGold();
		void PickUpBonus();
		void HandleEnemyKilled();
		void OnNotify(const GameEvent& event, GameObject* go) override;
		//Implement methods for bonus mode
		//Implement event for when score reaches 20000 to gain an extra life for the player

	private:
		int m_score;

		const int m_emeraldScore		{ 25 };
		int	m_currentEmeraldStreak		{ 0 };
		const int m_emeraldMaxStreak	{ 8 };
		const int m_emeraldStreakScore	{ 250 };
		const int m_goldScore			{ 500 };
		const int m_enemyKilledScore	{ 250 }; //for when blasted or had a bag dropped on them
		const int m_bonusScore			{ 1000 };
		const int m_eatEnemyStartScore	{ 200 };
		int m_eatEnemyScore				{ 200 }; //not const cause it grows exponentially
		const int m_scoreToGainExtraLife{ 20000 };

		

	};
}


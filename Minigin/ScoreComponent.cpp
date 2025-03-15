#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner)
	:BaseComponent(owner), m_score(0)
{
}

void dae::ScoreComponent::Update(float elapsedSec)
{
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}

void dae::ScoreComponent::AddScore(int score)
{
	m_score += score;
}

void dae::ScoreComponent::ResetScore()
{
	m_score = 0;
}

void dae::ScoreComponent::PickUpEmerald()
{
	m_score += m_emeraldScore;
	if (m_currentEmeraldStreak == m_emeraldMaxStreak)
	{
		m_score += m_emeraldStreakScore;
		m_currentEmeraldStreak = 0;
	}
	++m_currentEmeraldStreak;
}

void dae::ScoreComponent::PickUpGold()
{
	m_score += m_goldScore;
}

void dae::ScoreComponent::HandleEnemyKilled()
{
	m_score += m_enemyKilledScore;
}


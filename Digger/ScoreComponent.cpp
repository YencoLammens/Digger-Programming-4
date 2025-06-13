#include "ScoreComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "ServiceLocator.h"

dae::ScoreComponent::ScoreComponent(GameObject* owner)
	:BaseComponent(owner)
{
	m_score = 0;
}

void dae::ScoreComponent::Update(float)
{
}

void dae::ScoreComponent::FixedUpdate(float)
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
	if (m_currentEmeraldStreak == m_emeraldMaxStreak - 1)
	{
		m_score += m_emeraldStreakScore;
		m_currentEmeraldStreak = 0;
	}
	++m_currentEmeraldStreak;
	GetOwner()->NotifyObservers(GameEvent(EventId::SCORE_CHANGED));
	ServiceLocator::get_SoundSystem().Play(4, 0.5f);
}

void dae::ScoreComponent::PickUpGold()
{
	m_score += m_goldScore;
	GetOwner()->NotifyObservers(GameEvent(EventId::SCORE_CHANGED));
	ServiceLocator::get_SoundSystem().Play(5, 0.5f);
}

void dae::ScoreComponent::PickUpBonus()
{
	m_score += m_bonusScore;
	GetOwner()->NotifyObservers(GameEvent(EventId::SCORE_CHANGED));
	ServiceLocator::get_SoundSystem().Play(6, 0.5f);
}

void dae::ScoreComponent::HandleEnemyKilled()
{
	m_score += m_enemyKilledScore;
	GetOwner()->NotifyObservers(GameEvent(EventId::SCORE_CHANGED));
}

void dae::ScoreComponent::OnNotify(const GameEvent& event, GameObject*)
{
	if (event.Id == EventId::ENEMY_DIED)
	{
		HandleEnemyKilled();
		if (m_score >= m_scoreToGainExtraLife)
		{
			//GetOwner()->NotifyObservers(GameEvent(EventId::SCORE_REACHED_500));
			//m_score = 0; // Reset score after gaining extra life
		}
		return;
	}
}



#pragma once
#include <cstdint>
#include "ServiceLocator.h"

namespace dae
{
	enum class EventId
	{
		HEALTH_CHANGED,
		SCORE_CHANGED,
		SCORE_REACHED_500,
		PLAYER_DIED,
		ENEMY_DIED,
		COLLIDED
	};

	struct Event
	{
		explicit Event(EventId id);
		virtual ~Event() = default;

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;
		Event(Event&&) = delete;
		Event& operator=(Event&&) = delete;
		const EventId Id;

		virtual void process() = 0;
	};

	struct GameEvent : Event
	{
		GameEvent(EventId eventId);
		void process() override;
	};
	struct SoundEvent : Event
	{
		SoundEvent(EventId eventId, sound_id , float volume);

		void process() override;

		sound_id m_soundId;
		float m_volume{ 1.0f };
	};

	//struct ColliderEvent : Event
	//{
	//	ColliderEvent(EventId eventId, GameObject* collidedObject);

	//	void process() override;
	//	
	//	//GameObject* m_gameObject{ nullptr };
	//};
}


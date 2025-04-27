#pragma once
#include <cstdint>
#include "ServiceLocator.h"

namespace dae
{
	enum class EventId
	{
		HEALTH_CHANGED,
		SCORE_CHANGED,
		SCORE_REACHED_500
	};

	struct Event
	{
		explicit Event(EventId id);
		virtual ~Event() = default;
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
		SoundEvent(EventId eventId, sound_id soundId, float volume);

		void process() override;

		sound_id m_soundId;
		float m_volume{ 1.0f };
	};
}


#pragma once
#include <cstdint>

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
		const EventId Id;
	};
}


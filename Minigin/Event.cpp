#include "Event.h"

dae::Event::Event(EventId id)
	: Id(id)
{
}

dae::SoundEvent::SoundEvent(EventId eventId,sound_id soundId, float volume)
	: Event(eventId), m_soundId(soundId), m_volume(volume)
{
}

void dae::SoundEvent::process()
{
	ServiceLocator::get_SoundSystem().Play(static_cast<sound_id>(Id), 1.0f);
}

dae::GameEvent::GameEvent(EventId eventId)
	: Event(eventId)
{
	
}

void dae::GameEvent::process()
{

}

//dae::ColliderEvent::ColliderEvent(EventId eventId, collider_id colliderId)
//	: Event(eventId), m_colliderId(colliderId)
//{
//}


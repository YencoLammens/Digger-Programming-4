#include "logging_SoundSystem.h"

dae::logging_SoundSystem::logging_SoundSystem(std::unique_ptr<SoundSystem>&& real_SoundSystem)
	: _real_SoundSystem(std::move(real_SoundSystem))
{

}

void dae::logging_SoundSystem::Play(const sound_id id, const float volume)
{
	_real_SoundSystem->Play(id, volume);
	
}

void dae::logging_SoundSystem::AddAudioClip(AudioClip* audioClip)
{
	_real_SoundSystem->AddAudioClip(audioClip);
}

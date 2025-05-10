#include "sdl_SoundSystem.h"

dae::sdl_SoundSystem::sdl_SoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 524) < 0)
	{
		throw std::runtime_error("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()));
	}
}

dae::sdl_SoundSystem::~sdl_SoundSystem()
{
	Mix_CloseAudio();
}

void dae::sdl_SoundSystem::Play(const sound_id soundId, const float volume)
{
	auto audioclip = audioClips[soundId];
	if (!audioclip->is_loaded())
	{
		audioclip->load();
	}
	audioclip->set_volume(volume);
	audioclip->play();
}

void dae::sdl_SoundSystem::AddAudioClip(AudioClip* audioClip)
{
	audioClips.push_back(audioClip);
}

#pragma once
#include <vector>
#include <SDL_mixer.h>
#include "AudioClip.h"

using sound_id = unsigned short;
namespace dae 
{
	class SoundSystem
	{
		/*SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;*/


	public:
		virtual ~SoundSystem() = default;
		SoundSystem(const SoundSystem&) = delete;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator=(SoundSystem&&) = delete;
		virtual void Play(const sound_id id, const float volume) = 0;


		virtual void AddAudioClip(AudioClip* audioClip) = 0;
	protected:
		SoundSystem() = default;
		std::vector<AudioClip*> audioClips;

	
	};
}



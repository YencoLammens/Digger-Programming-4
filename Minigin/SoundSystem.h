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
		virtual void Play(const sound_id id, const float volume) = 0;


		virtual void AddAudioClip(AudioClip* audioClip) = 0;
	protected:
		std::vector<AudioClip*> audioClips;

	
	};
}



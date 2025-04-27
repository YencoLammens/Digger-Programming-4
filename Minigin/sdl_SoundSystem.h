#pragma once
#include "SoundSystem.h"
#include "AudioClip.h"
namespace dae
{
	class sdl_SoundSystem final : public SoundSystem
	{
	public:
		sdl_SoundSystem();
		~sdl_SoundSystem() override;
		void Play(const sound_id soundId, const float volume) override;
		void AddAudioClip(AudioClip* audioClip) override;
		
	};

}



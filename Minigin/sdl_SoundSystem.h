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
		sdl_SoundSystem(const sdl_SoundSystem&) = delete;
		sdl_SoundSystem& operator=(const sdl_SoundSystem&) = delete;
		sdl_SoundSystem(sdl_SoundSystem&&) = delete;
		sdl_SoundSystem& operator=(sdl_SoundSystem&&) = delete;

		void Play(const sound_id soundId, const float volume) override;
		void AddAudioClip(AudioClip* audioClip) override;
		
	};

}



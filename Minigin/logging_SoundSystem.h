#pragma once
#include "SoundSystem.h"

namespace dae
{
	class logging_SoundSystem final: public SoundSystem
	{
		std::unique_ptr<SoundSystem>  _real_SoundSystem;

	public:
		logging_SoundSystem(std::unique_ptr<SoundSystem>&& real_SoundSystem);
		~logging_SoundSystem() = default;
		logging_SoundSystem(const logging_SoundSystem&) = delete;
		logging_SoundSystem& operator=(const logging_SoundSystem&) = delete;
		logging_SoundSystem(logging_SoundSystem&&) = delete;
		logging_SoundSystem& operator=(logging_SoundSystem&&) = delete;

		void Play(const sound_id id, const float volume) override;
		void AddAudioClip(AudioClip* audioClip) override;
	};
}



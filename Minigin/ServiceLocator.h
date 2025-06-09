#pragma once
#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class null_SoundSystem final : public SoundSystem
	{
		void Play(const sound_id, const float) override {}
		void AddAudioClip(AudioClip*) override {}
	};
	
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _SoundSystem_instance;
	public:
		static SoundSystem& get_SoundSystem() { return *_SoundSystem_instance; }
		static void register_SoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) {
			_SoundSystem_instance = soundSystem == nullptr ? std::make_unique<null_SoundSystem>() : std::move(soundSystem); }

	};
}



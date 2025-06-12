#pragma once
#include <memory>
#include "SoundSystem.h"
#include "ColliderSystem.h"

namespace dae
{
	class ColliderSystem;
	class null_SoundSystem final : public SoundSystem
	{
		void Play(const sound_id, const float) override {}
		void AddAudioClip(AudioClip*) override {}
		
	};

	class null_ColliderSystem final : public ColliderSystem
	{
		void AddGOwithHitbox(GameObject*) override {}
		void RemoveGOwithHitbox(GameObject*) override {}
		void FixedUpdate(float) override {}

	};
	
	
	class ServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _SoundSystem_instance;
		static std::unique_ptr<ColliderSystem> _ColliderSystem_instance;
	public:
		static SoundSystem& get_SoundSystem() { return *_SoundSystem_instance; }
		static ColliderSystem& get_ColliderSystem() { return *_ColliderSystem_instance; }
		static void register_SoundSystem(std::unique_ptr<SoundSystem>&& soundSystem) {
			_SoundSystem_instance = soundSystem == nullptr ? std::make_unique<null_SoundSystem>() : std::move(soundSystem); }
		static void register_ColliderSystem(std::unique_ptr<ColliderSystem>&& colliderSystem) {
			_ColliderSystem_instance = colliderSystem == nullptr ? std::make_unique<null_ColliderSystem>() : std::move(colliderSystem); }

	};
}



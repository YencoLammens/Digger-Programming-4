#include "ServiceLocator.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::_SoundSystem_instance{ std::make_unique<dae::null_SoundSystem>() };
std::unique_ptr<dae::ColliderSystem> dae::ServiceLocator::_ColliderSystem_instance{ std::make_unique<dae::null_ColliderSystem>() };
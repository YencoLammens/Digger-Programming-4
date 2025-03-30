#pragma once
#include "Command.h"
#include "HealthComponent.h"

namespace dae 
{
	class DamageCommand : public GameObjectCommand
	{
	public:
		DamageCommand(GameObject* gameObject);
		void Execute() override;
	};
}



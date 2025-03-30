#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae 
{
	class GainPointsCommand : public GameObjectCommand
	{
	public:
		GainPointsCommand(GameObject* gameObject);
		void Execute() override;
	};
}



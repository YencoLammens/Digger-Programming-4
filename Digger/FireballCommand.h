#pragma once
#include "Command.h"
#include "FireballLauncherComponent.h"

namespace dae
{
	class FireballCommand : public GameObjectCommand
	{
	public:
		FireballCommand(GameObject* gameObject, glm::vec3 direction);
		void Execute() override;

	private:
		glm::vec3 m_direction;
	};
}



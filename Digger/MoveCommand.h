#pragma once
#include "Command.h"
#include "MoveComponent.h"

namespace dae
{
	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObject, glm::vec3 direction);
		void Execute() override;

	private:
		glm::vec3 m_direction;

	};

}



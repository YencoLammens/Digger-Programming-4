#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 direction)
	:GameObjectCommand(gameObject), m_direction(direction)
{

}


void dae::MoveCommand::Execute()
{
	GetGameObject()->GetComponent<MoveComponent>()->SetDirection(m_direction);
}
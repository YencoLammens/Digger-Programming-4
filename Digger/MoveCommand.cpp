#include "MoveCommand.h"

dae::MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 direction)
	:GameObjectCommand(gameObject), m_direction(direction)
{

}


void dae::MoveCommand::Execute()
{
	GetGameObject()->GetComponent<MoveComponent>()->SetDirectionX(m_direction.x);
	GetGameObject()->GetComponent<MoveComponent>()->SetDirectionY(m_direction.y);
}
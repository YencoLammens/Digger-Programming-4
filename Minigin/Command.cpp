#include "Command.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* gameObject)
	:m_gameObject(gameObject)
{

}


dae::MoveCommand::MoveCommand(GameObject* gameObject, glm::vec3 direction)
	:GameObjectCommand(gameObject), m_direction(direction)
{

}


void dae::MoveCommand::Execute()
{
	GetGameObject()->GetComponent<MoveComponent>()->SetDirectionX(m_direction.x);
	GetGameObject()->GetComponent<MoveComponent>()->SetDirectionY(m_direction.y);
}

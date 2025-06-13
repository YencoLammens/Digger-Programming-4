#include "FireballCommand.h"
#include "MoveComponent.h"
#include <iostream>

dae::FireballCommand::FireballCommand(GameObject* gameObject, glm::vec3 direction)
	:GameObjectCommand(gameObject), m_direction(direction)
{

}


void dae::FireballCommand::Execute()
{
	m_direction = GetGameObject()->GetComponent<MoveComponent>()->GetPreviousDirection();
	GetGameObject()->GetComponent<FireballLauncherComponent>()->Fire(m_direction);
	//std::cout << "FireballCommand executed with direction: " << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << std::endl;
}
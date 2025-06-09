#include "RotatorComponent.h"
#include <cmath>
#include <iostream>

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3& targetPosition, float speed)
	:BaseComponent(owner), m_targetPosition(targetPosition), m_angle(0), m_speed(speed)
{
	auto ownerPos = GetOwner()->GetTransform()->GetWorldPosition();
	m_startingDistance = sqrt(pow(ownerPos.x - m_targetPosition.x, 2.0f) + pow(ownerPos.y - m_targetPosition.y, 2.0f));
}

void dae::RotatorComponent::Update(float deltaTime)
{

	m_angle += m_speed * deltaTime;
	
	GetOwner()->GetTransform()->SetLocalPosition(RotateAroundTarget());
}

glm::vec3 dae::RotatorComponent::RotateAroundTarget() {
	
	auto ownerPos = GetOwner()->GetTransform()->GetWorldPosition();
	//Apply rotation transformatio


	//float distanceCurrentAndTarget = sqrt(pow(ownerPos.x - m_targetPosition.x, 2.0f) + pow(ownerPos.y + m_targetPosition.y, 2.0f));
	//std::cout << distanceCurrentAndTarget << std::endl;

	
	float x = m_targetPosition.x + m_startingDistance * cos(m_angle);
	float y = m_targetPosition.y + m_startingDistance * sin(m_angle);
	
	return glm::vec3{ x, y, 0 };
}

void dae::RotatorComponent::FixedUpdate(float)
{
}

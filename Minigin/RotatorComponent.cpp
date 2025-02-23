#include "RotatorComponent.h"
#include <cmath>

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3& targetPosition)
	:BaseComponent(owner), m_targetPosition(targetPosition)
{
}

void dae::RotatorComponent::Update(float)
{
	
	auto owner = GetOwner();
	auto currentPosition = owner->GetTransform()->GetWorldPosition();

	
	owner->GetTransform()->SetLocalPosition(RotateAroundTarget(m_targetPosition.x, m_targetPosition.y, currentPosition.x, currentPosition.y, 360));
}

glm::vec3 dae::RotatorComponent::RotateAroundTarget(float centerX, float centerY, float pointX, float pointY, float angleInDegrees) {
	
	
	float angleInRadians = angleInDegrees * 3.14f / 180.0f;

	//Apply rotation transformation
	float rotatedPointX = centerX + (pointX - centerX) * cos(angleInRadians) - (pointY - centerY) * sin(angleInRadians);
	float rotatedPointY = centerY + (pointX - centerX) * sin(angleInRadians) + (pointY - centerY) * cos(angleInRadians);
	return glm::vec3{ rotatedPointX, rotatedPointY, 0 };
}

void dae::RotatorComponent::FixedUpdate()
{
}

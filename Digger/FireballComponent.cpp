#include "FireballComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "MoveComponent.h"

dae::FireballComponent::FireballComponent(GameObject* owner, const glm::vec3& direction, float speed) 
	: BaseComponent(owner), m_direction(direction), m_speed(speed)
{
}

void dae::FireballComponent::Update(float deltaTime)
{
	GetOwner()->GetTransform()->SetLocalPosition(GetOwner()->GetTransform()->GetLocalPosition() + m_direction * m_speed * deltaTime);
}

void dae::FireballComponent::FixedUpdate(float)
{
	//GetOwner()->GetComponent<dae::MoveComponent>()->;
}

#include "EnemyComponent.h"

dae::EnemyComponent::EnemyComponent(GameObject* owner, float speed)
	:BaseComponent(owner), m_speed(speed)
{
}

void dae::EnemyComponent::Update(float)
{
}

void dae::EnemyComponent::FixedUpdate(float)
{
}

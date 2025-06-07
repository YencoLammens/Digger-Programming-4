#include "HitboxComponent.h"
#include "SDL.h"
#include "GameObject.h"
#include "Transform.h"
#include "utils.h"

dae::HitboxComponent::HitboxComponent(GameObject* owner, float width, float height)
	: BaseComponent(owner), m_hitbox{GetOwner()->GetTransform()->GetWorldPosition().x ,GetOwner()->GetTransform()->GetWorldPosition().y, width, height}
{

}

void dae::HitboxComponent::Update(float)
{
	m_hitbox.x = GetOwner()->GetTransform()->GetWorldPosition().x;
	m_hitbox.y = GetOwner()->GetTransform()->GetWorldPosition().y;

	//std::cout << m_hitbox.x << " " << m_hitbox.y << " " << m_hitbox.width << " " << m_hitbox.height << std::endl;
}

void dae::HitboxComponent::FixedUpdate(float /*fixedTimeStep*/)
{
	if (utils::IsOverlapping(m_hitbox, Rectf{ 0,0,300,300 }))
	{
		std::cout << "Hitbox is overlapping with the rect!" << std::endl;
	}

}

dae::Rectf dae::HitboxComponent::GetHitbox() const
{
	return m_hitbox;
}



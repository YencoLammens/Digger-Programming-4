#include "HitboxComponent.h"
#include "SDL.h"
#include "GameObject.h"
#include "Transform.h"
#include "utils.h"
#include "Event.h"

dae::HitboxComponent::HitboxComponent(GameObject* owner, float width, float height)
	: BaseComponent(owner), m_hitbox{GetOwner()->GetTransform()->GetWorldPosition().x ,GetOwner()->GetTransform()->GetWorldPosition().y, width, height}
{

}

void dae::HitboxComponent::Update(float)
{
	m_hitbox.x = GetOwner()->GetTransform()->GetWorldPosition().x;
	m_hitbox.y = GetOwner()->GetTransform()->GetWorldPosition().y;

}

void dae::HitboxComponent::FixedUpdate(float /*fixedTimeStep*/)
{
	

}

const dae::Rectf dae::HitboxComponent::GetHitbox() const
{
	return m_hitbox;
}

void dae::HitboxComponent::OnCollision()
{
	GetOwner()->NotifyObservers(GameEvent(EventId::COLLIDED));
}
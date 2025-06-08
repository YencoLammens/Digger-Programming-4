#include "EmeraldPickupComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "ScoreComponent.h"

dae::EmeraldPickupComponent::EmeraldPickupComponent(GameObject* owner, GameObject* player)
	: BaseComponent(owner), m_player(player)
{
}

void dae::EmeraldPickupComponent::Update(float)
{
	if (utils::IsOverlapping(GetOwner()->GetComponent<HitboxComponent>()->GetHitbox(), m_player->GetComponent<HitboxComponent>()->GetHitbox()) && m_hasBeenPickedUp == false)
	{
		OnPickup();
	}
}
void dae::EmeraldPickupComponent::OnPickup()
{
	m_player->GetComponent<ScoreComponent>()->PickUpEmerald();
	m_hasBeenPickedUp = true;
	//Mark the gameobject for destruction
	GetOwner()->MarkForDeletion();
}


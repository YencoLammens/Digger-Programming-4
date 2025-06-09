#include "GoldPickupComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "ScoreComponent.h"

dae::GoldPickupComponent::GoldPickupComponent(GameObject* owner, GameObject* player)
	: BaseComponent(owner), m_player(player)
{
}

void dae::GoldPickupComponent::Update(float)
{
	if (utils::IsOverlapping(GetOwner()->GetComponent<HitboxComponent>()->GetHitbox(), m_player->GetComponent<HitboxComponent>()->GetHitbox()) && m_hasBeenPickedUp == false)
	{
		OnPickup();
	}
}
void dae::GoldPickupComponent::OnPickup()
{
	m_player->GetComponent<ScoreComponent>()->PickUpGold();
	m_hasBeenPickedUp = true;
	//Mark the gameobject for destruction
	GetOwner()->MarkForDeletion();
}


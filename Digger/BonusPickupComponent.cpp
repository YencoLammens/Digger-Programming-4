#include "BonusPickupComponent.h"
#include "utils.h"
#include "GameObject.h"
#include "HitboxComponent.h"
#include "ScoreComponent.h"

dae::BonusPickupComponent::BonusPickupComponent(GameObject* owner, GameObject* player)
	: BaseComponent(owner), m_player(player)
{
}

void dae::BonusPickupComponent::Update(float)
{
	if (utils::IsOverlapping(GetOwner()->GetComponent<HitboxComponent>()->GetHitbox(), m_player->GetComponent<HitboxComponent>()->GetHitbox()) && m_hasBeenPickedUp == false)
	{
		OnPickup();
	}
}
void dae::BonusPickupComponent::OnPickup()
{
	m_player->GetComponent<ScoreComponent>()->PickUpBonus();
	m_hasBeenPickedUp = true;
	//Mark the gameobject for destruction
	GetOwner()->MarkForDeletion();
}
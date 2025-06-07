#include "PickupComponent.h"

dae::PickupComponent::PickupComponent(GameObject* owner, int value)
	:BaseComponent(owner), m_value(value)
{
}
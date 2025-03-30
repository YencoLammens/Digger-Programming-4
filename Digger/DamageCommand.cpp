#include "DamageCommand.h"

dae::DamageCommand::DamageCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{

}

void dae::DamageCommand::Execute()
{
	GetGameObject()->GetComponent<HealthComponent>()->LoseHeart();
}
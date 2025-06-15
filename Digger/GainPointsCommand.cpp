#include "GainPointsCommand.h"

dae::GainPointsCommand::GainPointsCommand(GameObject* gameObject)
	:GameObjectCommand(gameObject)
{

}

void dae::GainPointsCommand::Execute()
{
	//GetGameObject()->GetComponent<ScoreComponent>()->PickUpEmerald();
}
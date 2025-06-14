#include "basic_ColliderSystem.h"
#include "HitboxComponent.h"
#include "utils.h"
#include "Event.h"


void dae::basic_ColliderSystem::FixedUpdate(float)
{
	for (auto& gameObject : gameObjects)
	{
		for (auto& gameObject2 : gameObjects)
		{
			if (utils::IsOverlapping(gameObject->GetComponent<HitboxComponent>()->GetHitbox(), gameObject2->GetComponent<HitboxComponent>()->GetHitbox()))
			{
				if (gameObject != gameObject2)
				{
				
				/*	gameObject->NotifyObservers(GameEvent(EventId::COLLIDED));
					gameObject2->NotifyObservers(GameEvent(EventId::COLLIDED));*/
					gameObject->GetComponent<HitboxComponent>()->OnCollision(gameObject2);
					gameObject2->GetComponent<HitboxComponent>()->OnCollision(gameObject);
				
					break;
					
				}
			}
		}
	}
}

void dae::basic_ColliderSystem::AddGOwithHitbox(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void dae::basic_ColliderSystem::RemoveGOwithHitbox(GameObject* gameObject)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
}

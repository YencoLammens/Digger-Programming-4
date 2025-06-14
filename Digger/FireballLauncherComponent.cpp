#include "FireballLauncherComponent.h"
#include "Fireball.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "HitboxComponent.h"
#include "ServiceLocator.h"

dae::FireballLauncherComponent::FireballLauncherComponent(GameObject* owner)
	: BaseComponent(owner)
{
	//CreateFireball(); // Pre-create a fireball GameObject (can also be pooled)
}

void dae::FireballLauncherComponent::Update(float deltaTime)
{
	m_TimeSinceLastFire += deltaTime;


	if (m_spriteNeedsUpdate)
	{
		if (m_TimeSinceLastFire >= m_CooldownTime)
		{
			m_canFire = true; // Reset firing ability after cooldown
			GetOwner()->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("Digger.png"));
			m_spriteNeedsUpdate = false;
		}
	}
}

void dae::FireballLauncherComponent::Fire(const glm::vec3& direction)
    {
	if (!m_canFire)
		return;
	
	m_spriteNeedsUpdate = true;
	GetOwner()->GetComponent<RenderComponent>()->SetTexture(ResourceManager::GetInstance().LoadTexture("DiggerOom.png"));
	m_TimeSinceLastFire = 0.0f;

	this->CreateFireball(direction);
	m_canFire = false;
	//std::cout << "Fireball launched in direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
}

void dae::FireballLauncherComponent::CreateFireball(const glm::vec3& direction)
{
	auto pfireball = std::make_unique<GameObject>();

	auto transform = std::make_unique<Transform>(pfireball.get());

	
	float launchPositionX{ 0 };
	float launchPositionY{ 0 };
	//auto rotation = GetOwner()->GetTransform()->GetRotation();
	if (direction.x == 1 && direction.y == 0)
	{
		launchPositionX = GetOwner()->GetTransform()->GetWorldPosition().x + 51;
		launchPositionY = GetOwner()->GetTransform()->GetWorldPosition().y + 10;
	}
	else if (direction.x == -1 && direction.y == 0)
	{
		launchPositionX = GetOwner()->GetTransform()->GetWorldPosition().x - 31;
		launchPositionY = GetOwner()->GetTransform()->GetWorldPosition().y + 10;
	}
	else if (direction.x == 0 && direction.y == 1)
	{
		launchPositionX = GetOwner()->GetTransform()->GetWorldPosition().x + 10;
		launchPositionY = GetOwner()->GetTransform()->GetWorldPosition().y + 51 ;
	}
	else if (direction.x == 0 && direction.y == -1)
	{
		launchPositionX = GetOwner()->GetTransform()->GetWorldPosition().x + 10;
		launchPositionY = GetOwner()->GetTransform()->GetWorldPosition().y - 51;
	}
	
	glm::vec3 position = glm::vec3{ launchPositionX, launchPositionY, 0 };
	auto fireball = std::make_unique<Fireball>(pfireball.get(), position, direction);
	auto render = std::make_unique<RenderComponent>(pfireball.get());
	auto hitbox = std::make_unique<HitboxComponent>(pfireball.get(), 25.f, 25.f);
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("Fireball.png"));

	pfireball->AddComponent(std::move(transform));
	pfireball->AddComponent(std::move(render));
	pfireball->AddComponent(std::move(hitbox));
	pfireball->AddObserver(fireball.get());
	pfireball->AddComponent(std::move(fireball));
	
	
	ServiceLocator::get_ColliderSystem().AddGOwithHitbox(pfireball.get());


	SceneManager::GetInstance().GetScene(0)->Add(std::move(pfireball));
}

#include "FireballLauncherComponent.h"
#include "Fireball.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "HitboxComponent.h"

dae::FireballLauncherComponent::FireballLauncherComponent(GameObject* owner)
	: BaseComponent(owner)
{
	//CreateFireball(); // Pre-create a fireball GameObject (can also be pooled)
}

void dae::FireballLauncherComponent::Update(float deltaTime)
{
	m_TimeSinceLastFire += deltaTime;
}

void dae::FireballLauncherComponent::Fire(const glm::vec3& direction)
{
	if (m_TimeSinceLastFire < m_CooldownTime)
		return;

	m_TimeSinceLastFire = 0.0f;

	this->CreateFireball(direction);
	std::cout << "Fireball launched in direction: " << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
}

void dae::FireballLauncherComponent::CreateFireball(const glm::vec3& direction)
{
	m_pFireball = std::make_unique<GameObject>();

	auto transform = std::make_unique<Transform>(m_pFireball.get());
	auto fireball = std::make_unique<Fireball>(m_pFireball.get(), GetOwner()->GetTransform()->GetWorldPosition(), direction);
	auto render = std::make_unique<RenderComponent>(m_pFireball.get());
	auto hitbox = std::make_unique<HitboxComponent>(m_pFireball.get(), 25.f, 25.f);
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("Fireball.png"));

	m_pFireball->AddComponent(std::move(transform));
	m_pFireball->AddComponent(std::move(fireball));
	m_pFireball->AddComponent(std::move(render));
	m_pFireball->AddComponent(std::move(hitbox));


	// Add to scene (replace `scene` with your actual scene reference)
	SceneManager::GetInstance().GetScene(0)->Add(std::move(m_pFireball));
}
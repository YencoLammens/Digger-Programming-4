#include "HPDisplay.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "Event.h"
#include <iostream>

dae::HPDisplay::HPDisplay(GameObject* goUI)
	: BaseComponent(goUI)
{
}

void dae::HPDisplay::SetHeartIcons(const std::vector<GameObject*>& heartIcons)
{
	m_HeartIcons = heartIcons;
}

void dae::HPDisplay::OnNotify(const GameEvent& event, GameObject* go)
{
	if (event.Id != EventId::HEALTH_CHANGED || !go)
		return;

	auto healthComp = go->GetComponent<HealthComponent>();
	if (!healthComp)
		return;

	int currentHP = healthComp->GetHealth();
	for (size_t i = 0; i < m_HeartIcons.size(); ++i)
	{
		auto* heartGO = m_HeartIcons[i];
		if (!heartGO) continue;

		auto* renderComp = heartGO->GetComponent<RenderComponent>();
		if (renderComp)
		{
			std::cout << "Current HP: " << currentHP << "\n";
			renderComp->SetEnabled(i < currentHP);
		}
	}
}
//
//void dae::HPDisplay::Render() const
//{
//	if (!m_Texture) return;
//
//	const auto pos = m_goUI->GetTransform()->GetWorldPosition();
//
//	for (int i = 0; i < m_Lives; ++i)
//	{
//		dae::Renderer::GetInstance().RenderTexture(
//			m_Texture,
//			pos.x + i * m_Spacing,
//			pos.y
//		);
//	}
//}
#include "HPDisplay.h"
#include "HealthComponent.h"
#include "TextComponent.h"


dae::HPDisplay::HPDisplay(GameObject* goUI)
	:BaseComponent(goUI)
{
	m_goUI = goUI;
}

void dae::HPDisplay::OnNotify(const GameEvent& event, GameObject* go)
{
	switch (event.Id)
	{
	case EventId::HEALTH_CHANGED :
		m_goUI->GetComponent<TextComponent>()->SetText("# lives: " + std::to_string(go->GetComponent<HealthComponent>()->GetHealth()));
		break;
	}
}

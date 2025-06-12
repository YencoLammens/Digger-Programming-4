#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "Event.h"
#include <format>

dae::ScoreDisplay::ScoreDisplay(GameObject* goUI)
	:BaseComponent(goUI)
{
	m_goUI = goUI;
}

void dae::ScoreDisplay::OnNotify(const GameEvent& event, GameObject* go)
{
	switch (event.Id)
	{
	case EventId::SCORE_CHANGED:
		std::string scoreString = std::format("{:05}", go->GetComponent<dae::ScoreComponent>()->GetScore());
		m_goUI->GetComponent<TextComponent>()->SetText(scoreString);
		break;
	}

}

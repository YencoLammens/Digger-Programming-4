#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "Event.h"

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
		m_goUI->GetComponent<TextComponent>()->SetText("0" + std::to_string(go->GetComponent<ScoreComponent>()->GetScore()));
		break;
	}

}

#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

dae::ScoreDisplay::ScoreDisplay(GameObject* goUI)
	:BaseComponent(goUI)
{
	m_goUI = goUI;
}

void dae::ScoreDisplay::OnNotify(const Event& event, GameObject* go)
{
	switch (event.Id)
	{
	case EventId::SCORE_CHANGED:
		m_goUI->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(go->GetComponent<ScoreComponent>()->GetScore()));
		break;
	}

}

#include "Achievements.h"

void dae::Achievements::OnNotify(const GameEvent& event, GameObject*)
{
	switch (event.Id)
	{
	case EventId::SCORE_CHANGED:
		//Unlock achievement;
		break;
	}
}



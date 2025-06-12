#pragma once
//#include "Event.h"
//#include "GameObject.h"

namespace dae 
{
	struct GameEvent;
	class GameObject;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const GameEvent& event, GameObject* gameObject) = 0;
	};
}


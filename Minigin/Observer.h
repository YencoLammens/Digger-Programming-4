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
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(Observer&&) = delete;
		virtual void OnNotify(const GameEvent& event, GameObject* gameObject) = 0;
	};
}


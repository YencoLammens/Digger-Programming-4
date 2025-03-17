#pragma once
#include "Event.h"
#include "GameObject.h"

namespace dae 
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const Event& event, GameObject* gameObject) = 0;
	};
}


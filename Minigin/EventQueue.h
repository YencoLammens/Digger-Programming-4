#pragma once
#include "Event.h"
#include <queue>
#include <mutex>

namespace dae
{
	class EventQueue
	{
	public:
		void push(Event* event);
		Event* pop();
		void process();

	private:
		std::queue<Event*> eventQueue;
		std::mutex queueMutex_;
		std::condition_variable cv_;

	};

}

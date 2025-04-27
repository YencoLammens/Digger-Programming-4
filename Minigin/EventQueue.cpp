#include "EventQueue.h"
#include <queue>

void dae::EventQueue::push(Event* event)
{
	std::lock_guard<std::mutex> lock(queueMutex_);
	eventQueue.push(event);
	cv_.notify_one();
}

dae::Event* dae::EventQueue::pop()
{
	std::unique_lock<std::mutex> lock(queueMutex_);
	cv_.wait(lock, [this]() { return !eventQueue.empty(); });

	auto event = eventQueue.front();
	eventQueue.pop();
	return event;
}

void dae::EventQueue::process()
{
	std::unique_lock<std::mutex> lock(queueMutex_);
	while (!eventQueue.empty())
	{
		auto event = eventQueue.front();
		eventQueue.pop();
		
		lock.unlock();


		event->process();
		delete event;

		lock.lock();
	}
}

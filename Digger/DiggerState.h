#pragma once
#include "GameObject.h"
namespace dae
{
	enum class DiggerStates
	{
		Idle,
		Moving,
		Dying,
		Dead
	};

	class DiggerState
	{
	public:
		virtual ~DiggerState() = default;
		/*virtual void HandleInput(GameObject& gameObject) {};
		virtual void HandleEvent(GameObject& gameObject) {};
		virtual void Update(GameObject& gameObject, float elapsedSec) {};
		virtual void enter(GameObject& gameObject) {}
		virtual void exit(GameObject& gameObject) {}*/
	};

	/*class DiggerIdleState : public DiggerState
	{
	public:
		DiggerIdleState() = default;
		void HandleInput(GameObject& gameObject) override;
		void Update(GameObject& gameObject, float elapsedSec) override;
	};

	class DiggerMovingState : public DiggerState
	{
	public:
		DiggerMovingState() = default;
		void Update(GameObject& gameObject, float elapsedSec) override;
	};

	class DiggerDyingState : public DiggerState
	{
	public:
		DiggerDyingState() = default;
		void Update(GameObject& gameObject, float elapsedSec) override;
	};

	class DiggerDeadState : public DiggerState
	{
	public:
		DiggerDeadState() = default;
		void Update(GameObject& gameObject, float elapsedSec) override;
	};*/
}

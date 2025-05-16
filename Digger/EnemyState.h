#pragma once
#include "GameObject.h"
namespace dae
{
	enum class EnemyStates
	{
		EnemyIdle,
		Chasing,
		Dead
	};

	class EnemyState
	{
	public:
		virtual ~EnemyState() {};
		/*virtual void HandleEvent(GameObject& gameObject) {};
		virtual void Update(GameObject& gameObject, float elapsedSec) {};
		/*void enter(GameObject& go) override {};
		void exit(GameObject& go) override {};*/
	};

	/*class EnemyIdleState : public EnemyState
	{
		EnemyIdleState();
		virtual void HandleEvent(GameObject& gameObject) override;
		virtual void Update(GameObject& gameObject, float elapsedSec) override;
	};

	class EnemyChasingState : public EnemyState
	{
		EnemyChasingState();
		virtual void HandleEvent(GameObject& gameObject) override;
		virtual void Update(GameObject& gameObject, float elapsedSec) override;
	};

	class EnemyDeadState : public EnemyState
	{
		EnemyDeadState();
		virtual void HandleEvent(GameObject& gameObject) override;
		virtual void Update(GameObject& gameObject, float elapsedSec) override;
	};*/

}



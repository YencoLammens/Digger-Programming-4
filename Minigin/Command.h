#pragma once
#include "GameObject.h"
#include <memory>
#include "glm.hpp"

namespace dae
{
	class Command
	{

	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

	};
	class GameObjectCommand : public Command
	{
	public:
		explicit GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() = default;

	protected:
		GameObject* GetGameObject() const { return m_gameObject; }

	private:
		GameObject* m_gameObject;

	};

}



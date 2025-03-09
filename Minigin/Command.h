#pragma once
#include "GameObject.h"
#include <memory>
#include "glm.hpp"
#include "MoveComponent.h"

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

	class MoveCommand : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* gameObject, glm::vec3 direction);
		void Execute() override;

	private:
		glm::vec3 m_direction;

	};
}



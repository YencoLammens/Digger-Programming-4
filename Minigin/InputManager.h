#pragma once
#include "Singleton.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class ButtonState 
		{
			RELEASED,
			PRESSED,
			HELD

		};
		bool ProcessInput();

		

	private:
		
	};

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

	};


	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand();

	protected:
		GameObject* GetGameObject() const { return m_gameObject; }

	private:
		GameObject* m_gameObject;

	};

	class Move : public GameObjectCommand 
	{
		public: void Execute() override
		{
			//GetGameObject()->Move();
		}
	};
		
	

	
}

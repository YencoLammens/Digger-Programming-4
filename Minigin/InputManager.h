#pragma once
#include <SDL.h>
#include <vector>
#include <map>
#include "GameObject.h"
#include <memory>
#include "glm.hpp"
#include "Command.h"
#include "Controller.h"
namespace dae
{
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class ButtonState
		{
			DOWN,
			UP,
			PRESSED

		};
		bool ProcessInput();
		void BindKeyboardCommand(SDL_Keycode key, ButtonState state, std::unique_ptr<Command> command);
		void BindControllerCommand(WORD button, ButtonState state, std::unique_ptr<Command> command);


		

	private:
		std::map<std::pair<SDL_Keycode, ButtonState>, std::unique_ptr<Command>> m_KeyboardCommands;
		std::map<std::pair<WORD, ButtonState>, std::unique_ptr<Command>> m_ControllerCommands;
		std::unique_ptr<Controller> m_Controller = std::make_unique<Controller>(0);
		//std::map<SDL_Keycode, bool> m_PreviousKeyStates;
	};

	
}

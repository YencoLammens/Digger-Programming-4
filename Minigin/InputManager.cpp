#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include "MoveComponent.h"
bool dae::InputManager::ProcessInput()
{
	//Responsive
	SDL_Event e;
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (const auto& [keys, value] : m_KeyboardCommands)
			{
				if (keys.first == e.key.keysym.sym && keys.second == ButtonState::DOWN)
				{
					value.get()->Execute();
				}
			}
		}
		if (e.type == SDL_KEYUP) 
		{
			for (const auto& [keys, value] : m_KeyboardCommands)
			{
				if (keys.first == e.key.keysym.sym && keys.second == ButtonState::UP)
				{
					value.get()->Execute();
				}
			}
		}
	
	}
	for (const auto& [keys, value] : m_KeyboardCommands)
	{
		if (keyStates[SDL_GetScancodeFromKey(keys.first)] && keys.second == ButtonState::PRESSED)
		{
			value.get()->Execute();
		}
	}


	if (m_Controller)
	{
		m_Controller->Update();
		for (const auto& [keys, value] : m_ControllerCommands)
		{
			if (keys.second == ButtonState::PRESSED)
			{
				if (keys.first == XINPUT_GAMEPAD_DPAD_UP && m_Controller->IsDPadUp()) {
					value.get()->Execute();
				}
				else if (keys.first == XINPUT_GAMEPAD_DPAD_DOWN && m_Controller->IsDPadDown()) {
					value.get()->Execute();
				}
				if (keys.first == XINPUT_GAMEPAD_DPAD_LEFT && m_Controller->IsDPadLeft()) {
					value.get()->Execute();
				}
				else if (keys.first == XINPUT_GAMEPAD_DPAD_RIGHT && m_Controller->IsDPadRight()) {
					value.get()->Execute();
				}
			}
			if (keys.second == ButtonState::UP && m_Controller.get()->IsButtonReleased(keys.first))
			{
				if (keys.first == XINPUT_GAMEPAD_DPAD_UP && !m_Controller->IsDPadUp()) {
					value.get()->Execute();
				}
				else if (keys.first == XINPUT_GAMEPAD_DPAD_DOWN && !m_Controller->IsDPadDown()) {
					value.get()->Execute();
				}
				if (keys.first == XINPUT_GAMEPAD_DPAD_LEFT && !m_Controller->IsDPadLeft()) {
					value.get()->Execute();
				}
				else if (keys.first == XINPUT_GAMEPAD_DPAD_RIGHT && !m_Controller->IsDPadRight()) {
					value.get()->Execute();
				}
			}
			
		}
	}
	

	return true;
}

void dae::InputManager::BindKeyboardCommand(SDL_Keycode key, ButtonState state, std::unique_ptr<Command> command)
{
	m_KeyboardCommands.emplace(std::make_pair(key,state), std::move(command));
}

void dae::InputManager::BindControllerCommand(WORD button, ButtonState state, std::unique_ptr<Command> command)
{
	m_ControllerCommands.emplace(std::make_pair(button, state), std::move(command));
}

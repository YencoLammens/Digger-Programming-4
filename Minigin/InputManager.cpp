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

	return true;
}

void dae::InputManager::BindKeyboardCommand(SDL_Keycode key, ButtonState state, std::unique_ptr<Command> command)
{
	m_KeyboardCommands.emplace(std::make_pair(key,state), std::move(command));
}
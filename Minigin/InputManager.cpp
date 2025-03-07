#include <SDL.h>
#include "InputManager.h"
#include <iostream>

bool dae::InputManager::ProcessInput()
{
	//Responsive
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
			if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_z)
			{
				std::cout << "move up";
			}
			if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_q)
			{
				std::cout << "move left";
			}
			if (e.key.keysym.sym == SDLK_d)
			{
				std::cout << "move right";
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				std::cout << "move down";
			}
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		
		
		// etc...
	}

	return true;
}

dae::GameObjectCommand::GameObjectCommand(GameObject* gameObject)
	:m_gameObject(gameObject)
{

}

dae::GameObjectCommand::~GameObjectCommand()
{
}

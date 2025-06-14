#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "Transform.h"
#include "RotatorComponent.h"
#include "MoveComponent.h"
#include "Command.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "HPDisplay.h"
#include "Event.h"
#include "ScoreDisplay.h"
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");




	//Background
	auto go = std::make_unique<dae::GameObject>();
	auto renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
	go->AddComponent(std::move(renderComponent));
	scene.Add(std::move(go));

	//DAE Logo
	go = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(std::move(renderComponent));
	go->GetTransform()->SetLocalPosition(216, 150, 0);

	scene.Add(std::move(go));

	//Title
	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font.get());
	go->GetTransform()->SetLocalPosition(80, 80, 0);
	go->AddComponent(std::move(textComponent));
	scene.Add(std::move(go));

	//FPS display
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 10, 0);
	auto fpsComponent = std::make_unique<dae::FPSComponent>(go.get(), font);
	go->AddComponent(std::move(fpsComponent));
	scene.Add(std::move(go));

	

	//Digger
	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(250, 300, 0);
	renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DiggerScreenshot.png"));
	go->AddComponent(std::move(renderComponent));
	go->GetTransform()->SetLocalPosition(230, 300, 0);
	auto moveComponent = std::make_unique<dae::MoveComponent>(go.get());
	go->AddComponent(std::move(moveComponent));
	auto healthComponent = std::make_unique<dae::HealthComponent>(go.get());
	go->AddComponent(std::move(healthComponent));
	auto scoreComponent = std::make_unique<dae::ScoreComponent>(go.get());
	go->AddComponent(std::make_unique<dae::ScoreComponent>(go.get()));
	//auto rotatorComponent = std::make_unique<dae::RotatorComponent>(go.get(), glm::vec3(200, 200, 0), 2.0f);
	//go->AddComponent(std::move(rotatorComponent);

	//Bind keyboard inputs to DIGGER
	//Pressed
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_z, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, -1, 0 }));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, -1, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ -1, 0, 0 }));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_q, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ -1, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 1, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 1, 0 }));


	//Down
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_c, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::DamageCommand>(go.get()));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_x, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::GainPointsCommand>(go.get()));


	//Up
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_w, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_z, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_q, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	
	//Tutorial displays
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto go2 = std::make_unique<dae::GameObject>();
	go2->GetTransform()->SetLocalPosition(10, 220, 0);
	textComponent = std::make_unique<dae::TextComponent>(go2.get(), "Use WASD to move the first Digger, C to inflict damage, and X to gain points", font.get());
	go2->AddComponent(std::move(textComponent));
	scene.Add(std::move(go2));

	go2 = std::make_unique<dae::GameObject>();
	go2->GetTransform()->SetLocalPosition(10, 240, 0);
	textComponent = std::make_unique<dae::TextComponent>(go2.get(), "Use the DPAD to move the second Digger, X to inflict damage, A to gain points", font.get());
	go2->AddComponent(std::move(textComponent));
	scene.Add(std::move(go2));

	//HUD displays for Digger

	//Health display digger
	go2 = std::make_unique<dae::GameObject>();
	go2->GetTransform()->SetLocalPosition(10, 270, 0);
	textComponent = std::make_unique<dae::TextComponent>(go2.get(), "# lives: " + std::to_string(go->GetComponent<dae::HealthComponent>()->GetHealth()), font.get());
	go2->AddComponent(std::move(textComponent));
	auto hpDisplayComponent = std::make_unique<dae::HPDisplay>(go2.get());
	go2->AddComponent(std::move(hpDisplayComponent));
	go->AddObserver(go2->GetComponent<dae::HPDisplay>());
	scene.Add(std::move(go2));

	
	
	

	//Score display digger
	go2 = std::make_unique<dae::GameObject>();
	go2->GetTransform()->SetLocalPosition(10, 300, 0);
	textComponent = std::make_unique<dae::TextComponent>(go2.get(), "Score: " + std::to_string(go->GetComponent<dae::ScoreComponent>()->GetScore()), font.get());
	go2->AddComponent(std::move(textComponent));
	auto scoreDisplayComponent = std::make_unique<dae::ScoreDisplay>(go2.get());
	go2->AddComponent(std::move(scoreDisplayComponent));
	go->AddObserver(go2->GetComponent<dae::ScoreDisplay>());
	scene.Add(std::move(go2));



	
	
	//Nobbin or digger 2
	go2 = std::make_unique<dae::GameObject>();
		
	renderComponent = std::make_unique<dae::RenderComponent>(go2.get());
	//renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("NobbinScreenshot.png"));
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DiggerScreenshot.png"));
	go2->AddComponent(std::move(renderComponent));
	go2->GetTransform()->SetLocalPosition(300, 300, 0);
	moveComponent = std::make_unique<dae::MoveComponent>(go2.get(), 200.0f);
	go2->AddComponent(std::move(moveComponent));
	healthComponent = std::make_unique<dae::HealthComponent>(go2.get());
	go2->AddComponent(std::move(healthComponent));
	scoreComponent = std::make_unique<dae::ScoreComponent>(go2.get());
	go2->AddComponent(std::move(scoreComponent));
	//rotatorComponent = std::make_unique<dae::RotatorComponent>(go2.get(), glm::vec3(0,0,0), 5.0f);
	//go2->AddComponent(std::move(rotatorComponent));
	
	//go2->SetParent(go.get(), false);

	//Pressed
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, -1, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ -1, 0, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 1, 0, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 1, 0 }));


	//Down
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_X, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::DamageCommand>(go2.get()));
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_A, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::GainPointsCommand>(go2.get()));


	//Up
	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	
	
	scene.Add(std::move(go));

	//HUD displays for Digger2

	//Health display digger2
	auto go3 = std::make_unique<dae::GameObject>();
	go3->GetTransform()->SetLocalPosition(10, 330, 0);
	textComponent = std::make_unique<dae::TextComponent>(go3.get(), "# lives: " + std::to_string(go2->GetComponent<dae::HealthComponent>()->GetHealth()), font.get());
	go3->AddComponent(std::move(textComponent));
	hpDisplayComponent = std::make_unique<dae::HPDisplay>(go3.get());
	go3->AddComponent(std::move(hpDisplayComponent));
	go2->AddObserver(go3->GetComponent<dae::HPDisplay>());
	scene.Add(std::move(go3));




	//Score display digger2
	go3 = std::make_unique<dae::GameObject>();
	go3->GetTransform()->SetLocalPosition(10, 360, 0);
	textComponent = std::make_unique<dae::TextComponent>(go3.get(), "Score: " + std::to_string(go2->GetComponent<dae::ScoreComponent>()->GetScore()), font.get());
	go3->AddComponent(std::move(textComponent));
	scoreDisplayComponent = std::make_unique<dae::ScoreDisplay>(go3.get());
	go3->AddComponent(std::move(scoreDisplayComponent));
	go2->AddObserver(go3->GetComponent<dae::ScoreDisplay>());
	scene.Add(std::move(go3));
	scene.Add(std::move(go2));
	

	
	
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	
    return 0;
}

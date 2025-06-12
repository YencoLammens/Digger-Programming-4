//#if _DEBUG
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif
//
//#include "Minigin.h"
//
//int main(int, char* []) {
//	dae::Minigin engine;
//	engine.Run();
//	return 0;
//}

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
#include "MoveCommand.h"
#include "DamageCommand.h"
#include "GainPointsCommand.h"
#include "ServiceLocator.h"
#include "sdl_SoundSystem.h"
#include "logging_SoundSystem.h"
#include "AudioClip.h"
#include "EventQueue.h"
#include "HitboxComponent.h"
#include "GridMovementComponent.h"
#include "TileMap.h"
#include "EmeraldPickupComponent.h"
#include "BonusPickupComponent.h"
#include "GoldPickupComponent.h"
#include "DeathAnimationComponent.h"
#include "EnemyComponent.h"
#include "FireballLauncherComponent.h"
#include "FireballCommand.h"
#include <format>
#include "basic_ColliderSystem.h"


void load()
{
	//Register sound system
#if _DEBUG
	dae::ServiceLocator::register_SoundSystem(std::make_unique<dae::logging_SoundSystem>(std::make_unique<dae::sdl_SoundSystem>()));
#else
	dae::ServiceLocator::register_SoundSystem(std::make_unique<dae::sdl_SoundSystem>());
#endif

	dae::ServiceLocator::register_ColliderSystem(std::make_unique<dae::basic_ColliderSystem>());

	//dae::ServiceLocator::register_SoundSystem(std::make_unique<dae::sdl_SoundSystem>());
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Level");
	/*auto eventQueue = std::make_unique<dae::EventQueue>();
	eventQueue->push(std::make_unique(dae::SoundEvent(dae::EventId::SCORE_CHANGED, 1, 0.5f)));*/
	

	auto& soundService = dae::ServiceLocator::get_SoundSystem();
	/*auto clip = std::make_unique<dae::AudioClip>(dae::ResourceManager::GetInstance().GetDataPath() + "/bnb.wav");
	soundService.AddAudioClip(clip.get());
	soundService.Play(0, 0.5f);*/

	auto clip = dae::ResourceManager::GetInstance().LoadAudioClip("bnb.wav");
	soundService.AddAudioClip(clip.get());
	soundService.Play(0, 1.0f);


	//auto& colliderService = dae::ServiceLocator::get_ColliderSystem();


	dae::ResourceManager::GetInstance().LoadTexture("Gravestone.png");
	dae::ResourceManager::GetInstance().LoadTexture("Hobbin.png");
	dae::ResourceManager::GetInstance().LoadTexture("Fireball.png");

	/*go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font.get());
	go->GetTransform()->SetLocalPosition(80, 80, 0);
	go->AddComponent(std::move(textComponent));
	scene.Add(std::move(go));*/
	

	////Background
	//auto go = std::make_unique<dae::GameObject>();
	//auto renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	//renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
	//go->AddComponent(std::move(renderComponent));
	//scene.Add(std::move(go));

	////DAE Logo
	//go = std::make_unique<dae::GameObject>();
	//renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	//renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	//go->AddComponent(std::move(renderComponent));
	//go->GetTransform()->SetLocalPosition(216, 150, 0);

	//scene.Add(std::move(go));

	////Title
	//go = std::make_unique<dae::GameObject>();
	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_unique<dae::TextComponent>(go.get(), "Programming 4 Assignment", font.get());*/
	///*go->GetTransform()->SetLocalPosition(80, 80, 0);
	//go->AddComponent(std::move(textComponent));
	//scene.Add(std::move(go));*/

	////FPS display
	//go = std::make_unique<dae::GameObject>();
	//go->GetTransform()->SetLocalPosition(10, 10, 0);
	//auto fpsComponent = std::make_unique<dae::FPSComponent>(go.get(), font);
	//go->AddComponent(std::move(fpsComponent));
	//scene.Add(std::move(go));

	//Map n stuff
	auto tileMap = std::make_unique<dae::TileMap>(1000.0f, 650.0f);

	auto go = std::make_unique<dae::GameObject>();
	//Digger
	auto renderComponent = std::make_unique<dae::RenderComponent>(go.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Digger.png"));
	go->AddComponent(std::move(renderComponent));
	go->GetTransform()->SetLocalPosition(96, 128, 0);
	auto moveComponent = std::make_unique<dae::MoveComponent>(go.get());
	go->AddComponent(std::move(moveComponent));
	auto healthComponent = std::make_unique<dae::HealthComponent>(go.get());
	go->AddComponent(std::move(healthComponent));
	auto scoreComponent = std::make_unique<dae::ScoreComponent>(go.get());
	go->AddComponent(std::make_unique<dae::ScoreComponent>(go.get()));
	auto hitboxComponent = std::make_unique<dae::HitboxComponent>(go.get(), 50.f, 50.f);
	go->AddComponent(std::move(hitboxComponent));
	auto deathAnimationComponent = std::make_unique<dae::DeathAnimationComponent>(go.get());
	go->AddComponent(std::move(deathAnimationComponent));
	auto FireballLauncherComponent = std::make_unique<dae::FireballLauncherComponent>(go.get());
	go->AddComponent(std::move(FireballLauncherComponent));
	/*auto gridMovementComponent = std::make_unique<dae::GridMovementComponent>(go.get(), 50.0f, 200.0f, tileMap.get());
	go->AddComponent(std::move(gridMovementComponent));*/
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

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_SPACE, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::FireballCommand>(go.get(), glm::vec3{ 1, 0, 0 }));


	//Down
	/*dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_c, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::DamageCommand>(go.get()));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_x, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::GainPointsCommand>(go.get()));*/
	

	//Up
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_z, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_a, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));
	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_q, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_d, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));

	dae::InputManager::GetInstance().BindKeyboardCommand(SDLK_s, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go.get(), glm::vec3{ 0, 0, 0 }));


	//Tutorial displays
	auto font = dae::ResourceManager::GetInstance().LoadFont("PressStart2P-Regular.ttf", 32);

	auto go2 = std::make_unique<dae::GameObject>();
	/*go2->GetTransform()->SetLocalPosition(10, 220, 0);
	auto textComponent = std::make_unique<dae::TextComponent>(go2.get(), "Use WASD to move the first Digger", font.get());
	go2->AddComponent(std::move(textComponent));
	scene.Add(std::move(go2));

	go2 = std::make_unique<dae::GameObject>();
	go2->GetTransform()->SetLocalPosition(10, 240, 0);
	textComponent = std::make_unique<dae::TextComponent>(go2.get(), "Use the DPAD to move the second Digger", font.get());
	go2->AddComponent(std::move(textComponent));
	scene.Add(std::move(go2));*/

	//HUD displays for Digger

	//Health display digger
	go2 = std::make_unique<dae::GameObject>();
	//go2->GetTransform()->SetLocalPosition(240, 0, 0);
	auto hpDisplayComponent = std::make_unique<dae::HPDisplay>(go2.get());
	

	std::vector<dae::GameObject*> hearts;
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("Digger.png");

	for (int i = 0; i <= 2; ++i) // for 3 lives
	{
		auto heartGo = std::make_unique<dae::GameObject>();
		heartGo->GetTransform()->SetLocalPosition(240.f + i * 60.f, 0.f, 0.f);

		renderComponent = std::make_unique<dae::RenderComponent>(heartGo.get());
		renderComponent->SetTexture(texture);
		heartGo->AddComponent(std::move(renderComponent));

		hearts.push_back(heartGo.get());
		scene.Add(std::move(heartGo));
	}
	
	hpDisplayComponent->SetHeartIcons(hearts);
	
	go2->AddComponent(std::move(hpDisplayComponent));
	go->AddObserver(go2->GetComponent<dae::HPDisplay>());
	scene.Add(std::move(go2));

	





	//Score display digger
	auto scoreGo = std::make_unique<dae::GameObject>();
	scoreGo->GetTransform()->SetLocalPosition(50, 10, 0);
	std::string scoreString = std::format("{:05}", go->GetComponent<dae::ScoreComponent>()->GetScore());
	auto textComponent = std::make_unique<dae::TextComponent>(scoreGo.get(), scoreString, font.get());
	scoreGo->AddComponent(std::move(textComponent));
	auto scoreDisplayComponent = std::make_unique<dae::ScoreDisplay>(scoreGo.get());
	scoreGo->AddComponent(std::move(scoreDisplayComponent));
	go->AddObserver(scoreGo->GetComponent<dae::ScoreDisplay>());
	scene.Add(std::move(scoreGo));
	



	//Pickup emerald
	go2 = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go2.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Emerald.png"));
	go2->AddComponent(std::move(renderComponent));
	go2->GetTransform()->SetLocalPosition(500, 300, 0);
	hitboxComponent = std::make_unique<dae::HitboxComponent>(go2.get(), 50.f, 50.f);
	go2->AddComponent(std::move(hitboxComponent));
	auto emeraldPickupComponent = std::make_unique<dae::EmeraldPickupComponent>(go2.get(), go.get());
	go2->AddComponent(std::move(emeraldPickupComponent));
	scene.Add(std::move(go2));

	

	//Pickup bonus
	go2 = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go2.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bonus.png"));
	go2->AddComponent(std::move(renderComponent));
	go2->GetTransform()->SetLocalPosition(200, 100, 0);
	hitboxComponent = std::make_unique<dae::HitboxComponent>(go2.get(), 50.f, 50.f);
	go2->AddComponent(std::move(hitboxComponent));
	auto BonusPickupComponent = std::make_unique<dae::BonusPickupComponent>(go2.get(), go.get());
	go2->AddComponent(std::move(BonusPickupComponent));
	scene.Add(std::move(go2));

	//Pickup gold
	go2 = std::make_unique<dae::GameObject>();
	renderComponent = std::make_unique<dae::RenderComponent>(go2.get());
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Gold.png"));
	go2->AddComponent(std::move(renderComponent));
	go2->GetTransform()->SetLocalPosition(300, 100, 0);
	hitboxComponent = std::make_unique<dae::HitboxComponent>(go2.get(), 30.f, 30.f);
	go2->AddComponent(std::move(hitboxComponent));
	auto goldPickupComponent = std::make_unique<dae::GoldPickupComponent>(go2.get(), go.get());
	go2->AddComponent(std::move(goldPickupComponent));
	scene.Add(std::move(go2));

	

	//Nobbin
	go2 = std::make_unique<dae::GameObject>();

	renderComponent = std::make_unique<dae::RenderComponent>(go2.get());
	//renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("NobbinScreenshot.png"));
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Nobbin.png"));
	go2->AddComponent(std::move(renderComponent));
	go2->GetTransform()->SetLocalPosition(300, 300, 0);
	moveComponent = std::make_unique<dae::MoveComponent>(go2.get(), 200.0f);
	go2->AddComponent(std::move(moveComponent));
	/*healthComponent = std::make_unique<dae::HealthComponent>(go2.get());
	go2->AddComponent(std::move(healthComponent));
	scoreComponent = std::make_unique<dae::ScoreComponent>(go2.get());
	go2->AddComponent(std::move(scoreComponent))*/;
	hitboxComponent = std::make_unique<dae::HitboxComponent>(go2.get(), 50.f, 50.f);
	go2->AddComponent(std::move(hitboxComponent));
	auto enemyComponent = std::make_unique<dae::EnemyComponent>(go2.get(), go.get());
	go2->AddComponent(std::move(enemyComponent));
	go2->AddObserver(go->GetComponent<dae::ScoreComponent>());
	

	
	
	//rotatorComponent = std::make_unique<dae::RotatorComponent>(go2.get(), glm::vec3(0,0,0), 5.0f);
	//go2->AddComponent(std::move(rotatorComponent));

	//go2->SetParent(go.get(), false);

	////Pressed
	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, -1, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ -1, 0, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 1, 0, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputManager::ButtonState::PRESSED, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 1, 0 }));


	////Down
	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_X, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::DamageCommand>(go2.get()));
	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_A, dae::InputManager::ButtonState::DOWN, std::make_unique<dae::GainPointsCommand>(go2.get()));


	////Up
	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_UP, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_LEFT, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_RIGHT, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));

	//dae::InputManager::GetInstance().BindControllerCommand(XINPUT_GAMEPAD_DPAD_DOWN, dae::InputManager::ButtonState::UP, std::make_unique<dae::MoveCommand>(go2.get(), glm::vec3{ 0, 0, 0 }));



	scene.Add(std::move(go));

	//HUD displays for Digger2

	//Health display digger2
	//auto go3 = std::make_unique<dae::GameObject>();
	//go3->GetTransform()->SetLocalPosition(10, 330, 0);
	//textComponent = std::make_unique<dae::TextComponent>(go3.get(), "# lives: " + std::to_string(go2->GetComponent<dae::HealthComponent>()->GetHealth()), font.get());
	//go3->AddComponent(std::move(textComponent));
	//hpDisplayComponent = std::make_unique<dae::HPDisplay>(go3.get());
	//go3->AddComponent(std::move(hpDisplayComponent));
	//go2->AddObserver(go3->GetComponent<dae::HPDisplay>());
	//scene.Add(std::move(go3));

	//


	////Score display digger2
	//go3 = std::make_unique<dae::GameObject>();
	//go3->GetTransform()->SetLocalPosition(10, 360, 0);
	//textComponent = std::make_unique<dae::TextComponent>(go3.get(), "Score: " + std::to_string(go2->GetComponent<dae::ScoreComponent>()->GetScore()), font.get());
	//go3->AddComponent(std::move(textComponent));
	//scoreDisplayComponent = std::make_unique<dae::ScoreDisplay>(go3.get());
	//go3->AddComponent(std::move(scoreDisplayComponent));
	//go2->AddObserver(go3->GetComponent<dae::ScoreDisplay>());
	//scene.Add(std::move(go3));
	scene.Add(std::move(go2));

	
	//eventQueue->process();

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	

	return 0;
}
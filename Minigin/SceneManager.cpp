#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);

		scene->RemoveFlaggedObjects();
	}
}
 
//void dae::SceneManager::Render()
//{
//	for (const auto& scene : m_scenes)
//	{
//		scene->Render();
//	}
//}

void dae::SceneManager::FixedUpdate(float fixed_time_step)
{
	for (const auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixed_time_step);
	}
}

void dae::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->LateUpdate();
	}
}

dae::Scene* dae::SceneManager::GetScene(const int idx) const
{
	Scene* scene = m_scenes[idx].get();
	return scene;
}


dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}



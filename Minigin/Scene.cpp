#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;



Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.push_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

//std::vector<std::shared_ptr<GameObject>>& Scene::GetGameObjects() 
//{
//	return m_objects;
//}

//void dae::Scene::AComponentWasMarkedForDeletion()
//{
//	m_isThereAComponentToBeDeleted = true;
//}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	////if check necessary so it doesn't check all objects every update every time
	//if (m_isThereAComponentToBeDeleted == true)
	//{
	//	for (auto& object : m_objects)
	//	{
	//		object->RemoveFlaggedComponents();
	//	}
	//	m_isThereAComponentToBeDeleted = false;
	//}
	
}
//
//void Scene::Render() const
//{
//	for (const auto& object : m_objects)
//	{
//		object->Render();
//	}
//}


#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;



Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.push_back(std::move(object));
}

void Scene::Remove(dae::GameObject* pObject)
{
	for (auto& object : m_objects)
	{
		if (object.get() == pObject)
		{
			object->MarkForDeletion();
			m_mustAnObjectBeDeleted = true;

			break;
		}
		//m_ownerScene->AComponentWasMarkedForDeletion();
	}
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
	
}


void Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		object->LateUpdate();
	}

	if (m_mustAnObjectBeDeleted)
	{
		RemoveFlaggedObjects();
		m_mustAnObjectBeDeleted = false;
	}
}

//
//void Scene::Render() const
//{
//	for (const auto& object : m_objects)
//	{
//		object->Render();
//	}
//}

void Scene::RemoveFlaggedObjects()
{
	for (unsigned int idx{ 0 }; idx < m_objects.size(); ++idx)
	{
		if (m_objects[idx]->IsMarkedForDeletion())
		{
			m_objects[idx]->RemoveFlaggedComponents(); //remove components that are marked for deletion
			m_objects.erase(m_objects.begin() + idx);
			--idx; //to make sure the index doesn't go out of bounds and iterates over every element
		}
	}
}


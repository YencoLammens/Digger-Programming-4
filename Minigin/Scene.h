#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(GameObject* pObject);
		void RemoveAll();

		void Update(float deltaTime);
		void LateUpdate();
		/*void Render() const;*/
		void FixedUpdate(float fixedTimeStep);

		void RemoveFlaggedObjects();

		void ResetLevel();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


		//std::vector<std::shared_ptr<GameObject>>& GetGameObjects(); // Add this method

		//void AComponentWasMarkedForDeletion();

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector <std::unique_ptr<dae::GameObject>> m_objects;

		static unsigned int m_idCounter; 

		bool m_mustAnObjectBeDeleted{ false };

		//bool m_isThereAComponentToBeDeleted = false;
	};

}

#pragma once
#include <memory>
#include <vector>
#include "BaseComponent.h"
#include <glm.hpp>
#include "Scene.h"
#include "Observer.h"

namespace dae
{
	struct GameEvent;
	class Observer;
	class Transform;
	class GameObject final
	{
	public:
		GameObject();
		//GameObject(Scene* scene);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Component related
		void AddComponent(std::unique_ptr<BaseComponent> component);
		void RemoveComponent(BaseComponent* baseComponent);
		
		
		//Templates
		template <typename T>
		T HasComponentBeenAdded() const
		{
			for (const auto& component : m_componentsArr)
			{
				if (dynamic_cast<T>(component))
				{
					return true;
				}
			}
			return false;
		}

		//Tries to find the component type inside of the component vector by attempting to dynamic cast it to the given type, if it finds one, that one gets returned (the first one)
		template <typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_componentsArr)
			{
				if (auto castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}
			return nullptr;
		}


		//Observers
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void NotifyObservers(GameEvent event);

		
		//General methods
		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void LateUpdate();
		//void Render() const;

		//Parent-child related
		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent();

		Transform* GetTransform();
		
		std::vector<GameObject*> GetChildren();

		void MarkForDeletion();
		bool IsMarkedForDeletion() const { return m_toBeDeleted; }
		void RemoveFlaggedComponents();
	private:
		/*void SetThereIsAnOngoingEvent(bool isThereAnOngoingEvent);*/

		
		//Scene* m_ownerScene;

		
		void AddChild(GameObject* newChild);
		void RemoveChild(GameObject* orphanedChild);
		bool IsChild(GameObject* possibleChild);

		
		std::vector<Observer*> m_Observers;
		std::vector<std::unique_ptr<BaseComponent>> m_componentsArr;
		std::vector<GameObject*> m_ChildrenArr;
		GameObject* m_parent{nullptr};
		glm::vec3 m_worldPosition;
		glm::vec3 m_localPosition;
		std::unique_ptr<Transform> m_transform;

		bool m_positionIsDirty = false;
		bool m_mustAComponentBeDeleted = false;
		bool m_toBeDeleted = false;
	};
}

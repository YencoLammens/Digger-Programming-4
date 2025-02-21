#pragma once
#include <memory>
#include <vector>
#include "BaseComponent.h"
#include <glm.hpp>

namespace dae
{
	// todo: this should become final.
	class GameObject final
	{
	public:
		//void Update();
		//void Render() const;

		GameObject();
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
		bool HasComponentBeenAdded() const;

		//Tries to find the component type inside of the component vector by attempting to dynamic cast it to the given type, if it finds one, that one gets returned (the first one)
		template <typename T>
		std::unique_ptr<T> GetComponent() const;

		
		
		//General methods
		void Update();
		void FixedUpdate();
		void Render() const;

		void SetPositionDirty();


		//Parent-child related
		void SetParent(GameObject* parent, bool keepWorldPosition);
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
		void UpdateWorldPosition();

		void AddChild(GameObject* newChild);
		void RemoveChild(GameObject* orphanedChild);
		bool IsChild(GameObject* parent);



		


	private:
		void RemoveFlaggedComponents();
		std::vector<std::unique_ptr<BaseComponent>> m_componentsArr;
		std::vector<std::unique_ptr<GameObject>> m_ChildrenArr;
		GameObject* m_parent{nullptr};
		glm::vec3 m_worldPosition;
		glm::vec3 m_localPosition;

		bool m_positionIsDirty = false;
		
	};
}

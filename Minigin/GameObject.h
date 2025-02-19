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

		//Methods
		void AddComponent(std::unique_ptr<BaseComponent> component);
		void RemoveComponent(BaseComponent* baseComponent);
		
		
		//Templates
		template <typename T>
		bool HasComponentBeenAdded() const;

		//Tries to find the component type inside of the component vector by attempting to dynamic cast it to the given type, if it finds one, that one gets returned (the first one)
		template <typename T>
		std::unique_ptr<T> GetComponent() const;
		

		void Update();
		void FixedUpdate();
		void Render() const;

		const glm::vec3& GetWorldPosition();

	private:
		void RemoveFlaggedComponents();
		std::vector<std::unique_ptr<BaseComponent>> m_componentsArr;
		glm::vec3 m_worldPosition;
		
	};
}

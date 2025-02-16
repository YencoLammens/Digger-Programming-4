#pragma once
#include <memory>
#include <vector>
#include "BaseComponent.h"

namespace dae
{
	// todo: this should become final.
	class GameObject final
	{
	public:
		//void Update();
		//void Render() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//Methods
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);
		
		
		//Templates
		template <typename T>
		bool HasComponentBeenAdded() const;

		//Tries to find the component type inside of the component vector by attempting to dynamic cast it to the given type, if it finds one, that one gets returned (the first one)
		template <typename T>
		std::shared_ptr<T> GetComponent() const;
		/*{
			for (const auto& component : m_componentsArr)
			{
				if (auto castedComponent = std::dynamic_pointer_cast<T>(component))
				{
					return castedComponent;
				}
			}
			return nullptr;
		}*/

		void Update();
		void FixedUpdate();
		void Render() const;

	private:
		
		std::vector<std::shared_ptr<BaseComponent>> m_componentsArr;
	};
}

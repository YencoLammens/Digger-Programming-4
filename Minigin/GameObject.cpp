#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

dae::GameObject::GameObject()
    : m_worldPosition(0.0f, 0.0f, 0.0f)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	m_componentsArr.emplace_back(std::move(component));
}


void dae::GameObject::RemoveComponent(BaseComponent* toBeDeletedComponent)
{
    for (auto& component : m_componentsArr)
    {
        if (component.get() == toBeDeletedComponent)
        {
			component->m_ToBeDeleted = true;
            break;
        }
    }
}


template <typename T>
bool dae::GameObject::HasComponentBeenAdded() const
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

template <typename T>
std::unique_ptr<T> dae::GameObject::GetComponent() const
{
    for (const auto& component : m_componentsArr)
    {
        if (auto castedComponent = dynamic_cast<T>(component))
        {
            return castedComponent;
        }
    }
    return nullptr;
}

void dae::GameObject::Update()
{
    
    for (auto& component : m_componentsArr)
    {
        component->Update();
    }    
}

void dae::GameObject::FixedUpdate()
{
	for (auto& component : m_componentsArr)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
    {
        for (const auto& component : m_componentsArr)
        {
            component->Render();
        }
    }

}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
    return m_worldPosition;
}

void dae::GameObject::RemoveFlaggedComponents()
{
    m_componentsArr.erase(std::remove_if(m_componentsArr.begin(), m_componentsArr.end(),
        [](const std::unique_ptr<BaseComponent>& component) { return component->m_ToBeDeleted; }), m_componentsArr.end());
}

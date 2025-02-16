#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_componentsArr.emplace_back(component);
}


void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	m_componentsArr.erase(std::remove(m_componentsArr.begin(), m_componentsArr.end(), component), m_componentsArr.end());
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
std::shared_ptr<T> dae::GameObject::GetComponent() const
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
            if (component->GetType() == BaseComponent::Type::Render)
            {
				if (auto renderComponent = dynamic_cast<RenderComponent*>(component.get()))
				{
					renderComponent->Render();
				}
            }
            if (component->GetType() == BaseComponent::Type::Text)
            {
                if (auto textComponent = dynamic_cast<TextComponent*>(component.get()))
                {
                    textComponent->Render();
                }
            }
            if (component->GetType() == BaseComponent::Type::FPS)
            {
                if (auto fpsComponent = dynamic_cast<FPSComponent*>(component.get()))
                {
                    fpsComponent->Render();
                }
            }
            
        }
    }

}


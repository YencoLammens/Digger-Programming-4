#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

dae::GameObject::GameObject()
    : m_worldPosition(0.0f, 0.0f, 0.0f), m_localPosition(0.0f, 0.0f, 0.0f)
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

void dae::GameObject::SetPositionDirty()
{
    m_positionIsDirty = true;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_parent == parent)
        return;
    if (parent == nullptr)
        SetLocalPosition(GetWorldPosition());
    else
    {
        if (keepWorldPosition)
            SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
        SetPositionDirty();
    }
    if (m_parent) m_parent->RemoveChild(this);
    
    if (m_parent) m_parent->AddChild(this);
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
    return m_worldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
    m_localPosition = pos;
    SetPositionDirty();
}

void dae::GameObject::UpdateWorldPosition()
{
    if (m_positionIsDirty)
    {
        if (m_parent == nullptr)
            m_worldPosition = m_localPosition;
        else
            m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
    }
    m_positionIsDirty = false;
}

void dae::GameObject::AddChild(GameObject* newChild)
{
    m_ChildrenArr.emplace_back(newChild);
}

void dae::GameObject::RemoveChild(GameObject* orphanedChild)
{
    for (auto& child : m_ChildrenArr)
    {
        if (child.get() == orphanedChild)
        {
            //m_ChildrenArr.erase(orphanedChild); //fix this
        }
    }

}

bool dae::GameObject::IsChild(GameObject* parent)
{
    if (parent)
    {
        //make something fancy happen
    }
    return false;
}


void dae::GameObject::RemoveFlaggedComponents()
{
    m_componentsArr.erase(std::remove_if(m_componentsArr.begin(), m_componentsArr.end(),
        [](const std::unique_ptr<BaseComponent>& component) { return component->m_ToBeDeleted; }), m_componentsArr.end());
}

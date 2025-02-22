#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

dae::GameObject::GameObject(Scene* scene)
    : m_ownerScene(scene), m_worldPosition(0.0f, 0.0f, 0.0f), m_localPosition(0.0f, 0.0f, 0.0f)
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	m_componentsArr.push_back(std::move(component));
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
    m_ownerScene->AComponentWasMarkedForDeletion();
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
    m_ChildrenArr.push_back(newChild);
}

void dae::GameObject::RemoveChild(GameObject* orphanedChild)
{
    for (int idx{0}; idx < m_ChildrenArr.size(); ++idx )
    {
        if (m_ChildrenArr[idx] == orphanedChild)
        {
            m_ChildrenArr[idx]->SetParent(nullptr, true);
            m_ChildrenArr.erase(m_ChildrenArr.begin() + idx);
            return;
        }
    }

}

bool dae::GameObject::IsChild(GameObject* possibleChild)
{
    for (int idx{ 0 }; idx < m_ChildrenArr.size(); ++idx)
    {
        if (m_ChildrenArr[idx] == possibleChild)
        {
            return true;
        }
    }
    return false;
}


void dae::GameObject::RemoveFlaggedComponents()
{
    for (int idx{ 0 }; idx < m_componentsArr.size(); ++idx)
    {
        if (m_componentsArr[idx]->m_ToBeDeleted == true)
        {
            m_componentsArr.erase(m_componentsArr.begin() + idx);
            --idx; //to make sure the index doesn't go out of bounds and iterates over every element
        }
    }
}

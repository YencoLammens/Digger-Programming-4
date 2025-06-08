#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"


dae::GameObject::GameObject()
    : m_worldPosition(0.0f, 0.0f, 0.0f), m_localPosition(0.0f, 0.0f, 0.0f), m_transform(std::make_unique<Transform>(this))
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
			component->MarkForDeletion();
            m_mustAComponentBeDeleted = true;

            break;
        }
        //m_ownerScene->AComponentWasMarkedForDeletion();
    }
    
}

void dae::GameObject::AddObserver(Observer* observer)
{
    m_Observers.push_back(observer);
}

void dae::GameObject::RemoveObserver(Observer* observer)
{
    m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::GameObject::NotifyObservers(GameEvent event)
{
    if (m_Observers.empty()) return;

    for (Observer* observer : m_Observers)
    {
        observer->OnNotify(event, this);
    }
}

void dae::GameObject::Update(float deltaTime)
{

    for (auto& component : m_componentsArr)
    {
        component->Update(deltaTime);
    }

    
    


    
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
	for (auto& component : m_componentsArr)
	{
		component->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::LateUpdate()
{
	for (auto& component : m_componentsArr)
	{
		component->LateUpdate();
	}

    if (m_mustAComponentBeDeleted == true)
    {
        RemoveFlaggedComponents(); //Could cause issues in the future if components of game objects interact with each other, it's this or letting the components deletions happen in the scene which would make a lot of things accesible in an uncomfortable way as far as i can tell.
        m_mustAComponentBeDeleted = false;
    }
}

//void dae::GameObject::Render() const
//{
//     
//
//}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_parent == parent)
        return;
    if (parent == nullptr)
        m_transform->SetLocalPosition(m_transform->GetWorldPosition());
    else
    {
        if (keepWorldPosition)
            m_transform->SetLocalPosition(m_transform->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());
        m_transform->SetPositionDirty();
    }
    if (m_parent) m_parent->RemoveChild(this);
    m_parent = parent;
    if (m_parent) m_parent->AddChild(this);
}

dae::GameObject* dae::GameObject::GetParent()
{
    if (m_parent)
    {
        return m_parent;
    }
    return nullptr;
    
}

void dae::GameObject::AddChild(GameObject* newChild)
{
    m_ChildrenArr.push_back(newChild);
    //SetParent handles the logic
}

void dae::GameObject::RemoveChild(GameObject* orphanedChild)
{
    //Fix this, use std::algorithms
    for (unsigned int idx{0}; idx < m_ChildrenArr.size(); ++idx )
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
    for (unsigned int idx{ 0 }; idx < m_ChildrenArr.size(); ++idx)
    {
        if (m_ChildrenArr[idx] == possibleChild)
        {
            return true;
        }
    }
    return false;
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren()
{
    return m_ChildrenArr;
}

void dae::GameObject::MarkForDeletion()
{
	m_toBeDeleted = true;

	for (auto& child : m_ChildrenArr)
	{
		this->RemoveChild(child);
	}

	for (auto& observer : m_Observers)
	{
		this->RemoveObserver(observer);
	}

	for (auto& component : m_componentsArr)
	{
		component->MarkForDeletion();
	}
}




//void dae::GameObject::SetThereIsAnOngoingEvent(bool isThereAnOngoingEvent)
//{
//	m_thereIsAnOngoingEvent = isThereAnOngoingEvent;
//}

dae::Transform* dae::GameObject::GetTransform()
{
    return m_transform.get();
}


void dae::GameObject::RemoveFlaggedComponents()
{
    
    if (GameObject::GetComponent<dae::RenderComponent>())
    {
        dae::Renderer::GetInstance().RemoveRenderComponent(GameObject::GetComponent<dae::RenderComponent>());
    }

    for (unsigned int idx{ 0 }; idx < m_componentsArr.size(); ++idx)
    {
        if (m_componentsArr[idx]->IsMarkedForDeletion())
        {
            m_componentsArr.erase(m_componentsArr.begin() + idx);
            --idx; //to make sure the index doesn't go out of bounds and iterates over every element
        }
    }
}

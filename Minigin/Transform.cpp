#include "Transform.h"

dae::Transform::Transform(GameObject* owner) 
	:BaseComponent(owner), m_localPosition(0, 0, 0), m_worldPosition(0, 0, 0), m_positionIsDirty(false)
{

}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3(x, y, z));
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_positionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
	
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		if (GetOwner()->GetParent() == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = GetOwner()->GetParent()->GetTransform()->GetWorldPosition() + m_localPosition;
	}
	m_positionIsDirty = false;
}

bool dae::Transform::IsPositionDirty()
{
	return m_positionIsDirty;
}

void dae::Transform::SetPositionDirty()
{
	m_positionIsDirty = true;
	for (auto& child : GetOwner()->GetChildren())
	{
		child->GetTransform()->SetPositionDirty();
	}
}

void dae::Transform::Update(float elapsedSec)
{
	m_localPosition += elapsedSec;
}

void dae::Transform::FixedUpdate(float)
{
}



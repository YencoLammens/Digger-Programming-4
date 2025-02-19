#include "Transform.h"

dae::Transform::Transform(GameObject* parent) 
	:m_parent(parent), m_localPosition(0, 0, 0), m_worldPosition(0, 0, 0), m_positionIsDirty(false)
{

}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	m_positionIsDirty = true;
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
		if (m_parent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
	}
	m_positionIsDirty = false;
}


void dae::Transform::IsPositionDirty(bool isDirty)
{
	m_positionIsDirty = isDirty;
}



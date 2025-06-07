#include "GridMovementComponent.h"
#include "GameObject.h"
#include "Transform.h"

dae::GridMovementComponent::GridMovementComponent(GameObject* owner, float tileSize, float speed, TileMap* tilemap)
    : BaseComponent(owner), m_tileSize(tileSize), m_speed(speed), m_direction{ 0,0,0 }, m_targetDirection{ 0,0,0 }
{
	m_tileMap = tilemap;
}

void dae::GridMovementComponent::Update(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
    glm::vec3 gridPos = { pos.x / m_tileSize, pos.y / m_tileSize, 0 };

    if (IsAlignedToGrid()) {
        if (m_targetDirection != m_direction && CanMoveTo(gridPos, m_targetDirection))
            m_direction = m_targetDirection;

        if (!CanMoveTo(gridPos, m_direction))
            m_direction = { 0, 0, 0 };

        // Dig dirt tile
        if (m_tileMap && m_tileMap->GetTile(gridPos.x, gridPos.y) == dae::TileType::Dirt) {
            m_tileMap->SetTile(gridPos.x, gridPos.y, dae::TileType::Empty);
        }
    }

    // Smooth movement
    pos.x += m_direction.x * m_speed * deltaTime;
    pos.y += m_direction.y * m_speed * deltaTime;
    GetOwner()->GetTransform()->SetLocalPosition(pos);
}

void dae::GridMovementComponent::FixedUpdate(float)
{
}

void dae::GridMovementComponent::SetDirection(glm::vec3 dir)
{
	m_targetDirection = dir;
}

void dae::GridMovementComponent::SetMap(TileMap* tileMap)
{
    m_tileMap = tileMap;
}


bool dae::GridMovementComponent::IsAlignedToGrid() const
{
    glm::vec3 pos = GetOwner()->GetTransform()->GetWorldPosition();
    float gridSize = static_cast<float>(m_tileSize);

    return std::fmod(pos.x, gridSize) == 0.0f && std::fmod(pos.y, gridSize) == 0.0f;
}

bool dae::GridMovementComponent::CanMoveTo(glm::vec3& tilePos, glm::vec3& dir) const
{
    if (!m_tileMap) return true;

    glm::vec3 next = tilePos + dir;
    if (next.x < 0 || next.y < 0 || next.x >= m_tileMap->GetWidth() || next.y >= m_tileMap->GetHeight())
        return false;

    return m_tileMap->IsWalkable(next.x, next.y);
}

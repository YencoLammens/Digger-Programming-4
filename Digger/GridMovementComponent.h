#pragma once
#include <BaseComponent.h>
#include <glm.hpp>
#include "TileType.h"
#include "TileMap.h"
#include <memory>
namespace dae
{
	class GridMovementComponent : public BaseComponent
	{
    public:
        GridMovementComponent(GameObject* owner, float tileSize, float speed, TileMap* tileMap);

        void Update(float deltaTime) override;
		void FixedUpdate(float fixedTimeStep) override;
        void SetDirection(glm::vec3 dir);  // Called by input system
        void SetMap(TileMap* tileMap);  // Optional for collision

    private:
        bool IsAlignedToGrid() const;
        bool CanMoveTo(glm::vec3& tilePos, glm::vec3& dir) const;

        glm::vec3 m_direction;      // -1/0/1
        glm::vec3 m_targetDirection;      // Input requested direction
        float m_tileSize;
        float m_speed;

        TileMap* m_tileMap;
	};
}



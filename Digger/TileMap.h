#pragma once
#include <vector>
#include "TileType.h"

namespace dae
{
    class TileMap {
    public:
        TileMap(float width, float height, dae::TileType defaultType = dae::TileType::Dirt);

        dae::TileType GetTile(float x, float y) const;
        void SetTile(float x, float y, dae::TileType type);
        bool IsWalkable(float x, float y) const;

        float GetWidth() const { return width; }
        float GetHeight() const { return height; }

    private:
        float width, height;
        std::vector<std::vector<dae::TileType>> tiles;
    };
}


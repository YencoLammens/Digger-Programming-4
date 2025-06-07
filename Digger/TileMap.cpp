#include "TileMap.h"

dae::TileMap::TileMap(float width, float height, dae::TileType defaultType)
	: width(width), height(height), tiles(static_cast<size_t>(height), std::vector<dae::TileType>(static_cast<size_t>(width), defaultType))
{
}

dae::TileType dae::TileMap::GetTile(float x, float y) const
{
	int tileX = static_cast<int>(x);
	int tileY = static_cast<int>(y);
	return tiles.at(tileY).at(tileX);
}

void dae::TileMap::SetTile(float x, float y, dae::TileType type)
{
	int tileX = static_cast<int>(x);
	int tileY = static_cast<int>(y);
	tiles.at(tileY).at(tileX) = type;
}

bool dae::TileMap::IsWalkable(float x, float y) const
{
	auto type = GetTile(x, y);
	return type == dae::TileType::Empty;
}

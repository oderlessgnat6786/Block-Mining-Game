#include "block.h"
#include "types/BlockID.h"
#include "types/BlockType.h"
#include "types/ItemID.h"
#include <SFML/Graphics.hpp>

void Block::setTileCoords(int X, int Y)
{
    tileCoords = sf::Vector2i({X, Y});
}

sf::Vector2i Block::getTileCoords() const
{
    return tileCoords;
}

Block::Block(BlockID name, int X, int Y, float durability, BlockType type, ItemID item)
{
    this->name = name;
    this->durability = durability;
    this->type = type;
    this->item = item;
    setTileCoords(X, Y);
}

float Block::getDurability() const
{
    return durability;
}

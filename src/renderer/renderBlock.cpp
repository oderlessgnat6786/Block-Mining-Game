#include <SFML/Graphics.hpp>

#include "types/BlockID.h"
#include "types/ItemID.h"
#include "blocks/block.h"
#include "renderBlock.h"

#include "core/constants.h"

sf::Texture tileset("assets/textures/blocks.png");

void renderBlock(const Block &block, sf::RenderWindow &window, sf::Sprite &blockSprite, sf::Vector2i &pos)
{
    sf::Vector2i tileCoords = block.getTileCoords();
    if (!(tileCoords.x == -1 && tileCoords.y == -1))
    {
        blockSprite.setTextureRect(sf::IntRect({tileCoords.x * TILE_SIZE, tileCoords.y * TILE_SIZE}, {TILE_SIZE, TILE_SIZE}));
        blockSprite.setPosition({(float)(pos.x * TILE_SIZE), (float)(pos.y * TILE_SIZE)});
        window.draw(blockSprite);
    }
}
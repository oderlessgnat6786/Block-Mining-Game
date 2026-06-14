#include <SFML/Graphics.hpp>

#include "types/BlockID.h"
#include "types/ItemID.h"
#include "blocks/block.h"
#include "renderBlock.h"

#include "core/configParser.h"

sf::Texture tileset("assets/textures/blocks.png");

void renderBlock(const Block &block, sf::RenderWindow &window, sf::Sprite &blockSprite, sf::Vector2i &pos)
{
    sf::Vector2i tileCoords = block.getTileCoords();
    if (!(tileCoords.x == -1 && tileCoords.y == -1))
    {
        blockSprite.setTextureRect(sf::IntRect({tileCoords.x * Engine_Constants::getTileSize(), tileCoords.y * Engine_Constants::getTileSize()}, {Engine_Constants::getTileSize(), Engine_Constants::getTileSize()}));
        blockSprite.setPosition({(float)(pos.x * Engine_Constants::getTileSize()), (float)(pos.y * Engine_Constants::getTileSize())});
        window.draw(blockSprite);
    }
}
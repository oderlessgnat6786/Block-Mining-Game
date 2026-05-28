#include "types/BlockID.h"

#include "types/ItemID.h"
#include "blocks/block.h"
#pragma once

#include <SFML/Graphics.hpp>


void renderBlock(const Block& block, sf::RenderWindow& window, sf::Sprite& blockSprite,sf::Vector2i& pos);




#pragma once
#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include <optional>
#include "world/chunk.h"
#include "entities/player.h"

#include "blocks/BlockRegistry.h"

void input_mine(std::optional<sf::Vector2i> selectedBlock, Chunk &chunk, Player &plr, const BlockRegistry &registry,float dt);

std::optional<sf::Vector2i> input_getSelectedBlock(sf::Vector2f mousePos, sf::Vector2f plrPos);
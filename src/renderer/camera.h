#pragma once

#include <SFML/Graphics.hpp>

void renderCamera(sf::RenderWindow& window, sf::View& camera, sf::Vector2f target_pos, int TILE_SIZE, int blockRadius, int chunkWidth);
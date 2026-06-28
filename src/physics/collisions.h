#pragma once
#include "world/chunk.h"
#include "entities/player.h"

void movePlayer_X(Player& plr, Chunk& chunk,float newPos);

bool safeToPlaceBlock(sf::Vector2i pos, sf::Vector2f plrPos);


void movePlayer_Y(Player& plr, Chunk& chunk, float newPos);
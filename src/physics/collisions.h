#pragma once
#include "world/chunk.h"
#include "entities/player.h"
#include "types/BlockID.h"

void movePlayer_X(Player& plr, Chunk& chunk,float newPos);

bool safeToPlaceBlock(sf::Vector2i pos, sf::Vector2f plrPos);

void nudgePlayer(sf::Vector2i pos, Player &player);

bool checkSOLID(BlockID block);

void movePlayer_Y(Player& plr, Chunk& chunk, float newPos);
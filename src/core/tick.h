#pragma once
#include "entities/player.h"
#include "world/chunk.h"
#include <atomic>

struct plrInput{
    sf::Vector2f mousePos;
    bool isLeftClicking = false;
};

void tickGameplay(Player& plr,plrInput& inputData, Chunk& chunk, std::atomic<bool>& running);
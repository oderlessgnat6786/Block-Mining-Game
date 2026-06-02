#pragma once
#include <atomic>
#include "world/chunk.h"
#include "entities/player.h"

void renderWindow(sf::RenderWindow &window, std::atomic<bool> &running, Chunk &chunk, Player& plr);
#pragma once
#include "entities/player.h"
#include "world/chunk.h"
#include <atomic>

void tickGameplay(Player& plr, Chunk& chunk, std::atomic<bool>& running);
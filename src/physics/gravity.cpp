#include "gravity.h"

#include "entities/player.h"
#include "world/chunk.h"
#include "core/constants.h"
#include <SFML/Graphics.hpp>
#include "types/BlockID.h"

bool applyGravity(Player& plr, Chunk& chunk){
    sf::Vector2i blockPos = plr.getBlockPos();
    if (chunk.getBlock(blockPos.y-1,blockPos.x) == BlockID::AIR){
        return true;
    }
    return false;
}
#include "entities/player.h"
#include <SFML/Graphics.hpp>
#include "updater.h"
#include "world/chunk.h"
#include "physics/movement.h"
#include "core/configParser.h"
#include <vector>

void fixPlayerInVoid(Player& plr, Chunk& chunk){
    if (plr.getBlockPos().y > chunk.getChunkHeight()-1){
        std::vector<int> spawnPos = chunk.getSpawnPos();
        plr.updatePos(sf::Vector2f({(float)spawnPos.at(0)*Engine_Constants::getTileSize(),(float)spawnPos.at(1)*Engine_Constants::getTileSize()}));
    }
}

void update(Player& plr,Chunk& chunk, float dt){
    fixPlayerInVoid(plr,chunk);
    updatePos(plr,chunk,dt);
}
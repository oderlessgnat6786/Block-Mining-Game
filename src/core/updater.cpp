#include "entities/player.h"
#include <SFML/Graphics.hpp>
#include "updater.h"
#include "world/chunk.h"
#include "physics/collisions.h"
#include "core/constants.h"
#include <vector>

void updatePlayerPos(Player& plr,Chunk& chunk, float dt){

    sf::Vector2f pos = plr.getPos();
    sf::Vector2f velocity = plr.getVelocity();

    //X Axis Movement Update

    pos.x += (plr.getSpeed()*velocity.x)*dt;
    //pos.y += plr.getSpeed() + velocity.y*dt;
    movePlayer_X(plr,chunk,pos.x);

    //Update position and velocity

    pos = plr.getPos();
    velocity = plr.getVelocity();

    //Y Axis Movement Update
    
 

    velocity.y += GRAVITY*dt;



    velocity.y = (velocity.y > FALL_SPEED)?FALL_SPEED:velocity.y;

    plr.setVelocity_Y(velocity.y);


    pos.y += velocity.y*dt;


    movePlayer_Y(plr,chunk,pos.y);
}

void fixPlayerInVoid(Player& plr, Chunk& chunk){
    if (plr.getBlockPos().y > chunk.getChunkHeight()-1){
        std::vector<int> spawnPos = chunk.getSpawnPos();
        plr.updatePos(sf::Vector2f({(float)spawnPos.at(0)*TILE_SIZE,(float)spawnPos.at(1)*TILE_SIZE}));
    }
}

void update(Player& plr,Chunk& chunk, float dt){
    fixPlayerInVoid(plr,chunk);
    updatePlayerPos(plr,chunk,dt);
}
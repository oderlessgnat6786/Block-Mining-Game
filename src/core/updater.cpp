#include "entities/player.h"
#include <SFML/Graphics.hpp>
#include "updater.h"
#include <iostream>
void updatePlayerPos_X(Player& plr,float dt){
    sf::Vector2f velocity = plr.getVelocity();
    sf::Vector2f pos = plr.getPos();
    pos.x += (plr.getSpeed()*velocity.x)*dt;
    //pos.y += plr.getSpeed() + velocity.y*dt;
    plr.updatePos(pos);
}

void update(Player& plr, float dt){
    updatePlayerPos_X(plr,dt);
}
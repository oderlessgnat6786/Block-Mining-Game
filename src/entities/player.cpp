#include "player.h"
#include <SFML/Graphics.hpp>

const int TILE_SIZE = 32;

Player::Player(sf::Vector2i spawnPos, int hp)
{
    blockPos = spawnPos;
    this->hp = hp;
    pos = sf::Vector2f({(float)blockPos.x*TILE_SIZE,(float)blockPos.y*TILE_SIZE});
}
sf::Vector2i Player::getBlockPos(){
    return blockPos;
}

sf::Vector2f Player::getPos(){
    return pos;
}

sf::Vector2f Player::getVelocity(){
    return velocity;
}

void Player::setVelocity(sf::Vector2f velocity){
    this->velocity = pos;
}

void Player::updatePos(sf::Vector2f pos){
    this->pos = pos;
    blockPos = sf::Vector2i({(int)pos.x/TILE_SIZE,(int)pos.y/TILE_SIZE});
}

int Player::getHealth(){
    return hp;
}
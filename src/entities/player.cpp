#include "player.h"
#include <SFML/Graphics.hpp>
#include "core/constants.h"

Player::Player(sf::Vector2i spawnPos, int hp,float speed, float jumpPower)
{
    this->speed = speed;
    blockPos = spawnPos;
    this->hp = hp;
    pos = sf::Vector2f({(float)blockPos.x*TILE_SIZE,(float)blockPos.y*TILE_SIZE});
    this->jumpPower = jumpPower;
    onGround = true;
}

sf::Vector2i Player::getBlockPos(){
    return blockPos;
}

void Player::setVelocity_X(float x){
    this->velocity.x = x;
}

float Player::getSpeed(){
    return speed;
}

void Player::setVelocity_Y(float y){
    velocity.y = y;
}

sf::Vector2f Player::getPos(){
    return pos;
}

sf::Vector2f Player::getVelocity(){
    return velocity;
}

float Player::getJumpPower(){
    return jumpPower;
}

void Player::setGrounded(bool val)
{
    this->onGround = val;
}

bool Player::getGrounded()
{
    return onGround;
}

void Player::setVelocity(sf::Vector2f velocity){
    this->velocity = velocity;
}

void Player::setDirection(Direction direction){
    this->direction = direction;
}

Direction Player::getDirection(){
    return direction;
}

void Player::updatePos(sf::Vector2f pos){
    this->pos = pos;
    blockPos = sf::Vector2i({(int)pos.x/TILE_SIZE,(int)pos.y/TILE_SIZE});
}

int Player::getHealth(){
    return hp;
}
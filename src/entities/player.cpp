#include "player.h"
#include <SFML/Graphics.hpp>
#include "core/configParser.h"
#include "physics/unitConverter.h"
#include <cmath>

Player::Player(sf::Vector2i spawnPos, int hp,float speed, float jumpPower)
{
    //this->speed = speed;
    this->speed = convertToBlockUnits(speed);
    blockPos = spawnPos;
    this->hp = hp;
    pos = sf::Vector2f({(float)blockPos.x*Engine_Constants::getTileSize(),(float)blockPos.y*Engine_Constants::getTileSize()});
    this->jumpPower = std::sqrt(2*Engine_Constants::getGravity()*convertToBlockUnits(jumpPower));
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
    blockPos = sf::Vector2i({(int)std::floor(pos.x/Engine_Constants::getTileSize()),(int)std::floor(pos.y/Engine_Constants::getTileSize())});
}

int Player::getHealth(){
    return hp;
}
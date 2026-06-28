#include "player.h"
#include <SFML/Graphics.hpp>
#include "core/configParser.h"
#include "physics/unitConverter.h"
#include <cmath>
#include "types/BlockID.h"
#include "world/chunk.h"
#include "blocks/BlockRegistry.h"
#include "blocks/block.h"

Player::Player(sf::Vector2i spawnPos, int hp,float speed, float jumpPower,float miningSpeed)
{
    
    ActiveMine.mining = false;
    ActiveMine.targetPos = sf::Vector2i(-1,-1);
    ActiveMine.damage = 0.f;
    ActiveMine.durability = 100.f;


    this->miningSpeed = miningSpeed;
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

sf::Vector2i Player::getMiningTargetPos()
{
    return ActiveMine.targetPos;
}

float Player::getMiningSpeed()
{
    return miningSpeed;
}

float Player::getMiningProgress()
{
    if (ActiveMine.durability <= 0.f) return 0.f;
    return (ActiveMine.damage/ActiveMine.durability);
}

void Player::setMiningSpeed(float miningSpeed)
{
    this->miningSpeed = miningSpeed;
}

bool Player::isMining()
{
    return ActiveMine.mining;
}

void Player::mine(sf::Vector2i pos, Chunk &chunk, const BlockRegistry &registry, float dt)
{
    BlockID id = chunk.getBlock(pos.y,pos.x);

    if (ActiveMine.targetPos != pos){
        resetMining();
    }

    if (id != BlockID::AIR && id != BlockID::NONE && id != BlockID::BARRIER){
        ActiveMine.mining = true;
        ActiveMine.targetPos = pos;
        const Block& block = registry.getBlockDefinition(id);
        ActiveMine.durability = block.getDurability();
        ActiveMine.damage += miningSpeed*dt;
        
        if (ActiveMine.damage >= ActiveMine.durability){
            chunk.setBlock(pos.y,pos.x,BlockID::AIR);
            resetMining();
        }

    }
}

void Player::resetMining()
{
    ActiveMine.mining = false;
    ActiveMine.targetPos = sf::Vector2i(-1,-1);
    ActiveMine.damage = 0.f;
    ActiveMine.durability = 100.f;
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
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types/Direction.h"
#include "world/chunk.h"
#include "blocks/BlockRegistry.h"

class Player
{
private:
    sf::Vector2i blockPos; // block position (chunk coordinates)

    sf::Vector2f pos; // pixel position (window)

    sf::Vector2f velocity; // 2d vector representing velocities in x and y axes

    float speed; // set speed (works like the movement in hollow knight with no acceleration shit)

    int hp; // player health

    float jumpPower; // jump power

    bool onGround;

    float miningSpeed; // mining speed multiplier for block mining

    struct
    {
        bool mining;
        sf::Vector2i targetPos;
        float damage;
        float durability;
    } ActiveMine;

    Direction direction; // determines the players direction

public:
    Player(sf::Vector2i spawnPos, int hp, float speed, float jumpPower, float miningSpeed);

    sf::Vector2i getBlockPos();
    sf::Vector2f getPos();
    sf::Vector2f getVelocity();
    sf::Vector2i getMiningTargetPos();


    float getMiningSpeed();

    float getMiningProgress();

    void setMiningSpeed(float miningSpeed);

    bool isMining();

    

    void mine(sf::Vector2i pos, Chunk &chunk,const BlockRegistry& registry,float dt);

    void resetMining();

    void setVelocity_X(float x);

    void setVelocity_Y(float y);

    float getSpeed();

    float getJumpPower();

    void setGrounded(bool val);

    bool getGrounded();

    void setVelocity(sf::Vector2f velocity);
    void updatePos(sf::Vector2f pos1);
    void setDirection(Direction direction);

    Direction getDirection();

    int getHealth();
};
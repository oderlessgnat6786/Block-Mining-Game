#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "types/Direction.h"

class Player
{
private:
    sf::Vector2i blockPos; // block position (chunk coordinates)

    sf::Vector2f pos; // pixel position (window)

    sf::Vector2f velocity; // 2d vector representing velocities in x and y axes

    float speed; // set speed (works like the movement in hollow knight with no acceleration shit)

    int hp; // player health

    Direction direction; // determines the players direction

public:
    Player(sf::Vector2i spawnPos, int hp, float speed);

    sf::Vector2i getBlockPos();
    sf::Vector2f getPos();
    sf::Vector2f getVelocity();

    void setVelocity_X(float x);

    void setVelocity_Y(float y);

    float getSpeed();

    void setVelocity(sf::Vector2f velocity);
    void updatePos(sf::Vector2f pos1);
    void setDirection(Direction direction);

    Direction getDirection();

    int getHealth();
};
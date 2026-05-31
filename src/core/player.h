#pragma once
#include <vector>
#include <SFML/Graphics.hpp>


class Player{
    private:
        sf::Vector2i blockPos; //block position (chunk coordinates)
        
        sf::Vector2f pos; //pixel position (window)

        int hp;

    public:
        Player(sf::Vector2i spawnPos, int hp);
        sf::Vector2i getBlockPos();
        sf::Vector2f getPos();
        void updatePos(sf::Vector2f pos);
        int getHealth();
};
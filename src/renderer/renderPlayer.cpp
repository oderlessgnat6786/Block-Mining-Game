#include "renderPlayer.h"
#include <SFML/Graphics.hpp>

void renderPlayer(sf::RenderWindow& window, sf::Vector2f pos,int TILE_SIZE, sf::Sprite& plr){
    plr.setPosition(sf::Vector2f({pos.x,pos.y-TILE_SIZE}));
    window.draw(plr);
}
#include "camera.h"
#include <SFML/Graphics.hpp>



void renderCamera(sf::RenderWindow& window, sf::View& camera, sf::Vector2f pos, int TILE_SIZE, int blockRadius){

    float viewSize = (float)(TILE_SIZE*blockRadius*2);

    camera.setCenter(pos);
    camera.setSize(sf::Vector2f(viewSize,viewSize));
    window.setView(camera);
}
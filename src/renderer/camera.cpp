#include "camera.h"
#include <SFML/Graphics.hpp>

void renderCamera(sf::RenderWindow& window, sf::View& camera, sf::Vector2f target_pos, int TILE_SIZE, int blockRadius){

    //Note: target_pos refers to the current position of a target sprite like the player in this case

    float viewSize = (float)(blockRadius*TILE_SIZE*2);

    sf::Vector2f cameraPos;

	cameraPos.x= target_pos.x + (float)TILE_SIZE / 2.f;
	cameraPos.y = target_pos.y + (float)TILE_SIZE / 2.f;

    camera.setCenter(cameraPos);

    camera.setSize(sf::Vector2f(viewSize,viewSize));
    window.setView(camera);
}
#include "camera.h"
#include "core/configParser.h"
#include <SFML/Graphics.hpp>

void renderCamera(sf::RenderWindow& window, sf::View& camera, sf::Vector2f target_pos, int TILE_SIZE, int blockRadius, int chunkWidth){

    //Note: target_pos refers to the current position of a target sprite like the player in this case
    float windowRatio = (float)User_Settings::getWindowWidth()/(float)User_Settings::getWindowHeight();

    float viewHeight = (float)(blockRadius*TILE_SIZE*2);
    float viewWidth = windowRatio*viewHeight;
    sf::Vector2f cameraPos;

    float halfView = viewWidth/2.f;
    float halfViewHeight = viewHeight/2.f;
	cameraPos.x= target_pos.x + (float)TILE_SIZE / 2.f;
	cameraPos.y = target_pos.y + (float)TILE_SIZE / 2.f;

    if (cameraPos.x < halfView + TILE_SIZE)
       cameraPos.x = halfView + TILE_SIZE;

    if (cameraPos.x > chunkWidth*TILE_SIZE - halfView - TILE_SIZE)
        cameraPos.x = chunkWidth*TILE_SIZE - halfView - TILE_SIZE;

    if (cameraPos.y < halfViewHeight+ TILE_SIZE){
       cameraPos.y = halfViewHeight + TILE_SIZE;
    }
    
    camera.setCenter(cameraPos);

    camera.setSize(sf::Vector2f(viewWidth,viewHeight));
    camera.setViewport(sf::FloatRect({0.f,0.f},{1.f,1.f}));
    window.setView(camera);
}
#include "core/filepaths.h"
#include "core/configParser.h"

#include <SFML/Graphics.hpp>
#include "blockHighlights.h"

void renderBlockHighlights(sf::RenderWindow& window, sf::Texture& tileset,int stateID,sf::Vector2i pos){
    
    int scale = Engine_Constants::getTileSize();
    sf::Vector2f size({(float)scale,(float)scale});
    sf::Vector2f worldPos({(float)pos.x*scale,(float)pos.y*scale});

    if (stateID == 0){ //draw a black outline
        sf::RectangleShape selectionBox(size);
        selectionBox.setPosition(worldPos);
        selectionBox.setFillColor(sf::Color::Transparent);
        selectionBox.setOutlineColor(sf::Color::Black);
        selectionBox.setOutlineThickness(-3.f);
        window.draw(selectionBox);
    }else{
        sf::Sprite highlightSprite(tileset);

        highlightSprite.setTextureRect(sf::IntRect({(stateID-1)*scale,0},sf::Vector2i(size)));

        highlightSprite.setPosition(worldPos);
        window.draw(highlightSprite);
    }   
}
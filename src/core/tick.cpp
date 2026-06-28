#include "entities/player.h"
#include "world/chunk.h"
#include <atomic>
#include "input/keyboard_input.h"
#include "input/mouse_input.h"
#include <SFML/Graphics.hpp>
#include "core/updater.h"
#include "tick.h"
#include "blocks/BlockRegistry.h"

void tickGameplay(Player& plr, plrInput& inputData, Chunk& chunk, std::atomic<bool>& running){
    sf::Clock clock;
    BlockRegistry registry;
    while(running){
        float dt = clock.getElapsedTime().asSeconds(); // time elapsed since the last frame
		clock.restart();
        
        auto selectedBlock = input_getSelectedBlock(inputData.mousePos,plr.getPos());
        
        input_mine(selectedBlock,chunk,plr,registry,dt);
        
        input_Movement(plr);
        update(plr,chunk,dt);


        sf::sleep(sf::Time(sf::milliseconds(1)));
    }
}
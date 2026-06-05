#include "entities/player.h"
#include "world/chunk.h"
#include <atomic>
#include "input/keyboard_input.h"
#include <SFML/Graphics.hpp>
#include "core/updater.h"

void tickGameplay(Player& plr, Chunk& chunk, std::atomic<bool>& running){
    sf::Clock clock;
    while(running){
        float dt = clock.getElapsedTime().asSeconds(); // time elapsed since the last frame
		clock.restart();
        input_Movement(plr);
        update(plr,chunk,dt);
        sf::sleep(sf::Time(sf::milliseconds(1)));
    }
}
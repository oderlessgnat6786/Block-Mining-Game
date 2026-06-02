#include <iostream>
#include <string>

#include <world/chunk.h>
#include <world/cave_gen.h>

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "types/BlockID.h"
#include "types/BlockType.h"
#include "types/ItemID.h"

#include "renderer/renderTileMap.h"
#include "renderer/camera.h"
#include "renderer/renderPlayer.h"
#include "renderer/renderWindow.h"

#include "entities/player.h"

#include "core/constants.h"

#include "core/filepaths.h"

void movePlayer(Player& plr, sf::Vector2f distance){
	sf::Vector2f pos = plr.getPos();
	pos.x = pos.x + distance.x;
	pos.y = pos.y + distance.y;
	plr.updatePos(pos);
}

int main(int argI, char* args[])
{
	Filepaths::init(args[0]);

	int ar[8];
	for (int i = 0; i < 8; i++)
		std::cin >> ar[i];
	// cout << "Height || Width || SURFACE DEPTHS (MIN || MAX) || DIRT DEPTHS (MIN || MAX) || CHUNK OFFSETS (X || Y)";
	// Chunk ob = Chunk(32,100,5,28,2,6);


	Chunk ob = Chunk(ar[0], ar[1], ar[2], ar[3], ar[4], ar[5], ar[6], ar[7]);
	ob.print();



	std::vector<int> pos = ob.getSpawnPos();

	Player plr(sf::Vector2i({pos.at(0),pos.at(1)}),100);



	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH,WINDOW_HEIGHT}), gameTitle);

	window.setFramerateLimit(60);

	if (!window.setActive(false))
	{
		return -1;
	};

	std::atomic<bool> running(1);

	std::thread render(renderWindow, std::ref(window), std::ref(running), std::ref(ob), std::ref(plr));

	while (window.isOpen())
	{
		/* code */
		// std::cout << "main thread running" << std::endl;
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{

				running = false;

				render.join();

				window.close();

				break;
			}
			else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
				if (keyPressed->scancode == sf::Keyboard::Scancode::D){
					movePlayer(std::ref(plr),sf::Vector2f({1.0,0}));
				}
			}
		}


		sf::sleep(sf::milliseconds(10));
	}

	if (render.joinable())
	{
		running = false;
		render.join();
	}

	return 0;
}

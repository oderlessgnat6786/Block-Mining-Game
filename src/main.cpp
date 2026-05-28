#include <iostream>
#include <world/chunk.h>
#include <world/cave_gen.h>

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "types/BlockID.h"
#include "types/BlockType.h"
#include "types/ItemID.h"

#include "renderer/renderTileMap.h"

void renderThread(sf::RenderWindow& window, std::atomic<bool>& running, Chunk& chunk)
{

	if (!window.setActive(true))
	{
		
		running = false;
		return;
	}

	sf::Texture tileset;
	if (!tileset.loadFromFile("assets/textures/blocks.png")){
		
		running = false;
		return;
	}


	while (running)
	{

		window.clear(sf::Color::White);
		std::cerr << "[2] Window cleared..." << std::endl;
		renderChunk(chunk,tileset,window);
		std::cerr << "[3] Window cleared..." << std::endl;
		window.display();
	}
}

int main()
{

	sf::Texture tileset("assets/textures/blocks.png");	

	int ar[8];
	for (int i = 0; i < 8; i++)
		std::cin >> ar[i];
	// cout << "Height || Width || SURFACE DEPTHS (MIN || MAX) || DIRT DEPTHS (MIN || MAX) || CHUNK OFFSETS (X || Y)";
	// Chunk ob = Chunk(32,100,5,28,2,6);

	Chunk ob = Chunk(ar[0], ar[1], ar[2], ar[3], ar[4], ar[5], ar[6], ar[7]);

	sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Test",sf::Style::Close);

	window.setFramerateLimit(24);

	if (!window.setActive(false))
	{
		return -1;
	};

	std::atomic<bool> running(1);

	
	std::thread render(renderThread, std::ref(window), std::ref(running), std::ref(ob));

	while (window.isOpen())
	{
		/* code */
		//std::cout << "main thread running" << std::endl;
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{

				running = false;
				
				render.join();

				window.close();

				break;
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

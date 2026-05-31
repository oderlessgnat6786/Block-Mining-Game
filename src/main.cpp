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
#include "renderer/camera.h"
#include "renderer/renderPlayer.h"

#include "core/player.h"

const int TILE_SIZE = 32;
const int blockRadius = 10;

void renderThread(sf::RenderWindow &window, std::atomic<bool> &running, Chunk &chunk, Player& plr)
{

	if (!window.setActive(true))
	{

		running = false;
		return;
	}

	sf::Texture tileset;
	if (!tileset.loadFromFile("assets/textures/blocks.png"))
	{

		running = false;
		return;
	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/textures/player.png"))
	{
		running = false;
		return;
	}

	sf::View camera;

	sf::Sprite player(playerTexture);

	sf::Vector2f pos = plr.getPos();

	struct
	{
		float X, Y;
	} cameraPos;

	cameraPos.X = pos.x + (float)TILE_SIZE / 2.f;
	cameraPos.Y = pos.y + (float)TILE_SIZE / 2.f;

	while (running)
	{

		window.clear(sf::Color{214, 215, 255});
		renderCamera(window, camera, sf::Vector2f(cameraPos.X, cameraPos.Y), TILE_SIZE, blockRadius);

		renderChunk(chunk, tileset, window);

		renderPlayer(window,plr.getPos(),TILE_SIZE,player);
		
		window.display();
	}

	window.setActive(false);
}

int main()
{

	int ar[8];
	for (int i = 0; i < 8; i++)
		std::cin >> ar[i];
	// cout << "Height || Width || SURFACE DEPTHS (MIN || MAX) || DIRT DEPTHS (MIN || MAX) || CHUNK OFFSETS (X || Y)";
	// Chunk ob = Chunk(32,100,5,28,2,6);

	Chunk ob = Chunk(ar[0], ar[1], ar[2], ar[3], ar[4], ar[5], ar[6], ar[7]);
	ob.print();

	std::vector<int> pos = ob.getSpawnPos();

	Player plr(sf::Vector2i({pos.at(0),pos.at(1)}),100);

	sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Boannt", sf::Style::Close);

	window.setFramerateLimit(24);

	if (!window.setActive(false))
	{
		return -1;
	};

	std::atomic<bool> running(1);

	std::thread render(renderThread, std::ref(window), std::ref(running), std::ref(ob), std::ref(plr));

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

#include <SFML/Graphics.hpp>
#include <atomic>
#include <vector>
#include "world/chunk.h"
#include "entities/player.h"
#include "renderer/renderTileMap.h"
#include "renderer/camera.h"
#include "renderer/renderPlayer.h"
#include "core/constants.h"
#include "core/filepaths.h"

void renderWindow(sf::RenderWindow &window, std::atomic<bool> &running, Chunk &chunk, Player& plr)
{

	if (!window.setActive(true))
	{

		running = false;
		return;
	}

	sf::Texture tileset;
	if (!tileset.loadFromFile(Filepaths::getAsset("textures/blocks.png")))
	{

		running = false;
		return;
	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile(Filepaths::getAsset("textures/player.png")))
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
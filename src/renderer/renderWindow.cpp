#include <SFML/Graphics.hpp>
#include <atomic>
#include <vector>
#include "world/chunk.h"
#include "entities/player.h"
#include "renderer/renderTileMap.h"
#include "renderer/camera.h"
#include "renderer/renderPlayer.h"
#include "core/configParser.h"
#include "core/filepaths.h"

void renderWindow(sf::RenderWindow &window, std::atomic<bool> &running, Chunk &chunk, Player& plr)
{
	if (!window.setActive(true))
	{

		running = false;
		return;
	}

	window.setFramerateLimit(60);

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

	sf::Sprite playerSprite(playerTexture);

	while (running)
	{

		window.clear(sf::Color{214, 215, 255});
		
		renderCamera(window, camera, plr.getPos(), Engine_Constants::getTileSize(),User_Settings::getBlockRadius(),chunk.getChunkWidth());

		renderChunk(chunk, tileset, window);

		renderPlayer(window,plr.getPos(),Engine_Constants::getTileSize(),playerSprite);
		
		window.display();
	}

	window.setActive(false);
}
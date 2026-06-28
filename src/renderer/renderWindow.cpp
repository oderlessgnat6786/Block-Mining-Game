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

#include "renderer/blockHighlights.h"
#include "input/mouse_input.h"

void renderWindow(sf::RenderWindow &window, std::atomic<bool> &running, Chunk &chunk, Player &plr)
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

	sf::Texture blockHighlightsTexture;
	if (!blockHighlightsTexture.loadFromFile(Filepaths::getAsset("textures/block_highlights.png")))
	{
		running = false;
		return;
	}

	blockHighlightsTexture.setSmooth(false);
	playerTexture.setSmooth(false);
	tileset.setSmooth(false);


	sf::View camera;

	sf::Sprite playerSprite(playerTexture);

	while (running)
	{

		window.clear(sf::Color{214, 215, 255});

		renderCamera(window, camera, plr.getPos(), Engine_Constants::getTileSize(), User_Settings::getBlockRadius(), chunk.getChunkWidth());

		renderChunk(chunk, tileset, blockHighlightsTexture, window);

		renderPlayer(window, plr.getPos(), Engine_Constants::getTileSize(), playerSprite);

		sf::Vector2f playerCenter = plr.getPos();
		playerCenter.x += Engine_Constants::getTileSize() / 2.0f;
		playerCenter.y += Engine_Constants::getTileSize() / 2.0f;


		auto selectedBlock = input_getSelectedBlock(window.mapPixelToCoords(sf::Mouse::getPosition(window),camera), playerCenter);

		if (plr.isMining()){
			float progress = plr.getMiningProgress();

			int state = 1 + (int)(progress*4.95f);
			renderBlockHighlights(window,blockHighlightsTexture,state,plr.getMiningTargetPos());
		}else if (selectedBlock.has_value())
		{
			renderBlockHighlights(window, blockHighlightsTexture, 0, selectedBlock.value());
		}

		window.display();
	}

	window.setActive(false);
}
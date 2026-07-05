#include <string>

#include <world/chunk.h>
#include <world/cave_gen.h>

#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "types/BlockID.h"
#include "types/BlockType.h"
#include "types/ItemID.h"

#include "renderer/renderWindow.h"

#include "entities/player.h"

#include "core/configParser.h"
#include "core/filepaths.h"
#include "core/tick.h"

int main(int argI, char *args[])
{
	Filepaths::init(args[0]);
	User_Settings::load();
	Engine_Constants::load();
	BlockRegistry registry;

	Chunk ob = Chunk(Engine_Constants::getChunkHeight(), Engine_Constants::getChunkWidth(), Engine_Constants::getSurfaceMin(), Engine_Constants::getSurfaceMax(), Engine_Constants::getDirtMin(), Engine_Constants::getDirtMax(), Engine_Constants::getOffsetX(), Engine_Constants::getOffsetY());

	std::vector<int> pos = ob.getSpawnPos();

	Player plr(sf::Vector2i({pos.at(0), pos.at(1)}), Engine_Constants::getHealth(), Engine_Constants::getSpeed(), Engine_Constants::getJumpPower(), Engine_Constants::getMiningSpeed());

	sf::RenderWindow window(sf::VideoMode({User_Settings::getWindowWidth(), User_Settings::getWindowHeight()}), Engine_Constants::getGameTitle());

	if (!window.setActive(false))
	{
		return -1;
	};

	std::atomic<bool> running(1);

	plrInput inputData;

	std::thread render(renderWindow, std::ref(window), std::ref(running), std::ref(ob), std::ref(plr));
	std::thread tickThread(tickGameplay, std::ref(plr), std::ref(inputData), std::ref(ob), std::ref(running));

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{

				running = false;

				render.join();

				window.close();

				break;
			}
			else if (event->is<sf::Event::Resized>())
			{
				sf::Vector2u size = window.getSize();
				User_Settings::setWindowHeight(size.y);
				User_Settings::setWindowWidth(size.x);
			}else if (const auto* button = event->getIf<sf::Event::MouseButtonPressed>()){
				if (button->button == sf::Mouse::Button::Right){
					inputData.isRightClicking = true;
				}
			}
		}

		inputData.isLeftClicking = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		
		if (inputData.isLeftClicking || inputData.isRightClicking)
		{
			sf::View camera = window.getView();
			inputData.mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
		}

		sf::sleep(sf::Time(sf::milliseconds(1)));
	}

	if (render.joinable())
	{
		running = false;
		render.join();
	}

	if (tickThread.joinable())
	{
		running = false;
		tickThread.join();
	}

	return 0;
}

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

	Chunk ob = Chunk(Engine_Constants::getChunkHeight(),Engine_Constants::getChunkWidth(),Engine_Constants::getSurfaceMin(),Engine_Constants::getSurfaceMax(),Engine_Constants::getDirtMin(),Engine_Constants::getDirtMax(),Engine_Constants::getOffsetX(),Engine_Constants::getOffsetY());

	std::vector<int> pos = ob.getSpawnPos();

	Player plr(sf::Vector2i({pos.at(0), pos.at(1)}),Engine_Constants::getHealth(),Engine_Constants::getSpeed(),Engine_Constants::getJumpPower());

	sf::RenderWindow window(sf::VideoMode({User_Settings::getWindowWidth(),User_Settings::getWindowHeight()}), Engine_Constants::getGameTitle());

	if (!window.setActive(false))
	{
		return -1;
	};

	std::atomic<bool> running(1);



	std::thread render(renderWindow, std::ref(window), std::ref(running), std::ref(ob), std::ref(plr));
	std::thread tickThread(tickGameplay, std::ref(plr),std::ref(ob),std::ref(running));

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
			}else if(event->is<sf::Event::Resized>()){
				sf::Vector2u size = window.getSize();
				User_Settings::setWindowHeight(size.y);
				User_Settings::setWindowWidth(size.x);
			}
			// else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
			// if (keyPressed->scancode == sf::Keyboard::Scancode::D){
			//	movePlayer(std::ref(plr),sf::Vector2f({1.0,0}));
			// }
			//}
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

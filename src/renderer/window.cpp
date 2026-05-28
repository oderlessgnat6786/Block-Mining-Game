#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "types/BlockID.h"
#include "types/BlockType.h"
#include "types/ItemID.h"

#include "renderer/renderTileMap.h"



void renderThread(sf::RenderWindow &window, std::atomic<bool> &running)
{

    if (!window.setActive(true))
    {
        running = false;
        return;
    }

    sf::Texture texture("assets/textures/sfml.png");
    sf::Font font("assets/fonts/Roboto_Flex/RobotoFlex.ttf");

    while (running)
    {
        window.clear(sf::Color::White);
        
        renderTileMap()
        
        window.display();
    }
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({1024, 1024}), "Test");

    window.setFramerateLimit(24);

    if (!window.setActive(false))
    {
        return -1;
    };

    std::atomic<bool> running(1);

    std::thread render(renderThread, std::ref(window), std::ref(running));

    while (window.isOpen())
    {
        /* code */

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
    }

    if (render.joinable())
    {
        running = false;
        render.join();
    }

    return 0;
}

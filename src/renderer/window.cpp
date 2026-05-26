#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

void renderThread(sf::RenderWindow &window, std::atomic<bool> &running)
{

    if (!window.setActive(true))
    {
        running = false;
        return;
    }

    sf::Texture texture("assets/textures/sfml.png");
    sf::Font font("assets/fonts/Roboto_Flex/RobotoFlex.ttf");


    sf::Sprite sprite(texture);
    sprite.setPosition({300.0f,300.0f});
    sprite.setScale({0.1,0.1});

    sf::Text txt(font);
    txt.setString("Test");
    txt.setCharacterSize(24);
    txt.setFillColor(sf::Color::Black);
    txt.setPosition({500.f,400.f});


    sf::RectangleShape block({32,32});
    block.setFillColor(sf::Color::Blue);
    block.setPosition({200,200});


    while (running)
    {
        window.clear(sf::Color::White);

        window.draw(sprite);
        window.draw(txt);
        window.draw(block);
        window.display();
    }
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test");

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

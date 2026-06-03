#include "keyboard_input.h"
#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "types/Direction.h"



/*void set_velocity(Direction direction, Player &plr)
{
    float x;
    if (direction == Direction::RIGHT)
    {
        x = 1.f;
    }
    else if (direction == Direction::LEFT)
    {
        x = -1.f;
    }
    else if (direction == Direction::NONE)
    {
        x = 0;
    }
    x_intent += x;
    plr.setVelocity_X(x_intent);
}*/

void input_Movement(Player &plr)
{
    float x_intent = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        plr.setDirection(Direction::RIGHT);
        x_intent += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        plr.setDirection(Direction::LEFT);
        x_intent += -1.f;
    }
    if (x_intent == 0)
        plr.setDirection(Direction::NONE);

    plr.setVelocity_X(x_intent);
}
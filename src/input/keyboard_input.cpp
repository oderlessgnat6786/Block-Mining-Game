#include "keyboard_input.h"
#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "types/Direction.h"

float sprint(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
        return 2.f;
    return 1.f;
}

void input_Movement(Player &plr)
{
    float x_intent = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        plr.setDirection(Direction::RIGHT);
        x_intent += sprint();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        plr.setDirection(Direction::LEFT);
        x_intent += -sprint();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && plr.getGrounded())
    {
        plr.setVelocity_Y(-plr.getJumpPower());
        plr.setGrounded(false);
    }
    if (x_intent == 0)
        plr.setDirection(Direction::NONE);

    plr.setVelocity_X(x_intent);
}
#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "world/chunk.h"
#include "collisions.h"
#include "core/constants.h"
#include <cmath>

int calculateSteps(float d)
{
    return (int)std::ceil((d + safe_step) / safe_step);
}

void updatePos(Player &plr, Chunk &chunk, float dt)
{

    sf::Vector2f pos = plr.getPos();
    sf::Vector2f velocity = plr.getVelocity();

    // Find magnitude of maximum displacements in x and y axes
    float max_dx = (plr.getSpeed() * velocity.x) * dt; // X
    
    float projected_Vy = velocity.y + GRAVITY*dt; // Y
    projected_Vy = (projected_Vy > FALL_SPEED) ? FALL_SPEED : projected_Vy;
    
    float max_dy = projected_Vy*dt;

    int steps = calculateSteps(std::max(std::abs(max_dx), std::abs(max_dy)));

    float subDt = dt/(float)steps;
    
    /*
        
        pos.y += dy;
    */


    for (int i = 1;i<=steps;i++){
        float dx = (velocity.x*plr.getSpeed())*subDt;
        pos.x += dx;
        movePlayer_X(plr,chunk,pos.x);

        velocity.y += GRAVITY*subDt;

        velocity.y = (velocity.y > FALL_SPEED)?FALL_SPEED:velocity.y;

        plr.setVelocity_Y(velocity.y);

        float dy = velocity.y*subDt;

        pos.y += dy;

        movePlayer_Y(plr, chunk, pos.y);

        pos = plr.getPos();
    }
    
}
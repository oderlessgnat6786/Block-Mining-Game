#include <SFML/Graphics.hpp>
#include "entities/player.h"
#include "world/chunk.h"
#include "collisions.h"
#include "core/configParser.h"
#include <cmath>

int calculateSteps(float d)
{
    return (int)std::ceil((d + Engine_Constants::getSafeStep()) / Engine_Constants::getSafeStep());
}

void updatePos(Player &plr, Chunk &chunk, float dt)
{

    sf::Vector2f pos = plr.getPos();
    sf::Vector2f velocity = plr.getVelocity();

    // Find magnitude of maximum displacements in x and y axes
    float max_dx = (plr.getSpeed() * velocity.x) * dt; // X
    
    float projected_Vy = velocity.y + Engine_Constants::getGravity()*dt; // Y
    projected_Vy = (projected_Vy > Engine_Constants::getFallSpeed()) ? Engine_Constants::getFallSpeed() : projected_Vy;
    
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

        velocity.y += Engine_Constants::getGravity()*subDt;

        velocity.y = (velocity.y > Engine_Constants::getFallSpeed())?Engine_Constants::getFallSpeed():velocity.y;

        plr.setVelocity_Y(velocity.y);

        float dy = velocity.y*subDt;

        pos.y += dy;

        movePlayer_Y(plr, chunk, pos.y);

        pos = plr.getPos();
    }
    
}
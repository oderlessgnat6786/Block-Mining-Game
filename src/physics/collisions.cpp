#include "world/chunk.h"
#include "entities/player.h"
#include "collisions.h"
#include <SFML/Graphics.hpp>
#include "core/constants.h"
#include "types/BlockID.h"
#include "types/Direction.h"

#include <iostream>

bool checkSOLID(BlockID block)
{
    return (block != BlockID::AIR && block != BlockID::NONE);
}

void movePlayer_X(Player &plr, Chunk &chunk, float newPos)
{

    sf::Vector2i oldBlockPos = plr.getBlockPos();

    float v = plr.getVelocity().x;

    float leadingEdge_X = v > 0 ? (newPos + TILE_SIZE) : newPos;
    int X = (int)(leadingEdge_X / TILE_SIZE);
    int bottomY = oldBlockPos.y;
    int topY = bottomY - 1;

    if (checkSOLID(chunk.getBlock(bottomY, X)) || checkSOLID(chunk.getBlock(topY, X)))
    {

        newPos = v > 0 ? (X * TILE_SIZE - TILE_SIZE) : (X * TILE_SIZE + TILE_SIZE);
    }
    plr.updatePos(sf::Vector2f({newPos, plr.getPos().y}));
}

void movePlayer_Y(Player &plr, Chunk &chunk, float newPos)
{

    sf::Vector2i oldBlockPos = plr.getBlockPos();
    sf::Vector2f oldPos = plr.getPos();
    float v = plr.getVelocity().y;



    float leadingEdge_Y = v > 0 ? (newPos + TILE_SIZE) : (newPos - TILE_SIZE);
    int Y = (int)(leadingEdge_Y / TILE_SIZE);

    int leftX = (int)(oldPos.x / TILE_SIZE);


    int rightX = (int)((oldPos.x + TILE_SIZE - 1.f) / TILE_SIZE);

 

    if (checkSOLID(chunk.getBlock(Y, leftX)) || checkSOLID(chunk.getBlock(Y, rightX)))
    {
        plr.setVelocity_Y(0);
        if (v > 0)
        {
            newPos = (Y * TILE_SIZE - TILE_SIZE);
            plr.setGrounded(true);
        }
        else if (v < 0)
        {

            newPos = (Y * TILE_SIZE + 2 * TILE_SIZE);
        }
    }
    else
    {
        if (v > 0.1f)
        {
            plr.setGrounded(false);
        }
    }

    plr.updatePos(sf::Vector2f({oldPos.x, newPos}));
}
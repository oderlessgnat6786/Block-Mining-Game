#include "world/chunk.h"
#include "entities/player.h"
#include "collisions.h"
#include <SFML/Graphics.hpp>
#include "core/configParser.h"
#include "types/BlockID.h"
#include "types/Direction.h"
#include <cmath>

bool checkSOLID(BlockID block)
{
    return (block != BlockID::AIR && block != BlockID::NONE);
}

void nudgePlayer(sf::Vector2i pos, Player &player)
{

    sf::Vector2f plrPos = player.getPos();

    float TILE_SIZE = (float)Engine_Constants::getTileSize();

    struct AABB
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    AABB plr = {
        plrPos.x,
        (plrPos.x + TILE_SIZE),
        (plrPos.y - TILE_SIZE),
        (plrPos.y + TILE_SIZE)};

    AABB sel{
        pos.x * TILE_SIZE,
        (pos.x * TILE_SIZE) + TILE_SIZE,
        pos.y * TILE_SIZE,
        (pos.y * TILE_SIZE) + TILE_SIZE};

    bool intersecting = (plr.left < sel.right && plr.right > sel.left && plr.top < sel.bottom && plr.bottom > sel.top);
    if (intersecting)
    {
        plrPos.y = sel.top - TILE_SIZE;
        player.updatePos(plrPos);
        if (player.getVelocity().y > 0)
        {
            player.setVelocity_Y(0.f);
            player.setGrounded(true);
        }
    }
}

bool safeToPlaceBlock(sf::Vector2i pos, sf::Vector2f plrPos)
{
    float TILE_SIZE = (float)Engine_Constants::getTileSize();

    float margin = 0.1f;
    float feetMargin = 0.3f * TILE_SIZE;

    struct AABB
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    AABB plr = {
        plrPos.x + margin,
        (plrPos.x + TILE_SIZE) - margin,
        (plrPos.y - TILE_SIZE) + margin,
        (plrPos.y + TILE_SIZE) - feetMargin};

    AABB sel{
        pos.x * TILE_SIZE,
        (pos.x * TILE_SIZE) + TILE_SIZE,
        pos.y * TILE_SIZE,
        (pos.y * TILE_SIZE) + TILE_SIZE};

    bool intersecting = (plr.left < sel.right && plr.right > sel.left && plr.top < sel.bottom && plr.bottom > sel.top);

    return !intersecting;
}

void movePlayer_X(Player &plr, Chunk &chunk, float newPos)
{

    sf::Vector2f pos = plr.getPos();

    float v = plr.getVelocity().x;

    float oldleadingEdge_X = v > 0 ? (pos.x + Engine_Constants::getTileSize()) : pos.x;
    float newleadingEdge_X = v > 0 ? (newPos + Engine_Constants::getTileSize()) : newPos;

    int startX = (int)std::floor(oldleadingEdge_X / Engine_Constants::getTileSize());
    int endX = (int)std::floor(newleadingEdge_X / Engine_Constants::getTileSize());

    int topY = (int)std::floor((pos.y - Engine_Constants::getTileSize()) / Engine_Constants::getTileSize());
    int middleY = (int)std::floor(pos.y / Engine_Constants::getTileSize());
    int bottomY = (int)std::floor((pos.y + Engine_Constants::getTileSize() - 1.f) / Engine_Constants::getTileSize());

    int step = ((v > 0) ? 1 : -1);

    for (int i = startX; i != endX + step; i += step)
    {
        if (checkSOLID(chunk.getBlock(bottomY, i)) || checkSOLID(chunk.getBlock(middleY, i)) || checkSOLID(chunk.getBlock(topY, i)))
        {
            newPos = v > 0 ? (i * Engine_Constants::getTileSize() - Engine_Constants::getTileSize()) : (i * Engine_Constants::getTileSize() + Engine_Constants::getTileSize());
            break;
        }
    }
    plr.updatePos(sf::Vector2f({newPos, plr.getPos().y}));
}

void movePlayer_Y(Player &plr, Chunk &chunk, float newPos)
{

    sf::Vector2i oldBlockPos = plr.getBlockPos();
    sf::Vector2f oldPos = plr.getPos();
    float v = plr.getVelocity().y;

    float oldleadingEdge_Y = v > 0 ? (oldPos.y + Engine_Constants::getTileSize()) : (oldPos.y - Engine_Constants::getTileSize());
    float newleadingEdge_Y = v > 0 ? (newPos + Engine_Constants::getTileSize()) : (newPos - Engine_Constants::getTileSize());

    int startY = (int)std::floor(oldleadingEdge_Y / Engine_Constants::getTileSize());
    int endY = (int)std::floor(newleadingEdge_Y / Engine_Constants::getTileSize());

    bool hitfloor = false;

    int leftX = (int)std::floor(oldPos.x / Engine_Constants::getTileSize());

    int rightX = (int)(std::floor)((oldPos.x + Engine_Constants::getTileSize() - 1.f) / Engine_Constants::getTileSize());

    int step = ((v > 0) ? 1 : -1);

    for (int i = startY; i != endY + step; i += step)
    {

        if (checkSOLID(chunk.getBlock(i, leftX)) || checkSOLID(chunk.getBlock(i, rightX)))
        {
            plr.setVelocity_Y(0);
            if (v > 0)
            {
                newPos = (i * Engine_Constants::getTileSize() - Engine_Constants::getTileSize());
                plr.setGrounded(true);
                hitfloor = true;
            }
            else if (v < 0)
            {

                newPos = (i * Engine_Constants::getTileSize() + 2 * Engine_Constants::getTileSize());
            }
            break;
        }
    }

    if (!hitfloor && v > 0.1f)
    {
        plr.setGrounded(false);
    }

    plr.updatePos(sf::Vector2f({oldPos.x, newPos}));
}
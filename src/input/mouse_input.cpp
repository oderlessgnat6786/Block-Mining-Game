#include <SFML/Graphics.hpp>
#include "core/configParser.h"
#include "mouse_input.h"
#include <cmath>
#include <optional>

#include "world/chunk.h"
#include "types/BlockID.h"
#include "entities/player.h"
#include "blocks/BlockRegistry.h"
#include "physics/collisions.h"

BlockID currentBlock = BlockID::DIRT;

void input_mineBlock(std::optional<sf::Vector2i> selectedBlock, Chunk &chunk, Player &plr, const BlockRegistry &registry, float dt)
{

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (selectedBlock.has_value())
        {
            plr.mine(selectedBlock.value(), chunk, registry, dt);
        }
        else
        {
            plr.resetMining();
        }
    }
    else
    {
        plr.resetMining();
    }
}

void input_placeBlock(std::optional<sf::Vector2i> selectedBlock, Chunk &chunk, Player &plr, const BlockRegistry &registry, bool& buttonPressed)
{

    if (buttonPressed)
    {
        buttonPressed = false;
        if (selectedBlock.has_value())
        {
            sf::Vector2i pos = selectedBlock.value();
            if (chunk.getBlock(pos.y, pos.x) == BlockID::AIR && safeToPlaceBlock(pos,plr.getPos()))
            {
                chunk.setBlock(pos.y, pos.x, currentBlock);
                nudgePlayer(pos,plr);
            }
        }
    }
}

std::optional<sf::Vector2i> input_getSelectedBlock(sf::Vector2f mousePos, sf::Vector2f plrPos)
{
    sf::Vector2i chunkPos;

    chunkPos.x = mousePos.x / Engine_Constants::getTileSize();
    chunkPos.y = mousePos.y / Engine_Constants::getTileSize();

    int x_Radius = std::abs(chunkPos.x - (int)std::floor(plrPos.x / Engine_Constants::getTileSize()));

    int y_Radius = chunkPos.y - (int)std::floor(plrPos.y / Engine_Constants::getTileSize());

    bool ex1 = x_Radius <= 1 && y_Radius >= -2 && y_Radius <= 1; // checks whether the blocks around are within 1 block radius of the player

    bool ex2 = x_Radius == 0 && (y_Radius == 0 || y_Radius == -1); // checks whether the blocks are inside the player's hitboxes

    if (ex1 && !ex2)
    {
        return chunkPos;
    }

    return std::nullopt;
}

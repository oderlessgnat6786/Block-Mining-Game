#include <SFML/Graphics.hpp>
#include "world/chunk.h"
#include "renderBlock.h"
#include "world/chunk.h"
#include "blocks/BlockRegistry.h"
#include "renderBlock.h"

BlockRegistry Registry;

void renderChunk(Chunk &chunk, sf::Texture &tileset, sf::RenderWindow &window)
{
    sf::Sprite blockSprite(tileset);
    for (int i = 0; i < chunk.getChunkHeight(); i++)
    {
        for (int j = 0; i < chunk.getChunkWidth(); j++)
        {
            BlockID id = chunk.getBlock(i,j);
            const Block& block = Registry.getBlockDefinition(id);
            sf::Vector2i pos = {j,i};
            renderBlock(block, window, blockSprite, pos);
        }
    }
}
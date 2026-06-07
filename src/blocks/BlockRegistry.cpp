#include "block.h"
#include "types/BlockID.h"
#include "BlockRegistry.h"
#include "types/BlockType.h"
#include "types/ItemID.h"
#include <map>

BlockRegistry::BlockRegistry()
{
    Registry.emplace(BlockID::AIR, Block(BlockID::AIR, -1, -1, 0.f, BlockType::GAS, ItemID::NONE));
    //Registry.emplace(BlockID::BARRIER, Block(BlockID::BARRIER, 4, 0, 0.f, BlockType::ABSTRACT, ItemID::NONE));
    Registry.emplace(BlockID::BARRIER, Block(BlockID::BARRIER, 4, 0, 0.f, BlockType::ABSTRACT, ItemID::NONE));
    Registry.emplace(BlockID::DIRT, Block(BlockID::DIRT, 1, 0, 50.f, BlockType::ORGANIC, ItemID::NONE));
    Registry.emplace(BlockID::GRASS, Block(BlockID::GRASS, 0, 0, 50.f, BlockType::ORGANIC, ItemID::NONE));
    Registry.emplace(BlockID::NONE, Block(BlockID::NONE, -1, -1, 0.f, BlockType::ABSTRACT, ItemID::NONE));
    Registry.emplace(BlockID::ORE, Block(BlockID::ORE, 3, 0, 100.f, BlockType::ORE, ItemID::BRONZE));
    Registry.emplace(BlockID::STONE, Block(BlockID::STONE, 2, 0, 70.f, BlockType::SOLID, ItemID::STONE));
}

const Block& BlockRegistry::getBlockDefinition(BlockID id) const
{
    return Registry.at(id);
}
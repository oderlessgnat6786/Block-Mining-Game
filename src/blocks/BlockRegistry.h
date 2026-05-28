#include "block.h"
#include "types/BlockID.h"
#include <map>
#pragma once

class BlockRegistry
{
private:
    std::map<BlockID, Block> Registry;
public:
    BlockRegistry();
    const Block& getBlockDefinition(BlockID id) const;
};
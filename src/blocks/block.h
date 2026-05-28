#include "types/BlockID.h"
#include "SFML/Graphics.hpp"
#include "types/ItemID.h"
#include "types/BlockType.h"
#pragma once


class Block{
    private:
        BlockID name;
        sf::Vector2i tileCoords;
      //  struct{
     //       int x,int y;
      //  } position;
        float durability;
        BlockType type; //like misc, blocks
        ItemID item;
    public:
        void setTileCoords(int X, int Y);

        sf::Vector2i getTileCoords() const;

        Block(BlockID name, int X, int Y, float durability, BlockType type,ItemID item);
        
};

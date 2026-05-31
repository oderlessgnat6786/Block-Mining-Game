#include <iostream>
#include <vector>

#include "core/random_engine.h"
#include "types/BlockID.h"
#include "chunk.h"
#include "terrain_gen.h"
#include "cave_gen.h"

using namespace std;

void Chunk::setBlock(int y, int x, BlockID block)
{
	if (isValidBlockPosition(y, x))
		blocks.at(y).at(x) = block;
}

void Chunk::fillChunk(BlockID block)
{
	for (int i = 0; i < chunkHeight; i++)
	{
		for (int j = 0; j < chunkWidth; j++)
		{
			setBlock(i, j, block);
		}
	}
}

BlockID Chunk::getBlock(int y, int x)
{
	if (isValidBlockPosition(y, x))
		return blocks.at(y).at(x);
	return BlockID::NONE;
}

vector<int> &Chunk::getSurfaces()
{
	return surfaces;
}

int Chunk::getChunkWidth()
{
	return chunkWidth;
}

int Chunk::getChunkHeight()
{
	return chunkHeight;
}

vector<int> Chunk::getSurfaceDepths()
{
	vector<int> depth = {surface_depth.min, surface_depth.max};
	return depth;
}

vector<int> Chunk::getChunkOffsets()
{
	vector<int> offsets = {chunkOffset.X, chunkOffset.Y};
	return offsets;
}

vector<int> Chunk::getDirtDepths()
{
	vector<int> depth = {dirt_depth.min, dirt_depth.max};
	return depth;
}

void Chunk::setSurfaces(vector<int> &res)
{
	surfaces = res;
}

void Chunk::print()
{
	for (int i = 0; i < chunkHeight; i++)
	{
		for (int j = 0; j < chunkWidth; j++)
		{
			switch (blocks.at(i).at(j))
			{
			case BlockID::GRASS:
			{
				cout << "󰰡 ";
				break;
			}
			case BlockID::STONE:
			{
				cout << " ";
				break;
			}
			case BlockID::ORE:
			{
				// cout << ch == '#'?"󰇈 ":" ");
				cout << "󰇈 ";
				break;
			}
			case BlockID::DIRT:
			{
				cout << "󰝤 ";
				break;
			}
			case BlockID::AIR:
			{
				// cout << "  ";
				cout << "  ";
				break;
			}
			case BlockID::BARRIER:
			{
				cout << "󰯮 ";
				break;
			}
			default:
			{
				cout << "? ";
			}
			}
		}
		cout << endl;
	}
	cout << spawnP.X << "   pos   " << spawnP.Y << endl;
}

bool Chunk::isValidBlockPosition(int y, int x)
{
	if (y >= 0 && y < chunkHeight && x >= 0 && x < chunkWidth)
	{
		return true;
	}
	return false;
}

void Chunk::generate()
{
	// blocks.at(0).size()
	generateSurfaceMap(*this);

	generateTerrain(*this);

	generateCaves(*this);

	generateSpawn();
}

void Chunk::generateSpawn()
{
	// Find random columm
	// vector<int> col = surfaces;
	vector<int> eligibleSurfaces;
	int i = 0;
	while (i < surfaces.size())
	{
		int y = surfaces.at(i);
		int x = i;
		if (getBlock(y - 1, x) == BlockID::AIR && getBlock(y - 2, x) == BlockID::AIR) // minimum height of 2 air blocks
		{
			eligibleSurfaces.push_back(x);
		}
		i++;

	} // 5 4 1 2 4   {0,2,4}

	if (!eligibleSurfaces.empty())
	{
		int rC = randINT(0, eligibleSurfaces.size() - 1);
		spawnP.X = eligibleSurfaces.at(rC);
		spawnP.Y = surfaces.at(eligibleSurfaces.at(rC))-1;
	}else{
		int rC = randINT(0, surfaces.size() - 1);
		spawnP.X = rC;
		spawnP.Y = surfaces.at(rC);
	}
}

Chunk::Chunk(int height, int width, int min_surface_depth, int max_surface_depth, int min_dirt_depth, int max_dirt_depth, int chunkOffsetX, int chunkOffsetY)
{
	chunkHeight = height;
	chunkWidth = width;

	chunkOffset.X = chunkOffsetX;
	chunkOffset.Y = chunkOffsetY;

	surfaces.resize(chunkWidth);
	blocks.resize(chunkHeight, vector<BlockID>(chunkWidth));

	dirt_depth.min = min_dirt_depth;
	dirt_depth.max = max_dirt_depth;

	surface_depth.min = min_surface_depth;
	surface_depth.max = max_surface_depth;

	generate();
}

vector<int> Chunk::getSpawnPos()
{
	vector<int> pos = {spawnP.X, spawnP.Y};
	return pos;
}

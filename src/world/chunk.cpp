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
		Chunk::blocks.at(y).at(x) = block;
}



void Chunk::fillChunk(BlockID block)
{
	for (int i = 0; i < Chunk::chunkHeight; i++)
	{
		for (int j = 0; j < Chunk::chunkWidth; j++)
		{
			Chunk::setBlock(i, j, block);
		}
	}
}


BlockID Chunk::getBlock(int y, int x)
{
	if (Chunk::isValidBlockPosition(y, x))
		return Chunk::blocks.at(y).at(x);
	return BlockID::NONE;
}

vector<int>& Chunk::getSurfaces()
{
	return surfaces;
}

int Chunk::getChunkWidth()
{
	return Chunk::chunkWidth;
}

int Chunk::getChunkHeight()
{
	return Chunk::chunkHeight;
}

vector<int> Chunk::getSurfaceDepths()
{
	vector<int> depth = {Chunk::surface_depth.min, Chunk::surface_depth.max};
	return depth;
}

vector<int> Chunk::getChunkOffsets()
{
	vector<int> offsets = {Chunk::chunkOffset.X,Chunk::chunkOffset.Y};
	return offsets;
}

vector<int> Chunk::getDirtDepths()
{
	vector<int> depth = {Chunk::dirt_depth.min, Chunk::dirt_depth.max};
	return depth;
}

void Chunk::setSurfaces(vector<int> &res)
{
	Chunk::surfaces = res;
}

void Chunk::print()
{
	for (int i = 0; i < Chunk::chunkHeight; i++)
	{
		for (int j = 0; j < Chunk::chunkWidth; j++)
		{
			switch (Chunk::blocks.at(i).at(j))
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
				//cout << "  ";
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
	cout << Chunk::spawnP.X << "   pos   " << Chunk::spawnP.Y << endl;
}

bool Chunk::isValidBlockPosition(int y, int x)
{
	if (y >= 0 && y < Chunk::chunkHeight && x >= 0 && x < Chunk::chunkWidth)
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
	int rC = randINT(0, Chunk::chunkWidth - 1);
	Chunk::spawnP.X = rC;
	Chunk::spawnP.Y = Chunk::surfaces.at(rC);
}

Chunk::Chunk(int height, int width, int min_surface_depth, int max_surface_depth, int min_dirt_depth, int max_dirt_depth, int chunkOffsetX, int chunkOffsetY)
{
	Chunk::chunkHeight = height;
	Chunk::chunkWidth = width;

	Chunk::chunkOffset.X = chunkOffsetX;
	Chunk::chunkOffset.Y = chunkOffsetY;

	Chunk::surfaces.resize(Chunk::chunkWidth);
	Chunk::blocks.resize(Chunk::chunkHeight, vector<BlockID>(Chunk::chunkWidth));

	Chunk::dirt_depth.min = min_dirt_depth;
	Chunk::dirt_depth.max = max_dirt_depth;

	Chunk::surface_depth.min = min_surface_depth;
	Chunk::surface_depth.max = max_surface_depth;

	Chunk::generate();
}

vector<int> Chunk::getSpawnPos()
{
	vector<int> pos = {spawnP.X,spawnP.Y};
	return pos;
}

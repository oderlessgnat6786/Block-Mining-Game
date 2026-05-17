#include <iostream>
#include <vector>
#include "core/random_engine.h"
#include "world/BlockID.h"
using namespace std;

class Chunk
{
private:
	vector<vector<BlockID>> blocks;
	vector<int> surfaces;

	int chunkHeight, chunkWidth;

	struct
	{
		int X, Y;
	} spawnP;

	struct
	{
		int min, max;
	} surface_depth;

	int chunkWorldX, chunkWorldY;

	struct
	{
		int min, max;
	} dirt_depth;

	bool isValidBlockPosition(int y, int x)
	{
		if (y >= 0 && y < chunkHeight && x >= 0 && x < chunkWidth)
		{
			if (blocks.at(y).at(x) != BlockID::AIR)
				return true;
		}
		return false;
	}

	void setBlock(int y, int x, BlockID block)
	{
		if (isValidBlockPosition(y, x))
			blocks.at(y).at(x) = block;
	}

	BlockID getBlock(int y, int x)
	{
		if (isValidBlockPosition(y, x))
			return blocks.at(y).at(x);
	}

	void fillChunk(BlockID block)
	{
		for (int i = 0; i < chunkHeight; i++)
		{
			for (int j = 0; j < chunkWidth; j++)
			{
				setBlock(i, j, block);
			}
		}
	}

	void generateSurfaceMap()
	{

		for (int i = 0; i < surfaces.size(); i++)
		{
			surfaces.at(i) = chunkHeight - randINT(surface_depth.min, surface_depth.max);
		}
	}

	void generateTerrain()
	{
		fillChunk(BlockID::AIR);
		for (int j = 0; j < chunkWidth; j++)
		{
			int surface = surfaces.at(j);
			int dirt_depth = surface + randINT(this->dirt_depth.min, this->dirt_depth.max);
			// int stone_depth = dirt_depth+1;
			//     0 1
			//  -- 1 2 ))
			//  ## 2 3
			//  ## 3 4 ??
			//  .# 4 5 ??
			//  .. 5 6
			//  .. 6 7 ??
			for (int i = chunkHeight - 1; i >= 0; i--)
			{
				if (i == surface)
					setBlock(i, j, BlockID::GRASS);
				else if (i <= dirt_depth && i > surface)
					setBlock(i, j, BlockID::DIRT);
				else if (i > dirt_depth)
					setBlock(i, j, BlockID::STONE);
			}
		}
	}

	void generate()
	{
		// blocks.at(0).size()
		generateSurfaceMap();

		generateTerrain();

		generateSpawn();
	}

	void generateSpawn()
	{
		// Find random columm
		int rC = randINT(0, chunkWidth - 1);
		spawnP.X = rC;
		spawnP.Y = surfaces.at(rC);
	}

public:
	Chunk(int height, int width, int min_surface_depth, int max_surface_depth, int min_dirt_depth, int max_dirt_depth)
	{
		chunkHeight = height;
		chunkWidth = width;

		surfaces.resize(chunkWidth);
		blocks.resize(chunkHeight, vector<BlockID>(chunkWidth));

		this->dirt_depth.min = min_dirt_depth;
		this->dirt_depth.max = max_dirt_depth;

		this->surface_depth.min = min_surface_depth;
		this->surface_depth.max = max_surface_depth;

		generate();
	}
	void print()
	{
		for (int i = 0; i < blocks.size(); i++)
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
					cout << "  ";
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
};

int main()
{
	Chunk chong = Chunk(10, 10, 45, 62, 2, 7);
	chong.print();
	return 0;
}
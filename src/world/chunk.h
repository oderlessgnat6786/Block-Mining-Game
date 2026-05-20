#include <vector>
#include "BlockID.h"
//#include "chunk.cpp"
#pragma once
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

	bool isValidBlockPosition(int y, int x);

	void generate();

	void generateSpawn();

public:
	Chunk(int height, int width, int min_surface_depth, int max_surface_depth, int min_dirt_depth, int max_dirt_depth);
	
	void setBlock(int y, int x, BlockID block);

	BlockID getBlock(int y, int x);

	vector<int>& getSurfaces();

	void setSurfaces(vector<int>& res);

	int getChunkWidth();

	int getChunkHeight();

	vector<int> getSurfaceDepths();

	void fillChunk(BlockID block);

	void print();
};
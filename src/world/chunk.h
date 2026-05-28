#include <vector>
#include "types/BlockID.h"
//#include "chunk.cpp"
#pragma once
using namespace std;

class Chunk
{
private:
	vector<vector<BlockID>> blocks;
	vector<int> surfaces;

	struct{
		int X, Y;
	}chunkOffset;

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
	Chunk(int height, int width, int min_surface_depth, int max_surface_depth, int min_dirt_depth, int max_dirt_depth, int chunkOffsetX, int chunkOffsetY);
	
	void setBlock(int y, int x, BlockID block);

	BlockID getBlock(int y, int x);

	vector<int>& getSurfaces();

	void setSurfaces(vector<int>& res);

	int getChunkWidth();

	int getChunkHeight();

	vector<int> getSurfaceDepths();

	vector<int> getDirtDepths();

	vector<int> getChunkOffsets();

	void fillChunk(BlockID block);

	void print();
};
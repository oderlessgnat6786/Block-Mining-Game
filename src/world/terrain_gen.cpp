#include "terrain_gen.h"
#include "core/perlin_noise.h"
#include <vector>
#include "chunk.h"
#include "types/BlockID.h"
#include "core/random_engine.h"
using namespace std;

const static int sampler = 4;
const static float scale = 0.5;    // 0.5
const static float multiplier = 50; // 50

float sample(float x, float y, int width, int height, int n)
{

    float freq = 1;
    float amp = 1.25;
    float val = 0;

    for (int i = 0; i < n; i++)
    {
        val += perlin(x * freq/width , y * freq/height) * amp;

        freq *= 2;
        amp /= 2;
    }

    val *= multiplier;

    return val;
}

float sample(float x, float y, int width, int height, int n, int multiply)
{

    float freq = 1;
    float amp = 1.25;
    float val = 0;

    for (int i = 0; i < n; i++)
    {
        val += perlin(x * freq/width , y * freq/height) * amp;

        freq *= 2;
        amp /= 2;
    }

    val *= multiply;

    return val;
}

void generateSurfaceMap(Chunk &chunk)
{
    vector<int> surfaceDepth = chunk.getSurfaceDepths();
    vector<int> vec = chunk.getSurfaces();
    vector<int> offsets = chunk.getChunkOffsets();
    for (int i = 0; i < vec.size(); i++)
    {
        float intensity = sample((i + offsets.at(0))*scale, 0, chunk.getChunkWidth(), chunk.getChunkHeight(), sampler);

        int surface_depth = surfaceDepth.at(0) + intensity;

        if (surface_depth > surfaceDepth.at(1))
             surface_depth = surfaceDepth.at(1);
         else if (surface_depth < surfaceDepth.at(0))
             surface_depth = surfaceDepth.at(0);
        vec.at(i) = chunk.getChunkHeight() - surface_depth;
    }
    chunk.setSurfaces(vec);
}

int getDirtDepth(int y, int surfaceIndex, int width, int height, int min, int max)
{
    int depth;

    int old_min = -50, old_max = 50;

    float intensity = sample(0, ((float)y+500.0f) * scale, width, height, sampler,5);

    float map = min + (((intensity - old_min) * (max - min)) / (old_max - old_min));

    depth = surfaceIndex + (int)map;

    return depth;
}

void generateTerrain(Chunk &chunk)
{
    chunk.fillChunk(BlockID::AIR);

    vector<int> offsets = chunk.getChunkOffsets();

    vector<int> surfaces = chunk.getSurfaces();

    vector<int> dirtDepths = chunk.getDirtDepths();

    for (int j = 0; j < chunk.getChunkWidth(); j++)
    {
        int surface = surfaces.at(j);

        int dirtDepth = getDirtDepth(j + offsets.at(0), surface, chunk.getChunkWidth(), chunk.getChunkHeight(), dirtDepths.at(0), dirtDepths.at(1));

        for (int i = chunk.getChunkHeight() - 1; i >= 0; i--)
        {
            if (i == 0 || j == chunk.getChunkWidth()-1 || i == chunk.getChunkHeight() - 1 || j == 0)
                chunk.setBlock(i,j,BlockID::BARRIER);
            else if (i == surface)
                chunk.setBlock(i, j, BlockID::GRASS);
            else if (i < surface)
                chunk.setBlock(i, j, BlockID::AIR);
            else if (i > surface && i <= dirtDepth)
                chunk.setBlock(i, j, BlockID::DIRT);
            else
                chunk.setBlock(i, j, BlockID::STONE);
        }
    }
}
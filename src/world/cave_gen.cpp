#include "cave_gen.h"
#include "core/perlin_noise.h"
#include <vector>
#include "chunk.h"
#include <iostream>
#include "types/BlockID.h"

#include "core/constants.h"

const static int sampler = 4;
const static float scale = 0.08;
const static float multiplier = 50;

float sampleNoise(float x, float y, int width, int height, int n)
{

    float freq = 0.8;
    float amp = 1.1;
    float val = 0;

    for (int i = 0; i < n; i++)
    {
        val += perlin(x * freq, y * freq) * amp;
        freq *= 2;
        amp /= 2;
    }

    val *= multiplier;

    return val;
}

bool fillAIR(int y, int x, int safeDepth, int width, int height)
{
    float intensity = sampleNoise(x * scale, y * scale, width, height, sampler);

    struct
    {
        int min, max;
    } threshold;

    threshold.min = -15;
    threshold.max = 15;

    int limit = -6;

    if (y >= safeDepth && intensity < limit) return true;

    return false;
}

void generateCaves(Chunk &chunk)
{
    vector<int> chunkOffsets = chunk.getChunkOffsets();
    for (int i = 0; i < chunk.getChunkHeight(); i++)
    {
        for (int j = 0; j < chunk.getChunkWidth(); j++)
        {
            int safeDepth = chunk.getSurfaces().at(j)+chunk.getDirtDepths().at(0)+8;
            BlockID block = chunk.getBlock(i, j);

            if ((block == BlockID::DIRT && chunk.getBlock(i-1,j) != BlockID::GRASS) || block == BlockID::STONE)
            {
                if (fillAIR(i+chunkOffsets.at(1), j + chunkOffsets.at(0), safeDepth, chunk.getChunkWidth(), chunk.getChunkHeight()))
                    chunk.setBlock(i, j, BlockID::AIR);
            }
        }
    }
}

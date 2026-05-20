#include "terrain_gen.h"
#include "core/perlin_noise.h"
#include <vector>
#include "chunk.h"
#include <iostream>

using namespace std;

float sample(float x, float y, int width, int height, int n)
{
    float freq = 1;
    float amp = 1;
    float val = 0;

    float multiplier = 50;

    for (int i = 0; i < n; i++)
    {
        val += perlin(x * freq/width, y * freq/height) * amp;
        freq *= 2;
        amp /= 2;
    }

    val *= multiplier;

    return val;
}

void generateSurfaceMap(Chunk &chunk)
{
    vector<int> surfaceDepth = chunk.getSurfaceDepths();
    vector<int> vec = chunk.getSurfaces();


    for (int i = 0; i < vec.size(); i++)
    {
        float intensity = sample(i*0.1, 0, chunk.getChunkWidth(), chunk.getChunkHeight(), 4);
        
        int surface_depth = surfaceDepth.at(0) + intensity;
        
        cout << intensity << " >> " << surface_depth << "  " << chunk.getChunkHeight() - surface_depth << endl; 

        if (surface_depth > surfaceDepth.at(1)) surface_depth = surfaceDepth.at(1);
        else if (surface_depth < surfaceDepth.at(0)) surface_depth = surfaceDepth.at(0);
        vec.at(i) = chunk.getChunkHeight() - surface_depth;
    }
    chunk.setSurfaces(vec);
}

void generateTerrain(Chunk &chunk)
{
    chunk.fillChunk(BlockID::AIR);
    for (int j = 0; j < chunk.getChunkWidth(); j++)
    {
        int surface = chunk.getSurfaces().at(j);
        for (int i = chunk.getChunkHeight() - 1; i >= 0; i--)
        {
            
        }
    }
}
#include "perlin_noise.h"
#include <math.h>

//tutorial: https://www.youtube.com/watch?v=kCIaHqb60Cw (channel name: ZIPPED)

typedef struct{
    float x, y;
}vector2d;

vector2d randomGradient(int Gx, int Gy){
    //function provided by https://pastebin.com/XwCPn0xR
    
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; 
    unsigned a = Gx, b = Gy;
    a *= 3284157443;
 
    b ^= a << s | a >> w - s;
    b *= 1911520717;
 
    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
    // Create the vector from the angle
    vector2d v;
    v.x = sin(random);
    v.y = cos(random);
 
    return v;
}

float dotproduct(int Gx, int Gy, float x, float y){
    vector2d gradient = randomGradient(Gx,Gy);

    float dx = x - (float)Gx;
    float dy = y - (float)Gy;
    
    return (dx*gradient.x+dy*gradient.y);
}

float interpolate(float n1, float n2, float wt){
    return (n2-n1) * (3.0 - wt * 2.0) * wt * wt + n1;
}

float perlin(float x, float y){
    
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0+1;
    int y1 = y0+1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n1 = dotproduct(x0,y0,x,y); //rect n1n2n3n4
    float n2 = dotproduct(x1,y0,x,y);
    float n3 = dotproduct(x0,y1,x,y);
    float n4 = dotproduct(x1,y1,x,y);

    float lerp1 = interpolate(n1,n2,sx);
    float lerp2 = interpolate(n3,n4,sx);

    return interpolate(lerp1,lerp2,sy);

}
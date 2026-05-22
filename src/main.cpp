#include <iostream>
#include <world/chunk.h>
#include <world/cave_gen.h>
int main(){
//	int height,width,minS,maxS,minD,maxD,offX,offY;
	int ar[8];
	for (int i = 0;i<8;i++) cin >> ar[i];
	//cout << "Height || Width || SURFACE DEPTHS (MIN || MAX) || DIRT DEPTHS (MIN || MAX) || CHUNK OFFSETS (X || Y)";
	//Chunk ob = Chunk(32,100,5,28,2,6);
	Chunk ob = Chunk(ar[0],ar[1],ar[2],ar[3],ar[4],ar[5],ar[6],ar[7]);
	ob.print();
	return 0;
}
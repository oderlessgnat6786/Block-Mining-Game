#include <iostream>
#include <vector>
#include "core/random_engine.h"
using namespace std;
// BOANNT
// BLOCK IDS: 0 - AIR
// 1 - GRASS
// 2 - STONE
// 3 - ORE(5,7)
class chunk
{
private:
	vector<vector<int>> area;
	struct
	{
		int X, Y;
	} spawnP;
	vector<int> entities /* */;
	void gen()
	{
		int surfaces[area.at(0).size()];
		for (int j = 0; j < area.at(0).size(); j++)
		{
			int surface = area.size() - randINT(2,5);
			surfaces[j] = surface;
			for (int i = area.size() - 1; i >= 0; i--)
			{
				if (i < surface)
					area.at(i).at(j) = 0;
				else if (i == surface)
					area.at(i).at(j) = 1;
				else
					area.at(i).at(j) = 2;
			}
		}
		set_spawn(surfaces, sizeof(surfaces) / sizeof(surfaces[0]));
	}

	void set_spawn(int surfaces[], int len)
	{
		spawnP.Y = surfaces[randINT(0, len - 1)];
		spawnP.X = randINT(0, area.at(0).size() - 1);
	}

public:
	chunk(int chunkX, int chunkY)
	{
		area.resize(chunkX, vector<int>(chunkY));
		gen();
	}
	void print()
	{
		for (int i = 0; i < area.size(); i++)
		{
			for (int j = 0; j < area.at(0).size(); j++)
			{
				cout << area.at(i).at(j);
			}
			cout << endl;
		}
		cout << spawnP.X << "   pos   " << spawnP.Y << endl;
	}
};

int main()
{
	chunk chong = chunk(5, 7);
	chong.print();
	return 0;
}
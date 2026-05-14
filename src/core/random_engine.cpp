#include <random>
#include <iostream>
#include "random_engine.h"
using namespace std;
int randINT(int min, int max){
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution<> dist(min,max);
	return dist(mt);
}



#pragma once
#include <iostream>
#include <list>
#include <stdlib.h>
//#include "object.h"
class objectU;
struct item
{
	objectU* array;
	int type;
};
struct position
{
	int x;
	int y;
	int z;
};
class world
{
public:
	world(int x, int y, int z);
	bool sign(position tar, item set);
	item getSpaceArr(position tar);
private:
	int limitX;
	int limitY;
	int limitZ;
	std::list<objectU*> objBin;
	item* objSpaceArr;
};
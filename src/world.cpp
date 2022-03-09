#include "world.h"
world::world(int x, int y, int z) :limitX(x), limitY(y), limitZ(z)
{
	int limit = x * y * z;
	objSpaceArr = (item*)malloc(limit * sizeof(item));
	if (objSpaceArr)
		for (int i = 0; i < limit; i++)
			*(objSpaceArr + i) = { NULL,0 };
}
bool world::sign(position tar, item set)
{
	if ((tar.x < 0) || (tar.y < 0) || (tar.z < 0) || (tar.x > limitX) || (tar.y > limitY) || (tar.z > limitZ))
		return false;
	int tarid = tar.x + tar.y * limitX + tar.z * limitX * limitY;
	objSpaceArr[tarid] = set;
	return true;
}
item world::getSpaceArr(position tar)
{
	if ((tar.x < 0) || (tar.y < 0) || (tar.z < 0) || (tar.x > limitX) || (tar.y > limitY) || (tar.z > limitZ))
		return { NULL,NULL };
	int tarid = tar.x + tar.y * limitX + tar.z * limitX * limitY;
	return objSpaceArr[tarid];
}
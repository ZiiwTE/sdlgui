#include "objectWire.h"
bool wire::setPosition(position nP)
{
	if (setStatus = 0)
	{
		start = nP;
		setStatus = 1;
	}
	else if (setStatus >= 1)
	{
		if ((nP.x == start.x) || (nP.y == start.y) || (nP.z == start.z))
		{
			end = nP;
			setStatus = 2;
		}
		else
			return false;
	}
	return true;
}
bool wire::clearSet()
{
	setStatus = 0;
	return true;
}
bool wire::addObject(world* target)
{
	if (setStatus != 2)
		return false;
	double finalLen = aSize + bSize;
	int size = (int)ceil(finalLen * 2);//总尺寸
	int directionType = 0;//方向类型:1X,2Y,3Z
	if ((start.y == end.y) && (start.z == end.z))
		directionType = 1;
	if ((start.x == end.x) && (start.z == end.z))
		directionType = 2;
	if ((start.x == end.x) && (start.y == end.y))
		directionType = 3;
	if (directionType == 0)
		return false;
	int length;
	int pao, pbo;//层起始坐标
	switch (directionType)
	{
	case 1:
		length = end.x - start.x;
		pao = start.y - finalLen / 2;
		pbo = start.z - finalLen / 2;
	case 2:
		length = end.y - start.y;
		pao = start.x - finalLen / 2;
		pbo = start.z - finalLen / 2;
	case 3:
		length = end.z - start.z;
		pao = start.x - finalLen / 2;
		pbo = start.y - finalLen / 2;
	}
	for (int i = 0; i <= length; i++)//指针区域写入,层叠计层
	{
		for(int pa=0;pa< finalLen;pa++)
			for (int pb = 0; pb < finalLen; pb++)
			{
				switch (directionType)
				{
				case 1:
					;
				case 2:
					;
				case 3:
					;
				}
			}
	}
	return true;
}
#pragma once
#include "objectId.h"
#include "world.h"
class world;
class objectU
{
public:
	virtual bool setPosition(position nP) = 0;
	virtual bool clearSet() = 0;
	virtual bool addObject(world* target) = 0;
private:
	int id;
};
#pragma once
#include "object.h"
class wire : public objectU
{
public:
	bool setPosition(position nP);
	bool clearSet();
	bool addObject(world* target);
private:
	int setStatus = 0;
	position start;
	position end;

	int materialId;
	double aSize;
	int oMaterialId;
	double bSize;
};
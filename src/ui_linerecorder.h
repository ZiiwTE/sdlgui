#pragma once
#include <cstddef>
#include <stdlib.h>
#include <thread>
#include <functional>
#include "ui_universal.h"
#include "color_def.h"
#include "font_def.h"

#define RECORD_LIMIT 8

#define RECORD_INT 37
#define RECORD_FLOAT 24
#define RECORD_DOUBLE 75

class value_record
{
public:
	value_record();
	value_record(int limit);
	bool addResize(int nLimit);
	bool addRecord(double value);
	int getRecord(double* store,int limit);
	double getMax(int limit);
	double getMin(int limit);
private:
	int resize = 0;
	int lengthLimit;
	int length = 0;
	int start = 0;
	double* records = NULL;
};
class ui_item_linerecorder : public ui_item_u
{
public:
	friend class engine;
	ui_item_linerecorder();
	~ui_item_linerecorder();
	bool setSize(int width, int height);

	bool addRecordVar(int* var);
	bool addRecordVar(float* var);
	bool addRecordVar(double* var);

	bool setClock(int time);

	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	bool loop();
	bool start();
	bool end();
private:
	int recordNum = 0;
	value_record record[RECORD_LIMIT];
	void* recordArray[RECORD_LIMIT];
	int recordtype[RECORD_LIMIT];
	int recordColor[RECORD_LIMIT];
	bool recordVisible[RECORD_LIMIT];

	int clock = 100;

	bool recordRecord();

	int size_x;
	int size_y;

	bool running = false;
	std::thread t;

	int focus;//选中情况
};
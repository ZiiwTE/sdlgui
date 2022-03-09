#pragma once
#include <thread>
#include <functional>
#include "graphic.h"
#include "ui_universal.h"
class engine : public ui_item_u
{
public:
	engine(int w, int h);
	bool addItem(ui_item_u* item);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool textInput(char* text);
	//bool keyDown(int type);
	bool fresh();
	bool loop();
	bool setClock(int time);
private:
	int width;
	int height;
	int nitems;

	int clock = 10;
	bool running = false;
	std::thread t;

	ui_item_u** items;
};
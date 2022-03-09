#pragma once
#include <cstddef>
#include <thread>
#include <functional>
#include "ui_universal.h"
#include "color_def.h"
#include "font_def.h"

#define TOP 16
#define SWITCH 48

#define RESIZE_LIMIT 4

#define RESIZE_FALSE 0
#define RESIZE_LOW 1
#define RESIZE_HIGH 2

class ui_item_window : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	ui_item_window();
	bool setSize(int width, int height);

	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool setPlayer(ui_item_u* source);

	bool setClock(int time);

	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	bool loop();
	bool start();
	bool end();
private:
	int size_x;
	int size_y;
	int pressed;

	ui_item_u* inside = NULL;

	int clock = 100;
	bool running;
	std::thread t;

	bool cPressed = false;
	bool cAbove = false;

	bool move = false;
	int resizeX = RESIZE_FALSE;
	int resizeY = RESIZE_FALSE;

	int oX = 0;
	int oY = 0;

	int fontSize;
	wchar_t text[0xffff];
};
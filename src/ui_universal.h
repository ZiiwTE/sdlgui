#pragma once
#include <cstddef>
#include <stdlib.h>
#include <thread>
#include "graphic.h"

class ui_item_u
{
public:
	friend class engine;
	ui_item_u(int tp);
	bool setVisible(bool nset);
	bool getVisible();
	int getType();
	bool setPosition(int nx, int ny);
	int getX();
	int getY();
	virtual bool mouseMove(int ix, int iy) = 0;
	virtual bool click(int ix, int iy) = 0;
	virtual bool unclick(int ix, int iy) = 0;
	virtual bool textInput(char* text);
	virtual bool keyDown(int type);
	virtual bool fresh() = 0;

	pixel image[P_MAX];

protected:
	int type;
	bool visible;
	int x;
	int y;
};
class ui_item_u_text
{
public:
	friend class engine;
	friend class ui_item_u;
	ui_item_u_text();
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
protected:
	wchar_t text[255];
};
#pragma once
#include <cstddef>
#include <stdlib.h>
#include "ui_universal.h"
#include "color_def.h"
#include "font_def.h"
class ui_item_label : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	ui_item_label();
	bool setSize(int width, int height);
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
private:
	int size_x;
	int size_y;
	int fontSize;
};
class ui_item_button : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	ui_item_button();
	bool setSize(int width, int height);
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	bool setEvent(void(*funPtr)());
private:
	int size_x;
	int size_y;
	int fontSize;
	bool pressed;
	bool above;
	void (*eventa)();
};
class ui_item_checkBox :public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	ui_item_checkBox();
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	//特定状态查询
	bool getStatus();
private:
	int size_x;
	int size_y;
	int fontSize;
	bool pressed;
	bool above;
	bool status;
};
class ui_item_switch : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	ui_item_switch();
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	//特定状态查询
	bool getStatus();
private:
	int size_x;
	int size_y;
	int fontSize;
	bool pressed;
	bool above;
	bool status;
};
class ui_item_topmenusubitem : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	friend class ui_item_topmenuitem;
	ui_item_topmenusubitem();
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
private:
};
class ui_item_topmenuitem : public ui_item_u, public ui_item_u_text
{
public:
	friend class engine;
	friend class ui_item_top;
	ui_item_topmenuitem();
	bool setSize(int width, int height);
	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	bool addItem(ui_item_topmenusubitem* item);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
	bool signSuper(bool* arr);
	bool delSuper();
private:
	int size_x;
	int size_y;
	int nitems;
	ui_item_topmenusubitem** items;
	bool pressed;
	bool* motherPressArr;
};
class ui_item_top : public ui_item_u
{
public:
	friend class engine;
	ui_item_top();
	bool setSize(int height);
	bool addItem(ui_item_topmenuitem* item);
	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool fresh();
private:
	int size_x;
	int size_y;
	int size;
	int nitems;
	ui_item_topmenuitem** items;
	bool pressed;
};
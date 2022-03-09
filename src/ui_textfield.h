#pragma once
#include <cstddef>
#include <stdlib.h>
#include "ui_universal.h"
#include "color_def.h"
#include "font_def.h"
class ui_item_textfield : public ui_item_u
{
public:
	friend class engine;
	ui_item_textfield();
	bool setSize(int width, int height);

	bool setText(const char ntext[]);
	bool setText(const wchar_t ntext[]);
	wchar_t* getText();

	bool mouseMove(int ix, int iy);
	bool click(int ix, int iy);
	bool unclick(int ix, int iy);
	bool textInput(char* ntext);
	bool fresh();
private:
	int size_x;
	int size_y;
	int pressed;

	bool numFresh();//刷新每行计数
	bool offFresh();//重计算选针位置
	int focus;//选中情况
	int check1;//选区1:选区前字符数量
	int offL1;
	int offX1;
	int check2;//选区2
	int offL2;
	int offX2;

	int fontSize;
	wchar_t text[0xffff];
	int textLength[0xffff];//单字符长度
	int textNum[0xffff];//每行字符数量
};
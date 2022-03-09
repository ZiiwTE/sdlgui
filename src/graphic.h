#pragma once
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <algorithm>

#include <ft2build.h>

#include <atlimage.h>

#include <freetype/freetype.h>
#include <freetype/ftoutln.h>
#include <freetype/ftglyph.h>

#include "color_def.h"
#include "font_def.h"

#define P_MAX 8294400

#define PIXEL_DATA 0
#define PIXEL_ENDL 1
#define PIXEL_END 2

struct pixel
{
	int status;//0,正常 1,行结束 2,结束
	int color;
	int alpha;
};

struct position
{
	int x;
	int y;
};

class imgSpace
{
public:
	friend class imgSpace;
	imgSpace(int width, int height, int defaultC, int dafaultA);
	imgSpace(int width, int height, int defaultC);
	imgSpace();
	~imgSpace();
	int* getSpace();
	int getWidth();
	int getHeight();

	//线性表示
	bool toLiner(pixel target[]);
	bool copyFromLiner(int px, int py, pixel source[]);

	bool clear(int defaultC, int defaultA);
	bool resizeClear(int nwidth, int nheight, int defaultC, int defaultA);
	bool sign(int x, int y, int color);
	bool sign(int x, int y, int color, int alpha);
	bool signA(int pos, int color, int alpha);
	int getC(int x, int y);
	int getA(int x, int y);
	bool setA(int x, int y, int size_x, int size_y, int alpha);
	bool fill(int x, int y, int size_x, int size_y, int color, int alpha);
	bool draw_line(int x1, int y1, int x2, int y2, int color);
	bool draw_line_antialiasing(double x1, double y1, double x2, double y2, int color);
	bool draw_bezier(position* source, int num, int color);
	bool draw_rectangle(int x, int y, int size_x, int size_y, int color);
	bool draw_circle(int x, int y, int rx, int ry, int color);
	bool print(int x, int y, int fontSize, const char font[], wchar_t chr[], int color);
	bool print_mass(int xp, int yp, int fontSize, int length, const char font[], wchar_t chr[], int color);
	bool spaceCopy(int px, int py, imgSpace* source);
	int getPrintLength(int fontSize, const char font[], wchar_t chr[]);
	int getPrintLength(int fontSize, const char font[], wchar_t chr);
private:
	int width;
	int height;
	int* carr;
	int* alpha;
	bool draw_line_stright(int x1, int y1, int x2, int y2, int color);
};
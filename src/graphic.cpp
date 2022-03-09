//绘图器
#include "graphic.h"

imgSpace::imgSpace(int width, int height, int defaultC, int defaultA) :width(width), height(height), carr(NULL), alpha(NULL)
{
	int length = width * height;
	carr = (int*)malloc(length * sizeof(int));
	if (carr)
		for (int i = 0; i < length; i++)
			*(carr + i) = defaultC;
	alpha = (int*)malloc(length * sizeof(int));
	if (alpha)
		for (int i = 0; i < length; i++)
			*(alpha + i) = defaultA;
}
imgSpace::imgSpace(int width, int height, int defaultC)
{
	new (this)imgSpace(width, height, defaultC, 0xff);
}
imgSpace::imgSpace()
{
	new (this)imgSpace(0, 0, 0);
}
imgSpace::~imgSpace()
{
	if (carr)
		free(carr);
	if (alpha)
		free(alpha);
}
int* imgSpace::getSpace()
{
	return carr;
}
int imgSpace::getWidth()
{
	return width;
}
int imgSpace::getHeight()
{
	return height;
}

bool imgSpace::toLiner(pixel target[])
{
	target[(width + 1) * height].status = PIXEL_END;
	for (int i = 1; i < height; i++)
	{
		target[(width + 1) * i - 1].status = PIXEL_ENDL;
	}
	int limitLength = (width + 1) * height - 1;
	int i;
	int s = 0;
	for (i = 0; i < limitLength; i++)
	{
		for (int j = 0; j < width; j++)
		{
			target[i] = { PIXEL_DATA,carr[s] ,alpha[s] };
			i++;
			s++;
		}
	}
	return true;
}
bool imgSpace::copyFromLiner(int px, int py, pixel source[])
{
	int point = px + (py * width);
	int total = width * height;
	int limita = width - px;
	int ppx = 0;//当前行复制个数
	for (int i = 0; source[i].status != PIXEL_END; i++)
	{
		if (source[i].status == PIXEL_ENDL)
		{
			i++;
			point += width - ppx;
			ppx = 0;
		}
		if (source[i].status == PIXEL_END)
			break;
		if (point >= total)
			break;
		if ((point > 0) && (px + ppx >= 0))
		{
			carr[point] = source[i].color;
			alpha[point] = source[i].alpha;
		}
		point++;
		ppx++;
		if (ppx > limita)//复制至目标尽头
		{
			while ((source[i].status != PIXEL_ENDL) && (source[i].status != PIXEL_END))
				i++;
			point += px - 1;
			ppx = 0;
		}
	}
	return true;
}

bool imgSpace::clear(int defaultC, int defaultA)
{
	int length = width * height;
	if (carr)
		for (int i = 0; i < length; i++)
			*(carr + i) = defaultC;
	if (alpha)
		for (int i = 0; i < length; i++)
			*(alpha + i) = defaultA;
	return true;
}
bool imgSpace::resizeClear(int nwidth, int nheight, int defaultC, int defaultA)
{
	int length = nwidth * nheight;
	width = nwidth;
	height = nheight;
	if (carr)
		delete(carr);
	carr = (int*)malloc(length * sizeof(int));
	if (carr)
		for (int i = 0; i < length; i++)
			*(carr + i) = defaultC;
	if (alpha)
		delete(alpha);
	alpha = (int*)malloc(length * sizeof(int));
	if (alpha)
		for (int i = 0; i < length; i++)
			*(alpha + i) = defaultA;
	return true;
}
//图像绘制
bool imgSpace::sign(int x, int y, int color)
{
	if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
	{
		*(carr + (width * y) + x) = color;
		return true;
	}
	else
		return false;
}
bool imgSpace::sign(int x, int y, int color, int alpha)
{
	if (alpha == 0)
		return true;
	if (alpha == 0xff)
		return sign(x, y, color);
	if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
	{
		int pro = *(carr + (width * y) + x);
		int r = pro >> 16;
		int g = (pro >> 8) & 0xff;
		int b = pro & 0xff;
		int r2 = color >> 16;
		int g2 = (color >> 8) & 0xff;
		int b2 = color & 0xff;
		*(carr + (width * y) + x) = (((r * (0xff - alpha)) + (r2 * alpha)) / 0xff << 16) + (((g * (0xff - alpha)) + (g2 * alpha)) / 0xff << 8) + (((b * (0xff - alpha)) + (b2 * alpha)) / 0xff);
		return true;
	}
	else
		return false;
}
bool imgSpace::signA(int pos, int color, int alpha)
{
	if (alpha == 0)
		return true;
	//if (alpha == 0xff)
		//return sign(x, y, color);
	if ((pos >= 0) && (pos < (width * height)))
	{
		int pro = *(carr + pos);
		int r = pro >> 16;
		int g = (pro >> 8) % 0x100;
		int b = pro % 0x100;
		int r2 = color >> 16;
		int g2 = (color >> 8) % 0x100;
		int b2 = color % 0x100;
		*(carr + pos) = (((r * (0xff - alpha)) + (r2 * alpha)) / 0xff << 16) + (((g * (0xff - alpha)) + (g2 * alpha)) / 0xff << 8) + (((b * (0xff - alpha)) + (b2 * alpha)) / 0xff);
		return true;
	}
	else
		return false;
}
int imgSpace::getC(int x, int y)
{
	return *(carr + (width * y) + x);
}
int imgSpace::getA(int x, int y)
{
	return *(alpha + (width * y) + x);
}
bool imgSpace::setA(int x, int y, int size_x, int size_y, int alpha)
{
	if (x + size_x > width)
		size_x = width - x;
	if (y + size_y > height)
		size_y = height - y;
	if ((size_x < 0) || (size_y < 0))
		return false;
	int length = size_x * size_y;
	int offset = width - size_x;
	int i, j;
	i = 0;
	int point = x + (y * width);
	while (i < length)
	{
		for (j = 0; j < size_x; j++)
		{
			imgSpace::alpha[point] = alpha;
			i++;
			point++;
		}
		point += offset;
	}
	return true;
}
bool imgSpace::fill(int x, int y, int size_x, int size_y, int color, int alpha)
{
	if (x + size_x > width)
		size_x = width - x;
	if (y + size_y > height)
		size_y = height - y;
	if ((size_x < 0) || (size_y < 0))
		return false;
	int length = size_x * size_y;
	int limita = size_x;
	int offset = width - limita;
	int i, j;
	i = 0;
	int point = x + (y * width);
	while (i < length)
	{
		for (j = 0; j < limita; j++)
		{
			signA(point, color, alpha);
			i++;
			point++;
		}
		point += offset;
	}
	return true;
}
bool imgSpace::draw_line(int x1, int y1, int x2, int y2, int color)
{
	if ((x1 == x2) || (y1 == y2))
	{
		draw_line_stright(x1, y1, x2, y2, color);
		return true;
	}
	int cp = abs(y2 - y1) > abs(x2 - x1), x, y, dx, dy, sy;
	float e, de;
	if (cp)
	{
		y = x1;
		x1 = y1;
		y1 = y;
		y = x2;
		x2 = y2;
		y2 = y;
	}
	if (x1 > x2)
	{
		y = x1;
		x1 = x2;
		x2 = y;
		y = y1;
		y1 = y2;
		y2 = y;
	}
	dx = x2 - x1;
	dy = abs(y2 - y1);
	e = 0.0f;
	if (dx)
		de = dy / (float)dx;
	else
		de = 0.0f;
	y = y1;
	sy = (y1 < y2) ? 1 : -1;
	for (x = x1; x <= x2; x++)
	{
		if (cp)
			sign(y, x, color);
		else
			sign(x, y, color);
		e += de;
		if (e >= 0.5f)
		{
			y += sy;
			e -= 1.0f;
		}
	}
	return true;
}
int ipart(double x)
{
	return (int)floor(x);
}
// fractional part of x
double fpart(double x)
{
	return x - floor(x);
}
double rfpart(double x)
{
	return 1 - fpart(x);
}
bool imgSpace::draw_line_antialiasing(double x1, double y1, double x2, double y2, int color)
{
	x1 -= 0.5;
	y1 -= 0.5;
	x2 -= 0.5;
	y2 -= 0.5;
	boolean steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}
	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	double dx = x2 - x1;
	double dy = y2 - y1;
	double gradient;
	if (dx == 0.0)
		gradient = 1.0;
	else
		gradient = dy / dx;
	// handle first endpoint
	int xend = (int)round(x1);
	double yend = y1 + gradient * (xend - x1);
	double xgap = rfpart(x1 + 0.5);
	int xpxl1 = xend; // this will be used in the main loop
	int ypxl1 = ipart(yend);
	if (steep)
	{
		sign(ypxl1, xpxl1, color, (int)(rfpart(yend) * xgap * 0xff));
		sign(ypxl1 + 1, xpxl1, color, (int)(fpart(yend) * xgap * 0xff));
	}
	else
	{
		sign(xpxl1, ypxl1, color, (int)(rfpart(yend) * xgap * 0xff));
		sign(xpxl1, ypxl1 + 1, color, (int)(fpart(yend) * xgap * 0xff));
	}
	double intery = yend + gradient; // first y-intersection for the main loop
	// handle second endpoint
	xend = (int)round(x2);
	yend = y2 + gradient * (xend - x2);
	xgap = fpart(x2 + 0.5);
	int xpxl2 = xend; //this will be used in the main loop
	int ypxl2 = ipart(yend);
	if (steep)
	{
		sign(ypxl2, xpxl2, color, (int)(rfpart(yend) * xgap * 0xff));
		sign(ypxl2 + 1, xpxl2, color, (int)(fpart(yend) * xgap * 0xff));
	}
	else
	{
		sign(xpxl2, ypxl2, color, (int)(rfpart(yend) * xgap * 0xff));
		sign(xpxl2, ypxl2 + 1, color, (int)(fpart(yend) * xgap * 0xff));
	}
	// main loop
	if (steep)
	{
		for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
		{
			sign(ipart(intery), x, color, (int)(rfpart(intery) * 0xff));
			sign(ipart(intery) + 1, x, color, (int)(fpart(intery) * 0xff));
			intery = intery + gradient;
		}
	}
	else
	{
		for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
		{
			sign(x, ipart(intery), color, (int)(rfpart(intery) * 0xff));
			sign(x, ipart(intery) + 1, color, (int)(fpart(intery) * 0xff));
			intery = intery + gradient;
		}
	}
	return true;
}
bool imgSpace::draw_bezier(position* source, int num, int color)
{

}
bool imgSpace::draw_rectangle(int x, int y, int size_x, int size_y, int color)
{
	size_x--;
	size_y--;
	if ((size_x < 0) || (size_y < 0))
		return false;
	draw_line(x, y, x + size_x, y, color);
	draw_line(x + size_x, y, x + size_x, y + size_y, color);
	draw_line(x + size_x, y + size_y, x, y + size_y, color);
	draw_line(x, y + size_y, x, y, color);
	return true;
}
bool imgSpace::draw_circle(int x, int y, int rx, int ry, int color)
{
	int yTop = ry, yBottom, i, j;
	if (!rx)
	{
		for (j = -ry; j <= ry; j++)
			sign(x, y + j, color);
		return true;
	}
	for (i = 0; i <= rx; i++) {
		yBottom = yTop;
		while (pow(i - rx, 2.0) * pow(ry, 2.0) + pow(yTop - ry, 2.0) * pow(rx, 2.0) <= pow(rx, 2.0) * pow(ry, 2.0))
			yTop++;
		if (yBottom != yTop)
			yTop--;
		for (int j = yBottom; j <= yTop; j++)
		{
			sign(x + i - rx, y + j - ry, color);
			if (i != rx)
				sign(x - i + rx, y + j - ry, color);
			if (j != ry)
			{
				sign(x + i - rx, y - j + ry, color);
				if (i != rx)
					sign(x - i + rx, y - j + ry, color);
			}
		}
	}
	return true;
}
bool imgSpace::draw_line_stright(int x1, int y1, int x2, int y2, int color)
{
	if (x1 == x2)
	{
		if (y1 < y2)
			for (int i = y1; i <= y2; i++)
				sign(x1, i, color);
		else
			for (int i = y2; i <= y1; i++)
				sign(x1, i, color);
	}
	else if (y1 == y2)
	{
		if (x1 < x2)
			for (int i = x1; i <= x2; i++)
				sign(i, y1, color);
		else
			for (int i = x2; i <= x1; i++)
				sign(i, y1, color);
	}
	return true;
}
bool imgSpace::print(int xp, int yp, int fontSize, const char font[], wchar_t chr[], int color)
{
	FT_Library library;
	FT_Face face;

	if (FT_Init_FreeType(&library)) {
		//Could not initialize font library
		return false;
	}

	if (FT_New_Face(library, font, 0, &face)) {
		//Could not load font
		return false;
	}

	FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	FT_GlyphSlot glyph = face->glyph;

	unsigned int xOffset = 0;
	unsigned int yOffset = 0;

	for (int cr = 0; chr[cr] != 0; cr++) {
		if (FT_Load_Char(face, chr[cr], FT_LOAD_RENDER)) continue;

		yOffset = -glyph->bitmap_top;

		for (unsigned int x = 0; x < glyph->bitmap.width; x++) {
			for (unsigned int y = 0; y < glyph->bitmap.rows; y++) {
				unsigned int bitmapIndex = x + y * glyph->bitmap.width;
				sign(xp + x + xOffset, yp + y + yOffset, color, glyph->bitmap.buffer[bitmapIndex]);
			}
		}

		xOffset += glyph->bitmap.width + fontSize / 14;
		if (chr[cr] == ' ')
			xOffset += fontSize / 2;
	}
	FT_Done_Face(face);
	face = NULL;
	FT_Done_FreeType(library);
	library = NULL;
	return true;
}
bool imgSpace::print_mass(int xp, int yp, int fontSize, int length, const char font[], wchar_t chr[], int color)
{
	FT_Library library;
	FT_Face face;

	if (FT_Init_FreeType(&library)) {
		//Could not initialize font library
		return false;
	}

	if (FT_New_Face(library, font, 0, &face)) {
		//Could not load font
		return false;
	}

	FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	FT_GlyphSlot glyph = face->glyph;

	int xOffset = 0;
	int yOffset = 0;
	int nlens = 0;

	for (int cr = 0; chr[cr] != 0; cr++) {
		if (FT_Load_Char(face, chr[cr], FT_LOAD_RENDER)) continue;

		yOffset = -glyph->bitmap_top + (nlens * fontSize * 12 / 10);

		for (unsigned int x = 0; x < glyph->bitmap.width; x++) {
			for (unsigned int y = 0; y < glyph->bitmap.rows; y++) {
				unsigned int bitmapIndex = x + y * glyph->bitmap.width;
				sign(xp + x + xOffset, yp + y + yOffset, color, glyph->bitmap.buffer[bitmapIndex]);
			}
		}

		xOffset += glyph->bitmap.width + fontSize / 14;
		if (chr[cr] == ' ')
			xOffset += fontSize / 2;

		if (xOffset + getPrintLength(fontSize, font, chr[cr + 1]) > length)
		{
			xOffset = 0;
			nlens++;
		}
	}
	FT_Done_Face(face);
	face = NULL;
	FT_Done_FreeType(library);
	library = NULL;
	return true;
}
int imgSpace::getPrintLength(int fontSize, const char font[], wchar_t chr[])
{
	FT_Library library;
	FT_Face face;

	if (FT_Init_FreeType(&library)) {
		//Could not initialize font library
		return false;
	}

	if (FT_New_Face(library, font, 0, &face)) {
		//Could not load font
		return false;
	}

	FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	FT_GlyphSlot glyph = face->glyph;

	unsigned int xOffset = 0;

	for (int cr = 0; chr[cr] != 0; cr++) {
		if (FT_Load_Char(face, chr[cr], FT_LOAD_RENDER)) continue;

		xOffset += glyph->bitmap.width + fontSize / 14;
		if (chr[cr] == ' ')
			xOffset += fontSize / 2;
	}
	FT_Done_Face(face);
	face = NULL;
	FT_Done_FreeType(library);
	library = NULL;
	return xOffset;
}
int imgSpace::getPrintLength(int fontSize, const char font[], wchar_t chr)
{
	FT_Library library;
	FT_Face face;

	if (FT_Init_FreeType(&library)) {
		//Could not initialize font library
		return false;
	}

	if (FT_New_Face(library, font, 0, &face)) {
		//Could not load font
		return false;
	}

	FT_Set_Pixel_Sizes(face, fontSize, fontSize);

	FT_GlyphSlot glyph = face->glyph;

	unsigned int xOffset = 0;

	if (FT_Load_Char(face, chr, FT_LOAD_RENDER))
		return 0;

	xOffset += glyph->bitmap.width + fontSize / 14;
	if (chr == ' ')
		xOffset += fontSize / 2;
	int ret = glyph->bitmap.width;
	FT_Done_Face(face);
	face = NULL;
	FT_Done_FreeType(library);
	library = NULL;
	return xOffset;
}
bool imgSpace::spaceCopy(int px, int py, imgSpace* source)
{
	int length = source->width * source->height;
	int limita = source->width;
	int offset = width - limita;
	int i, j;
	i = 0;
	int point = px + (py * width);
	if (source->width <= width)//源图形未超宽
	{
		while (i < length)
		{
			for (j = 0; j < limita; j++)
			{
				if (source)
					signA(point, source->carr[i], source->alpha[i]);
				i++;
				point++;
			}
			point += offset;
		}
	}
	else//源图形超宽
	{
		while (i < length)
		{
			for (j = 0; j < width; j++)
			{
				signA(point, source->carr[i], source->alpha[i]);
				i++;
				point++;
			}
			i += px + limita - width;
			point += px;
		}
	}
	return true;
}
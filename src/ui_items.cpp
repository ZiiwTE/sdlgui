//UI项目
#include "ui_items.h"
wchar_t* conv(const wchar_t* source)
{
	wchar_t* re = (wchar_t*)malloc(50 * sizeof(wchar_t));
	if (re == 0)
		return NULL;
	int i;
	for (i = 0; source[i] != 0; i++)
		*(re + i) = source[i];
	*(re + i) = 0;
	return re;
}
//label项目函数
ui_item_label::ui_item_label() :ui_item_u(2938), size_x(64), size_y(32), fontSize(16)
{
	fresh();
}
bool ui_item_label::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	fresh();
	return true;
}
bool ui_item_label::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_label::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_label::mouseMove(int ix, int iy)
{
	return true;
}
bool ui_item_label::click(int ix, int iy)
{
	fresh();
	return true;
}
bool ui_item_label::unclick(int ix, int iy)
{
	fresh();
	return true;
}
bool ui_item_label::fresh()
{
	imgSpace nrender(size_x, size_y, 0xffffff, 0xff);
	int plength = nrender.getPrintLength(12, FONT_DEFAULT, text);
	nrender.print((size_x / 2) - (plength / 2), (size_y / 2) + 5, 12, FONT_DEFAULT, text, 0x000000);
	nrender.toLiner(image);
	return true;
}
//button项目函数
ui_item_button::ui_item_button() :ui_item_u(7259), size_x(0), size_y(0), fontSize(16), pressed(false), above(false), eventa(NULL)
{

}
bool ui_item_button::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	fresh();
	return true;
}
bool ui_item_button::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_button::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_button::mouseMove(int ix, int iy)
{
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
		above = true;
	else
		above = false;
	fresh();
	return true;
}
bool ui_item_button::click(int ix, int iy)
{
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
	{
		pressed = true;
	}
	else
	{
		pressed = false;
	}
	fresh();
	return true;
}
bool ui_item_button::unclick(int ix, int iy)
{
	if (pressed)
	{
		if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
			if (eventa)
				eventa();
	}
	pressed = false;
	fresh();
	return true;
}
bool ui_item_button::fresh()
{
	imgSpace nrender(size_x, size_y, 0xffffff, 0xff);
	if (above)
	{
		nrender.draw_rectangle(1, 1, size_x - 2, size_y - 2, COLOR_PRESSED);
		nrender.draw_rectangle(2, 2, size_x - 4, size_y - 4, 0xeeeeee);
	}
	if (pressed)
		nrender.fill(0, 0, size_x, size_y, COLOR_PRESSED, 0xff);
	nrender.draw_rectangle(0, 0, size_x, size_y, 0x000000);
	int plength = nrender.getPrintLength(12, FONT_DEFAULT, text);
	nrender.print((size_x / 2) - (plength / 2), (size_y / 2) + 5, 12, FONT_DEFAULT, text, 0x000000);
	nrender.toLiner(image);
	return true;
}
bool ui_item_button::setEvent(void(*funPtr)())
{
	eventa = funPtr;
	return true;
}
//
ui_item_checkBox::ui_item_checkBox() :ui_item_u(6395), size_x(96), size_y(42), fontSize(16), status(false), pressed(false), above(false)
{

}
bool ui_item_checkBox::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_checkBox::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_checkBox::mouseMove(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	if ((ix > 5) && (iy > center_y - 5) && (ix < 18) && (iy < center_y + 8))
		above = true;
	else
		above = false;
	fresh();
	return true;
}
bool ui_item_checkBox::click(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	if ((ix > 5) && (iy > center_y - 5) && (ix < 18) && (iy < center_y + 8))
		pressed = true;
	else
		pressed = false;
	fresh();
	return true;
}
bool ui_item_checkBox::unclick(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	if (pressed)
		if ((ix > 5) && (iy > center_y - 5) && (ix < 18) && (iy < center_y + 8))
			status = !status;
	pressed = false;
	fresh();
	return true;
}
bool ui_item_checkBox::fresh()
{
	imgSpace nrender(size_x, size_y, COLOR_WHITE, 0xff);
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	nrender.draw_rectangle(4, center_y - 6, 13, 13, COLOR_BLACK);
	if (above)
		nrender.draw_rectangle(5, center_y - 5, 11, 11, COLOR_PRESSED);
	if (pressed)
		nrender.fill(5, center_y - 5, 11, 11, COLOR_PRESSED, 0xff);
	if (status)
		nrender.fill(7, center_y - 3, 7, 7, COLOR_BLACK, 0xff);
	nrender.print(18, center_y + 5, 12, FONT_DEFAULT, text, COLOR_BLACK);
	nrender.toLiner(image);
	return true;
}
bool ui_item_checkBox::getStatus()
{
	return status;
}
//
ui_item_switch::ui_item_switch() :ui_item_u(5391), size_x(96), size_y(42), fontSize(16), status(false), pressed(false), above(false)
{

}
bool ui_item_switch::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_switch::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_switch::mouseMove(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	int sizeS_x = 32;
	int sizeS_y = 14;
	if ((ix > center_x - sizeS_x / 2) && (iy > center_y - sizeS_y / 2) && (ix < center_x + sizeS_x / 2) && (iy < center_y + sizeS_y / 2))
		above = true;
	else
		above = false;
	fresh();
	return true;
}
bool ui_item_switch::click(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	int sizeS_x = 32;
	int sizeS_y = 14;
	if ((ix > center_x - sizeS_x / 2) && (iy > center_y - sizeS_y / 2) && (ix < center_x + sizeS_x / 2) && (iy < center_y + sizeS_y / 2))
		pressed = true;
	else
		pressed = false;
	fresh();
	return true;
}
bool ui_item_switch::unclick(int ix, int iy)
{
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	int sizeS_x = 32;
	int sizeS_y = 14;
	if (pressed)
		if ((ix > center_x - sizeS_x / 2) && (iy > center_y - sizeS_y / 2) && (ix < center_x + sizeS_x / 2) && (iy < center_y + sizeS_y / 2))
			status = !status;
	pressed = false;
	fresh();
	return true;
}
bool ui_item_switch::fresh()
{
	imgSpace nrender(size_x, size_y, 0xffffff, 0xff);
	int center_x = size_x / 2;
	int center_y = size_y / 2;
	int sizeS_x = 32;
	int sizeS_y = 14;
	nrender.draw_rectangle(center_x - sizeS_x / 2, center_y - sizeS_y / 2, sizeS_x, sizeS_y, COLOR_BLACK);
	if (above || pressed)
		nrender.draw_rectangle(center_x - sizeS_x / 2 + 1, center_y - sizeS_y / 2 + 1, sizeS_x - 2, sizeS_y - 2, COLOR_PRESSED);
	if (pressed)
	{
		if (status)
			nrender.fill(center_x + 2, center_y - sizeS_y / 2 + 4, sizeS_x / 2 - 6, sizeS_y - 8, COLOR_PRESSED, 0xff);
		else
			nrender.fill(center_x - sizeS_x / 2 + 4, center_y - sizeS_y / 2 + 4, sizeS_x / 2 - 6, sizeS_y - 8, COLOR_PRESSED, 0xff);
	}
	if (status)
		nrender.draw_rectangle(center_x, center_y - sizeS_y / 2 + 2, sizeS_x / 2 - 2, sizeS_y - 4, COLOR_BLACK);
	else
		nrender.draw_rectangle(center_x - sizeS_x / 2 + 2, center_y - sizeS_y / 2 + 2, sizeS_x / 2 - 2, sizeS_y - 4, COLOR_BLACK);
	int plength = nrender.getPrintLength(10, FONT_DEFAULT, text);
	nrender.print((center_x)-(plength / 2), center_y - 9, 10, FONT_DEFAULT, text, COLOR_BLACK);
	wchar_t* F = conv(L"OFF");
	nrender.print((center_x)-36, center_y + 4, 10, FONT_DEFAULT, F, COLOR_BLACK);
	F = conv(L"ON");
	nrender.print((center_x)+17, center_y + 4, 10, FONT_DEFAULT, F, COLOR_BLACK);
	if (F)
		free(F);
	nrender.toLiner(image);
	return true;
}
bool ui_item_switch::getStatus()
{
	return status;
}
//
ui_item_topmenusubitem::ui_item_topmenusubitem() :ui_item_u(4619)
{
	fresh();
}
bool ui_item_topmenusubitem::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_topmenusubitem::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_topmenusubitem::mouseMove(int ix, int iy)
{
	return true;
}
bool ui_item_topmenusubitem::click(int ix, int iy)
{
	fresh();
	return true;
}
bool ui_item_topmenusubitem::unclick(int ix, int iy)
{
	fresh();
	return true;
}
bool ui_item_topmenusubitem::fresh()
{
	return true;
}
//
ui_item_topmenuitem::ui_item_topmenuitem() : ui_item_u(5938), size_x(64), nitems(0), items(NULL), motherPressArr(NULL)
{
	items = (ui_item_topmenusubitem**)malloc(511 * sizeof(ui_item_topmenusubitem*));
	fresh();
}
bool ui_item_topmenuitem::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	fresh();
	return true;
}
bool ui_item_topmenuitem::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_topmenuitem::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_topmenuitem::addItem(ui_item_topmenusubitem* item)
{
	items[nitems] = item;
	nitems++;
	fresh();
	return true;
}
bool ui_item_topmenuitem::mouseMove(int ix, int iy)
{
	fresh();
	return true;
}
bool ui_item_topmenuitem::click(int ix, int iy)
{
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
	{
		pressed = true;
	}
	else
	{
		pressed = false;
	}
	fresh();
	return true;
}
bool ui_item_topmenuitem::unclick(int ix, int iy)
{
	pressed = false;
	fresh();
	return true;
}
bool ui_item_topmenuitem::fresh()
{
	imgSpace nrender;
	if (pressed)
		nrender = imgSpace(size_x, size_y, COLOR_PRESSED, 0xff);
	else
		nrender = imgSpace(size_x, size_y, 0xffffff, 0xff);
	int plength = nrender.getPrintLength(12, FONT_DEFAULT, text);
	nrender.print((size_x / 2) - (plength / 2), (size_y / 2) + 5, 12, FONT_DEFAULT, text, 0x000000);
	nrender.draw_line(0, 0, 0, size_y - 1, 0x000000);
	nrender.draw_line(size_x - 1, 0, size_x - 1, size_y - 1, 0x000000);
	nrender.toLiner(image);
	return true;
}
bool ui_item_topmenuitem::signSuper(bool* arr)
{
	motherPressArr = arr;
	return true;
}
bool ui_item_topmenuitem::delSuper()
{
	if (motherPressArr == NULL)
		return false;
	motherPressArr = NULL;
	return true;
}
//
ui_item_top::ui_item_top() :ui_item_u(5618), size_x(1920), size_y(256), size(16), nitems(0), items(NULL)
{
	fresh();
	items = (ui_item_topmenuitem**)malloc(511 * sizeof(ui_item_topmenuitem*));
}
bool ui_item_top::setSize(int height)
{
	size = height;
	for (int i = 0; i < nitems; i++)
	{
		items[i]->setSize(items[i]->size_x, height);
	}
	fresh();
	return true;
}
bool ui_item_top::addItem(ui_item_topmenuitem* item)
{
	item->setSize(item->size_x, size);
	item->signSuper(&pressed);
	items[nitems] = item;
	nitems++;
	fresh();
	return true;
}
bool ui_item_top::mouseMove(int ix, int iy)
{
	int offset = -1;
	for (int i = 0; i < nitems; i++)
	{
		items[i]->mouseMove(ix - offset, iy);
		offset += items[i]->size_x - 1;
	}
	fresh();
	return true;
}
bool ui_item_top::click(int ix, int iy)
{
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size))
	{
		pressed = true;
	}
	else
	{
		pressed = false;
	}
	int offset = -1;
	for (int i = 0; i < nitems; i++)
	{
		items[i]->click(ix - offset, iy);
		offset += items[i]->size_x - 1;
	}
	fresh();
	return true;
}
bool ui_item_top::unclick(int ix, int iy)
{
	int offset = -1;
	for (int i = 0; i < nitems; i++)
	{
		items[i]->unclick(ix - offset, iy);
		offset += items[i]->size_x;
	}
	fresh();
	return true;
}
bool ui_item_top::fresh()
{
	imgSpace nrender(size_x, size_y, 0xffffff, 0x00);
	nrender.setA(0, 0, size_x, size, 0xff);
	nrender.fill(0, 0, size_x, size, 0xffffff, 0xff);
	int offset = -1;
	for (int i = 0; i < nitems; i++)
	{
		nrender.copyFromLiner(offset, 0, items[i]->image);
		offset += items[i]->size_x - 1;
	}
	nrender.draw_line(0, size - 1, size_x - 1, size - 1, 0x000000);
	nrender.toLiner(image);
	return true;
}
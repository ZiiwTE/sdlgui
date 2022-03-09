#include "ui_universal.h"
//主项目类函数
ui_item_u::ui_item_u(int tp) :type(tp), visible(false), x(0), y(0)
{
	for (int i = 0; i < P_MAX; i++)
		image[i].status = PIXEL_END;
}
bool ui_item_u::setVisible(bool nset)
{
	visible = nset;
	return true;
}
bool ui_item_u::getVisible()
{
	return visible;
}
int ui_item_u::getType()
{
	return type;
}
bool ui_item_u::setPosition(int nx, int ny)
{
	x = nx;
	y = ny;
	return true;
}
int ui_item_u::getX()
{
	return x;
}
int ui_item_u::getY()
{
	return y;
}
bool ui_item_u::textInput(char* text)
{
	return true;
}
bool ui_item_u::keyDown(int type)
{
	return true;
}
//主项目类文本函数
ui_item_u_text::ui_item_u_text() :text(L"")
{

}
bool ui_item_u_text::setText(const char ntext[])
{
	int i;
	for (i = 0; (i < 255) && (ntext[i] != 0); i++)
		text[i] = ntext[i];
	text[i] = 0;
	return true;
}
bool ui_item_u_text::setText(const wchar_t ntext[])
{
	int i;
	for (i = 0; (i < 255) && (ntext[i] != 0); i++)
		text[i] = ntext[i];
	text[i] = 0;
	return true;
}
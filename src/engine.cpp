//GUI引擎
#include "engine.h"




engine::engine(int w, int h) :ui_item_u(7395), width(w), height(h), nitems(0)
{
	items = (ui_item_u**)malloc(512 * sizeof(ui_item_u*));
	running = true;
	t = std::thread(std::bind(&engine::loop, this));
}
bool engine::addItem(ui_item_u* item)
{
	items[nitems] = item;
	nitems++;
	return true;
}
bool engine::mouseMove(int ix, int iy)
{
	for (int i = 0; i < nitems; i++)
	{
		items[i]->mouseMove(ix - items[i]->x, iy - items[i]->y);
	}
	return true;
}
bool engine::click(int ix, int iy)
{
	for (int i = 0; i < nitems; i++)
	{
		items[i]->click(ix - items[i]->x, iy - items[i]->y);
	}
	return true;
}
bool engine::unclick(int ix, int iy)
{
	for (int i = 0; i < nitems; i++)
	{
		items[i]->unclick(ix - items[i]->x, iy - items[i]->y);
	}
	return true;
}
bool engine::textInput(char* text)
{
	for (int i = 0; i < nitems; i++)
	{
		items[i]->textInput(text);
	}
	return true;
}
bool engine::fresh()
{
	imgSpace nrender(width, height, 0xffffff, 0xff);
	nrender.resizeClear(width, height, 0xffffff, 0xff);
	for (int i = 0; i < nitems; i++)
	{
		if (items[i]->getVisible())
			nrender.copyFromLiner(items[i]->x, items[i]->y, items[i]->image);
	}
	nrender.draw_rectangle(0, 0, width, height, 0x000000);

	//测试复制器用的
	//imgSpace nn(2, 2, 0, 255);
	//nn.draw_rectangle(0, 0, 2, 2, 0x000000);
	//pixel dr[444];
	//nn.toLiner(dr);
	//nrender.copyFromLiner(200, 100, dr);

	nrender.toLiner(image);
	return true;
}
bool engine::loop()
{
	while (running)
	{
		fresh();
		Sleep(clock);
	}
	return true;
}
bool engine::setClock(int time)
{
	if (time < 1)
		return false;
	clock = time;
	return true;
}
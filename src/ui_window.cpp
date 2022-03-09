#include "ui_window.h"
ui_item_window::ui_item_window() :ui_item_u(8624), size_x(64), size_y(32)
{

}
bool ui_item_window::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	return true;
}
bool ui_item_window::setText(const char ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_window::setText(const wchar_t ntext[])
{
	bool rv = ui_item_u_text::setText(ntext);
	fresh();
	return rv;
}
bool ui_item_window::setPlayer(ui_item_u* source)
{
	if (!source)
		return false;
	inside = source;
	return true;
}
bool ui_item_window::setClock(int time)
{
	if (time < 1)
		return false;
	clock = time;
	return true;
}
bool ui_item_window::mouseMove(int ix, int iy)
{
	if ((ix > size_x - 15) && (iy > 2) && (ix < size_x - 2) && (iy < 15))
		cAbove = true;
	else
		cAbove = false;
	if (!cPressed)
	{
		if (move)
			setPosition(getX() + ix - oX, getY() + iy - oY);
		int Nx = x;
		int Ny = y;
		int Nsize_x = size_x;
		int Nsize_y = size_y;
		int NoX = oX;
		int NoY = oY;
		switch (resizeX)
		{
		case(RESIZE_LOW):
			Nx += ix - oX;
			Nsize_x += oX - ix;
			if (Nsize_x < SWITCH)
			{
				Nx -= ix - oX;
				Nsize_x = SWITCH;
			}
			break;
		case(RESIZE_HIGH):
			Nsize_x += ix - oX;
			NoX += ix - oX;
			if (Nsize_x < SWITCH)
			{
				NoX -= ix - oX;
				Nsize_x = SWITCH;
			}
			break;
		}
		switch (resizeY)
		{
		case(RESIZE_LOW):
			Ny += iy - oY;
			Nsize_y += oY - iy;
			if (Nsize_y < TOP)
			{
				Ny -= iy - oY;
				Nsize_y = TOP;
			}
			break;
		case(RESIZE_HIGH):
			Nsize_y += iy - oY;
			NoY += iy - oY;
			if (Nsize_y < TOP + 1)
			{
				NoY -= iy - oY;
				Nsize_y = TOP + 1;
			}
			break;
		}
		x = Nx;
		y = Ny;
		size_x = Nsize_x;
		size_y = Nsize_y;
		oX = NoX;
		oY = NoY;
	}
	return true;
}
bool ui_item_window::click(int ix, int iy)
{
	if ((ix > size_x - 15) && (iy > 2) && (ix < size_x - 2) && (iy < 15))
		cPressed = true;
	else
		cPressed = false;
	oX = ix;
	oY = iy;
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < TOP))
	{
		move = true;
	}
	if ((ix > -RESIZE_LIMIT) && (ix < RESIZE_LIMIT))
	{
		resizeX = RESIZE_LOW;
		move = false;
	}
	if ((ix > size_x - RESIZE_LIMIT) && (ix < size_x + RESIZE_LIMIT))
	{
		resizeX = RESIZE_HIGH;
		move = false;
	}
	if ((iy > -RESIZE_LIMIT) && (iy < RESIZE_LIMIT))
	{
		resizeY = RESIZE_LOW;
		move = false;
	}
	if ((iy > size_y - RESIZE_LIMIT) && (iy < size_y + RESIZE_LIMIT))
	{
		resizeY = RESIZE_HIGH;
		move = false;
	}
	return true;
}
bool ui_item_window::unclick(int ix, int iy)
{
	if (cPressed)
	{
		if ((ix > size_x - 15) && (iy > 2) && (ix < size_x - 2) && (iy < 15))
			visible = false;
	}
	cPressed = false;
	move = false;
	resizeX = RESIZE_FALSE;
	resizeY = RESIZE_FALSE;
	return true;
}
bool ui_item_window::fresh()
{
	int X = size_x;
	int Y = size_y;
	imgSpace nrender(X, Y, COLOR_WHITE, 0xff);
	if (inside)
	{
		nrender.copyFromLiner(0, TOP, inside->image);
	}
	nrender.draw_rectangle(X - 15, 2, 13, 13, COLOR_BLACK);
	if (cAbove)
		nrender.draw_rectangle(X - 14, 3, 11, 11, COLOR_PRESSED);
	if (cPressed)
		nrender.fill(X - 14, 3, 11, 11, COLOR_PRESSED, 0xff);
	nrender.draw_line(X - 12, 5, X - 6, 11, COLOR_BLACK);
	nrender.draw_line(X - 12, 11, X - 6, 5, COLOR_BLACK);
	nrender.draw_rectangle(0, 0, X, Y, COLOR_BLACK);
	nrender.draw_line(0, TOP, X, TOP, COLOR_BLACK);
	nrender.toLiner(image);
	return true;
}
bool ui_item_window::loop()
{
	while (running)
	{
		fresh();
		Sleep(clock);
	}
	return true;
}
bool ui_item_window::start()
{
	running = true;
	t = std::thread(std::bind(&ui_item_window::loop, this));
	return true;
}
bool ui_item_window::end()
{
	if (running)
	{
		running = false;
		t.join();
	}
	return true;
}
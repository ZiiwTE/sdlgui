#include "ui_textfield.h"
ui_item_textfield::ui_item_textfield() :ui_item_u(7839), size_x(64), size_y(32), pressed(false), focus(false), fontSize(14), text(L"")
{
	textLength[0] = -1;
	textNum[0] = -1;
}
bool ui_item_textfield::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	numFresh();
	fresh();
	return true;
}
bool ui_item_textfield::setText(const char ntext[])
{
	int i;
	imgSpace render(1, 1, COLOR_BLACK);
	for (i = 0; (i < 255) && (ntext[i] != 0); i++)
	{
		text[i] = ntext[i];
		textLength[i] = render.getPrintLength(fontSize, FONT_DEFAULT, text[i]);
	}
	text[i] = 0;
	textLength[i] = -1;
	numFresh();
	fresh();
	return true;
}
bool ui_item_textfield::setText(const wchar_t ntext[])
{
	int i;
	imgSpace render(1, 1, COLOR_BLACK);
	for (i = 0; (i < 255) && (ntext[i] != 0); i++)
	{
		text[i] = ntext[i];
		textLength[i] = render.getPrintLength(fontSize, FONT_DEFAULT, text[i]);
	}
	text[i] = 0;
	textLength[i] = -1;
	numFresh();
	fresh();
	return true;
}
wchar_t* ui_item_textfield::getText()
{
	return text;
}
bool ui_item_textfield::numFresh()
{
	int lengthLimit = size_x - 4;
	int i = 0;//计算数量
	int lint = 0;//行数量
	int lcount;//当前行字符数量
	int length;//当前行长度
	while (textLength[i] != -1)
	{
		lcount = 0;
		length = 0;
		while ((length + textLength[i] <= lengthLimit) && (textLength[i] != -1))
		{
			length += textLength[i];
			lcount++;
			i++;
		}
		textNum[lint] = lcount;
		lint++;
	}
	textNum[lint] = -1;
	return true;
}
bool ui_item_textfield::offFresh()
{
	int lenOff;
	int chrCnt;
	lenOff = 0;
	chrCnt = 0;
	while ((chrCnt + textNum[lenOff] < check1) && (textNum[lenOff] != -1))
	{
		chrCnt += textNum[lenOff];
		lenOff++;
	}
	offL1 = lenOff;
	offX1 = 0;
	while (chrCnt < check1)
	{
		offX1 += textLength[chrCnt];
		chrCnt++;
	}
	lenOff = 0;
	chrCnt = 0;
	while ((chrCnt + textNum[lenOff] < check1) && (textNum[lenOff] != -1))
	{
		chrCnt += textNum[lenOff];
		lenOff++;
	}
	offL2 = lenOff;
	offX2 = 0;
	while (chrCnt < check2)
	{
		offX2 += textLength[chrCnt];
		chrCnt++;
	}
	return true;
}
bool ui_item_textfield::mouseMove(int ix, int iy)
{
	if (pressed)
		if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
		{
			check2 = 0;
			int nlens;//测试行数量
			for (nlens = 0; (nlens + 1) * fontSize * 12 / 10 < iy; nlens++)
			{
				if (textNum[nlens] == -1)
					break;
				check2 += textNum[nlens];
			}
			offL2 = nlens;
			if (textNum[nlens] == -1)
				offL2--;
			int offX = 0;//测试行X轴当前偏移
			int limitX = ix + 2;
			int chrOff = 0;
			while (offX + textLength[check2] < limitX)
			{
				if (textLength[check2] == -1)
					break;
				if (chrOff == textNum[nlens])
					break;
				offX += textLength[check2];
				chrOff++;
				check2++;
			}
			if ((textNum[nlens] == -1) && (nlens != 0))
				for (int fc = 0; fc < textNum[nlens - 1]; fc++)
					offX += textLength[check2 - fc - 1];
			offX2 = offX;
		}
	fresh();
	return true;
}
bool ui_item_textfield::click(int ix, int iy)
{
	if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
	{
		focus = true;
		pressed = true;
		check1 = 0;
		int nlens;//测试行数量
		for (nlens = 0; (nlens + 1) * fontSize * 12 / 10 < iy; nlens++)
		{
			if (textNum[nlens] == -1)
				break;
			check1 += textNum[nlens];
		}
		offL1 = nlens;
		if (textNum[nlens] == -1)
			offL1--;
		int offX = 0;//测试行X轴当前偏移
		int limitX = ix + 2;
		int chrOff = 0;
		while (offX + textLength[check1] < limitX)
		{
			if (textLength[check1] == -1)
				break;
			if (chrOff == textNum[nlens])
				break;
			offX += textLength[check1];
			chrOff++;
			check1++;
		}
		if ((textNum[nlens] == -1) && (nlens != 0))
			for (int fc = 0; fc < textNum[nlens - 1]; fc++)
				offX += textLength[check1 - fc - 1];
		offX1 = offX;
		check2 = 0;
		nlens;//测试行数量
		for (nlens = 0; (nlens + 1) * fontSize * 12 / 10 < iy; nlens++)
		{
			if (textNum[nlens] == -1)
				break;
			check2 += textNum[nlens];
		}
		offL2 = nlens;
		if (textNum[nlens] == -1)
			offL2--;
		offX = 0;//测试行X轴当前偏移
		limitX = ix + 2;
		chrOff = 0;
		while (offX + textLength[check2] < limitX)
		{
			if (textLength[check2] == -1)
				break;
			if (chrOff == textNum[nlens])
				break;
			offX += textLength[check2];
			chrOff++;
			check2++;
		}
		if ((textNum[nlens] == -1) && (nlens != 0))
			for (int fc = 0; fc < textNum[nlens - 1]; fc++)
				offX += textLength[check2 - fc - 1];
		offX2 = offX;
	}
	else
	{
		focus = false;
		pressed = false;
	}
	fresh();
	return true;
}
bool ui_item_textfield::unclick(int ix, int iy)
{
	if(pressed)
		if ((ix > 0) && (iy > 0) && (ix < size_x) && (iy < size_y))
		{
			check2 = 0;
			int nlens;//测试行数量
			for (nlens = 0; (nlens + 1) * fontSize * 12 / 10 < iy; nlens++)
			{
				if (textNum[nlens] == -1)
					break;
				check2 += textNum[nlens];
			}
			offL2 = nlens;
			if (textNum[nlens] == -1)
				offL2--;
			int offX = 0;//测试行X轴当前偏移
			int limitX = ix + 2;
			int chrOff = 0;
			while (offX + textLength[check2] < limitX)
			{
				if (textLength[check2] == -1)
					break;
				if (chrOff == textNum[nlens])
					break;
				offX += textLength[check2];
				chrOff++;
				check2++;
			}
			if ((textNum[nlens] == -1) && (nlens != 0))
				for (int fc = 0; fc < textNum[nlens - 1]; fc++)
					offX += textLength[check2 - fc - 1];
			offX2 = offX;
		}
	pressed = false;
	fresh();
	return true;
}
bool ui_item_textfield::textInput(char* ntext)
{
	if (ntext[0] == 1)
		return false;
	if (check1 < 0)
		check1 = 0;
	if (check2 < 0)
		check2 = 0;
	int num;
	for (num = 0; ntext[num] != 0; num++);
	int lastPtr;
	for (lastPtr = 0; text[lastPtr] != 0; lastPtr++);
	if (focus)
	{
		int checkTop;//最高选区
		bool flag = false;
		if (check1 < check2)
		{
			checkTop = check2;
			check2 = check1;
			flag = true;
		}
		if (check1 > check2)
		{
			checkTop = check1;
			check1 = check2;
			flag = true;
		}
		if (flag)
		{
			int offset = checkTop - check1;
			lastPtr -= offset;
			int i;
			for (i = checkTop; text[i] != 0; i++)
			{
				text[i - offset] = text[i];
				textLength[i - offset] = textLength[i];
			}
			text[i - offset] = 0;
			textLength[i - offset] = -1;
		}
		if (check1 == check2)
		{
			imgSpace render(1, 1, COLOR_BLACK);
			while (lastPtr >= check1)
			{
				text[lastPtr + num] = text[lastPtr];
				textLength[lastPtr + num] = textLength[lastPtr];
				lastPtr--;
			}
			for (int i = 0; i < num; i++)
			{
				text[check1 + i] = ntext[i];
				textLength[check1 + i] = render.getPrintLength(fontSize, FONT_DEFAULT, ntext[i]);
			}
			check1 += num;
			check2 += num;
		}
	}
	numFresh();
	offFresh();
	fresh();
	return true;
}
bool ui_item_textfield::fresh()
{
	imgSpace nrender(size_x, size_y, COLOR_WHITE, 0xff);
	if (focus)
	{
		if (check1 == check2)
			nrender.draw_line(offX1 + 1, offL1 * fontSize * 12 / 10, offX1 + 1, (offL2 + 1) * fontSize * 12 / 10, COLOR_BLACK);
		else
		{
			if (offL1 == offL2)
			{
				if (offX1 < offX2)
					nrender.fill(offX1 + 1, offL1 * fontSize * 12 / 10 + 1, offX2 - offX1 + 1, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
				else
					nrender.fill(offX2 + 1, offL2 * fontSize * 12 / 10 + 1, offX1 - offX2 + 1, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
			}
			else
			{
				if (offL1 < offL2)
				{
					nrender.fill(offX1 + 1, offL1 * fontSize * 12 / 10 + 1, size_x - offX1, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
					for (int i = offL1 + 1; i < offL2; i++)
						nrender.fill(0, i * fontSize * 12 / 10 + 1, size_x, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
					nrender.fill(1, offL2 * fontSize * 12 / 10 + 1, offX2, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
				}
				else
				{
					nrender.fill(offX2 + 1, offL2 * fontSize * 12 / 10 + 1, size_x - offX2, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
					for (int i = offL2 + 1; i < offL1; i++)
						nrender.fill(0, i * fontSize * 12 / 10 + 1, size_x, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
					nrender.fill(1, offL1 * fontSize * 12 / 10 + 1, offX1, fontSize * 12 / 10, COLOR_PRESSED, 0xff);
				}
			}
		}
		nrender.draw_rectangle(1, 1, size_x - 2, size_y - 2, COLOR_PRESSED);
	}
	nrender.draw_rectangle(0, 0, size_x, size_y, COLOR_BLACK);
	nrender.print_mass(2, fontSize, fontSize, size_x - 4, FONT_DEFAULT, text, COLOR_BLACK);
	nrender.toLiner(image);
	return true;
}
#include "ui_linerecorder.h"
value_record::value_record()
{
	new (this)value_record(1);
}
value_record::value_record(int limit) :lengthLimit(limit > 0 ? limit : 1)
{
	records = (double*)malloc(lengthLimit * sizeof(double));
}
bool value_record::addResize(int nLimit)
{
	if (nLimit < 1)
		return false;
	resize = nLimit;
	return true;
}
bool value_record::addRecord(double value)
{
	if (resize != 0)
	{
		double* newRecord = (double*)malloc(resize * sizeof(double));
		if (!newRecord)
			goto end;
		if (length > resize)//新空间不足
		{
			start += length - resize;
			start %= lengthLimit;
			length = resize;
		}
		for (int i = 0; i < length; i++)
			newRecord[i] = records[(start + i) % lengthLimit];
		lengthLimit = resize;
		resize = 0;
		start = 0;
		free(records);
		records = newRecord;
	}
end:
	if (length == lengthLimit)
	{
		records[(start + length) % lengthLimit] = value;
		start++;
		start %= lengthLimit;
	}
	else
	{
		records[(start + length) % lengthLimit] = value;
		length++;
	}
	return true;
}
int value_record::getRecord(double* store, int limit)
{
	int fLength = limit < length ? limit : length;
	for (int i = 1; i <= fLength; i++)
		store[i - 1] = records[(start + fLength - i) % lengthLimit];
	return fLength;
}
double value_record::getMax(int limit)
{
	int fLength = limit < length ? limit : length;
	double max = records[start];
	for (int i = 0; i < fLength; i++)
	{
		if (records[(start + i) % lengthLimit] > max)
			max = records[(start + i) % lengthLimit];
	}
	return max;
}
double value_record::getMin(int limit)
{
	int fLength = limit < length ? limit : length;
	double min = records[start];
	for (int i = 0; i < fLength; i++)
	{
		if (records[(start + i) % lengthLimit] < min)
			min = records[(start + i) % lengthLimit];
	}
	return min;
}
//                  -------                  //
ui_item_linerecorder::ui_item_linerecorder() : ui_item_u(5820), size_x(64), size_y(32)
{

}
ui_item_linerecorder::~ui_item_linerecorder()
{
	if (running)
	{
		running = false;
		t.join();
	}
	return;
}
bool ui_item_linerecorder::setSize(int width, int height)
{
	size_x = width;
	size_y = height;
	for (int i = 0; i < recordNum; i++)
		record[i].addResize(width);
	return true;
}
bool ui_item_linerecorder::addRecordVar(int* var)
{
	if (var)
	{
		record[recordNum] = value_record(size_x);
		recordArray[recordNum] = var;
		recordtype[recordNum] = RECORD_INT;
		recordColor[recordNum] = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + (rand() & 0xff);
		recordVisible[recordNum] = true;
		recordNum++;
		return true;
	}
	else
	{
		return false;
	}
}
bool ui_item_linerecorder::addRecordVar(float* var)
{
	if (var)
	{
		record[recordNum] = value_record(size_x);
		recordArray[recordNum] = var;
		recordtype[recordNum] = RECORD_FLOAT;
		recordColor[recordNum] = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + (rand() & 0xff);
		recordVisible[recordNum] = true;
		recordNum++;
		return true;
	}
	else
	{
		return false;
	}
}
bool ui_item_linerecorder::addRecordVar(double* var)
{
	if (var)
	{
		record[recordNum] = value_record(size_x);
		recordArray[recordNum] = var;
		recordtype[recordNum] = RECORD_DOUBLE;
		recordColor[recordNum] = ((rand() & 0xff) << 16) + ((rand() & 0xff) << 8) + (rand() & 0xff);
		recordVisible[recordNum] = true;
		recordNum++;
		return true;
	}
	else
	{
		return false;
	}
}
bool ui_item_linerecorder::setClock(int time)
{
	if (time < 1)
		return false;
	clock = time;
	return true;
}
bool ui_item_linerecorder::mouseMove(int ix, int iy)
{
	return true;
}
bool ui_item_linerecorder::click(int ix, int iy)
{
	return true;
}
bool ui_item_linerecorder::unclick(int ix, int iy)
{
	return true;
}
bool ui_item_linerecorder::fresh()
{
	imgSpace nrender(size_x, size_y, COLOR_WHITE, 0xff);
	int playLength = size_x;
	int playHeight = size_y;
	if (recordNum != 0)
	{
		double max = record[0].getMax(playLength);
		double min = record[0].getMin(playLength);
		for (int i = 0; i < recordNum; i++)
		{
			if (record[i].getMax(playLength) > max)
				max = record[i].getMax(playLength);
			if (record[i].getMin(playLength) < min)
				min = record[i].getMin(playLength);
		}
		if (max == min)
		{
			max += 1;
			min -= 1;
		}
		double diff = max - min;
		double** resource = (double**)malloc(recordNum * sizeof(double*));//原统计数据
		if (resource)
			for (int i = 0; i < recordNum; i++)
				resource[i] = (double*)malloc(playLength * sizeof(double));
		int* subLength = (int*)malloc(recordNum * sizeof(int));//统计长度
		if (resource && subLength)
		{
			for (int i = 0; i < recordNum; i++)
			{
				if (resource[i])
					subLength[i] = record[i].getRecord(resource[i], playLength);
			}
			for (int i = 0; i < recordNum; i++)
			{
				if ((resource[i]) && (recordVisible[i]))
				{
					int oldX = playLength;
					int oldY = (int)(((max - ((resource[i])[0])) * (playHeight - 5) / diff) + 2);
					for (int j = 0; (j < subLength[i]) && (j < playLength); j++)
					{
						//nrender.sign(playLength - j, (int)(((max - ((resource[i])[j])) * (playHeight - 5) / diff) + 2), recordColor[i]);
						nrender.draw_line(oldX, oldY, playLength - j, (int)(((max - ((resource[i])[j])) * (playHeight - 5) / diff) + 2), recordColor[i]);
						oldX = playLength - j;
						oldY = (int)(((max - ((resource[i])[j])) * (playHeight - 5) / diff) + 2);
					}
				}
			}
		}
		if (resource)
		{
			for (int i = 0; i < recordNum; i++)
			{
				if (resource[i] != NULL)
				{
					free(resource[i]);
					resource[i] = NULL;
				}
			}
			free(resource);
			resource = NULL;
		}
		if (subLength)
		{
			free(subLength);
			subLength = NULL;
		}
	}
	nrender.draw_rectangle(0, 0, playLength, playHeight, COLOR_BLACK);
	nrender.toLiner(image);
	return true;
}
bool ui_item_linerecorder::recordRecord()
{
	double temp;
	for (int i = 0; i < recordNum; i++)
	{
		switch (recordtype[i])
		{
		case RECORD_INT:
			temp = (double)(*((int*)recordArray[i]));
			break;
		case RECORD_FLOAT:
			temp = (double)(*((float*)recordArray[i]));
			break;
		case RECORD_DOUBLE:
			temp = *((double*)recordArray[i]);
			break;
		default:
			temp = 0;
		}
		record[i].addRecord(temp);
	}
	return true;
}
bool ui_item_linerecorder::loop()
{
	while (running)
	{
		recordRecord();
		fresh();
		Sleep(clock);
	}
	return true;
}
bool ui_item_linerecorder::start()
{
	running = true;
	t = std::thread(std::bind(&ui_item_linerecorder::loop, this));
	return true;
}
bool ui_item_linerecorder::end()
{
	if (running)
	{
		running = false;
		t.join();
	}
	return true;
}
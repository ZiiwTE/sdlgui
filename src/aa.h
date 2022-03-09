#pragma once
#include <atlimage.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "engine.h"
#include "ui_items.h"
#include "ui_textfield.h"
#include "proMain.h"
#include "ui_linerecorder.h"
#include "ui_window.h"
class programnw
{
public:
	programnw();
	pixel* getOrginalImg();
	//CImageÎ¬»¤
	bool imgArrWork;
	engine itembox;
private:
	int width;
	int height;
	CImage* imgArr;
};
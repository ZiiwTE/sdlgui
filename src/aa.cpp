//程序主体对象
#include "aa.h"
using namespace std;
struct xsnode
{
	int xh;
	char xm[0xff];
	int cj;
};
xsnode start[0xffff];
int num;
ui_item_linerecorder* lr;
ui_item_textfield* t1;
ui_item_textfield* t2;
ui_item_textfield* t3;
ui_item_textfield* xinxi;

double b;
double a;
double c;
double d=3;
double tt;
void t2t()
{
	while (true)
	{
		tt += 0.001;
		a = sin(tt);
		b = cos(tt);
		c = a * b;
		//d += 0.005/(tt+1);
		Sleep(3);
	}
}

std::thread ttr(t2t);

void addi()
{
	lr->setSize(200, 200);
}

void cxxxh()
{
	char tmp[0xffff];
	
	int nxh = 0;
	int i = 0;
	while (t1->getText()[i] != 0)
	{
		nxh = nxh * 10;
		nxh += t1->getText()[i] - '0';
		i++;
	}

	char tmpt[0xffff];
	char* pt = tmpt;
	tmp[0] = 0;
	tmpt[0] = 0;
	xsnode* p = start;
	int t = 0;
	while (t<num)
	{
		if (p->xh == nxh)
		{
			sprintf_s(tmp, "grade:%d   --NEXT--               ", p->cj);
			for (int i = 0; tmp[i] != 0; i++)
			{
				*pt = tmp[i];
				pt++;
			}
			*pt = 0;
		}
		t++;
		p++;
	}
	xinxi->setText(tmpt);
}

void cxx()
{
	char tmp[0xffff];

	char tmpt[0xffff];
	char* pt = tmpt;
	tmp[0] = 0;
	tmpt[0] = 0;
	xsnode* p = start;
	int t = 0;
	while (t < num)
	{
		sprintf_s(tmp, "ID:%d  name:%s  grade:%d   --NEXT--               ", p->xh, p->xm, p->cj);
		for (int i = 0; tmp[i] != 0; i++)
		{
			*pt = tmp[i];
			pt++;
		}
		*pt = 0;
		t++;
		p++;
	}
	xinxi->setText(tmpt);
}

void dele()
{
	int i = 0;
	char xm[0xff];
	while (t2->getText()[i] != 0)
	{
		xm[i] = t2->getText()[i];
		i++;
	}
	xm[i] = 0;
	bool flag = false;
	for (i = 0; i < num; i++)
	{
		if (strcmp(start[i].xm, xm) == 0)
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		while (i+1 < num)
		{
			start[i] = start[i + 1];
			i++;
		}
		num--;
	}
}

void cbjg()
{
	char tmp[0xffff];

	char tmpt[0xffff];
	char* pt = tmpt;
	tmp[0] = 0;
	tmpt[0] = 0;
	xsnode* p = start;
	int t = 0;
	while (t < num)
	{
		if (p->cj<60)
		{
			sprintf_s(tmp, "ID:%d  name:%s  grade:%d   --NEXT--               ", p->xh, p->xm, p->cj);
			for (int i = 0; tmp[i] != 0; i++)
			{
				*pt = tmp[i];
				pt++;
			}
			*pt = 0;
		}
		t++;
		p++;
	}
	xinxi->setText(tmpt);
}

programnw::programnw() :itembox(1600, 900), imgArrWork(false), width(1600), height(900), imgArr(NULL)
{
	num = 0;

	

	ui_item_label* l1=new ui_item_label();
	l1->setPosition(20, 10);
	l1->setText(L"学号");
	l1->setSize(50, 16);
	//itembox.addItem(l1);

	ui_item_label* sss = new ui_item_label();
	sss->setPosition(600, 10);
	sss->setText(L"学号");
	sss->setSize(50, 16);
	//itembox.addItem(sss);

	ui_item_label* l2 = new ui_item_label();
	l2->setPosition(20, 30);
	l2->setText(L"姓名");
	l2->setSize(50, 16);
	//itembox.addItem(l2);

	ui_item_label* l3 = new ui_item_label();
	l3->setPosition(20, 50);
	l3->setText(L"成绩");
	l3->setSize(50, 16);
	//itembox.addItem(l3);

	t1 = new ui_item_textfield();
	t1->setPosition(100, 10);
	t1->setSize(160, 16);
	//itembox.addItem(t1);

	t2 = new ui_item_textfield();
	t2->setPosition(100, 30);
	t2->setSize(160, 16);
	//itembox.addItem(t2);

	t3 = new ui_item_textfield();
	t3->setPosition(100, 50);
	t3->setSize(160, 16);
	//itembox.addItem(t3);

	ui_item_button* add = new ui_item_button();
	add->setPosition(20, 80);
	add->setSize(80, 30);
	add->setText(L"添加");
	add->setEvent(addi);
	add->setVisible(true);
	itembox.addItem(add);

	ui_item_button* cx = new ui_item_button();
	cx->setPosition(20, 120);
	cx->setSize(160, 30);
	cx->setText(L"查询全部（刷新）");
	cx->setVisible(true);
	cx->setEvent(cxx);
	itembox.addItem(cx);

	ui_item_button* cxxh = new ui_item_button();
	cxxh->setPosition(190, 120);
	cxxh->setSize(160, 30);
	cxxh->setText(L"按照学号查询");
	cxxh->setEvent(cxxxh);
	//itembox.addItem(cxxh);

	ui_item_button* del = new ui_item_button();
	del->setPosition(360, 120);
	del->setSize(160, 30);
	del->setText(L"删除此学号");
	del->setEvent(dele);
	//itembox.addItem(del);

	ui_item_button* bjg = new ui_item_button();
	bjg->setPosition(530, 120);
	bjg->setSize(160, 30);
	bjg->setText(L"查询(不及格)");
	bjg->setEvent(cbjg);
	//itembox.addItem(bjg);

	xinxi = new ui_item_textfield();
	xinxi->setPosition(20, 160);
	xinxi->setSize(512, 360);
	xinxi->setVisible(true);
	itembox.addItem(xinxi);

	lr = new ui_item_linerecorder();
	lr->setSize(1200, 800);
	//lr->setSize(500, 200);
	lr->setPosition(600, 100);
	lr->start();
	lr->addRecordVar(&a);
	lr->addRecordVar(&b);
	lr->addRecordVar(&c);
	lr->addRecordVar(&d);
	lr->setClock(10);
	//itembox.addItem(lr);

	ui_item_window* waa = new ui_item_window();
	waa->setPosition(100, 100);
	waa->setSize(200, 200);
	waa->start();
	waa->setClock(10);
	//waa->setPlayer(lr);
	waa->setPlayer(&itembox);
	waa->setVisible(true);
	itembox.addItem(waa);
}
pixel* programnw::getOrginalImg()
{
	//itembox.fresh();
	return itembox.image;
}
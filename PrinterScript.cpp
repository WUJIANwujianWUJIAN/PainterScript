// PrinterScript.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<fstream>
#include <EasyX.h >
#include <conio.h >
#include <string.h >
#include <vector >
#include<queue>

using namespace std;

#define CMD_LEN 1200
#define TMP_LEN 300
std::wstring s2ws(const std::string& str)		//Unicode 2 UTF8
{
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);//CP_UTF8
	std::wstring w_str(wide);
	delete[] wide;
	return w_str;
}

std::string ws2s(const std::wstring &wstr)		//UTF8 2 Unicode
{
	std::string str;
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');
	int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);
	if (nResult == 0)
	{
		return "";
	}
	return str;
}

struct mRect
{

	int x=-1, y=-1, w=-1, h=-1;
	bool Isfill=false;
	vector<string> key ={ string("rectangle"), string("fillrectangle")};

	bool isReady()
	{
		if (x >=0 && y >= 0 && w >= 0 && h >= 0)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		if (sscanf_s(parameter.c_str(), "%d%d%d%d", &x, &y, &w, &h) != 4)
		{
			//cout << "XXX: " << x << "\tYYY: " << y << "\tWWW: " << w << "\tHHH: " << h << endl;
			x = y = w = h = -1;
			return;
		}
		//cout << "okXXX: " << x << "\tYYY: " << y << "\tWWW: " << w << "\tHHH: " << h << endl;
		if (key == 0)
		{
			Isfill = false;
		}
		else if (key == 1)
		{
			Isfill = true;
		}
	}
	int match(string cmd, string parameter)
	{
		//cout << "MMMMMMMMMMM" << endl;
		int i = 0;

		for (i = 0; i < key.size(); i++)
		{
			//cout << "I" << i << "MMMMMMMMMMMMMMMMMMMMMM" << key[i].c_str() << cmd.c_str() << endl;
			if (strcmp(key[i].c_str(), cmd.c_str())==0)
			{
				break;
			}
		}

		std::cout << i << endl;
		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	
	}
};


struct mEllipse
{
	
	int x=-1, y=-1, w=-1, h=-1;
	bool Isfill=false;
	vector<string> key = { string("ellipse"), string("fillellipse") };

	bool isReady()
	{
		if (x >=0 && y >=0 && w >=0 && h >=0)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		if(sscanf_s(parameter.c_str(), "%d%d%d%d", &x, &y, &w, &h) != 4)
		{
			x = y = w = h = -1;
			return;
		}
		if (key == 0)
		{
			Isfill = false;
		}
		else if (key == 1)
		{
			Isfill = true;
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str())==0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}

	}
};
struct mCircle
{

	int x = -1, y = -1, r = -1;
	bool Isfill = false;
	vector<string> key = { string("circle"), string("fillcircle") };
	bool isReady()
	{
		if (x != -1 && y != -1 && r != -1)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		if (sscanf_s(parameter.c_str(), "%d%d%d", &x, &y, &r) != 3)
		{
			x = y = r = -1;
			return;
		}
		if (key == 0)
		{
			Isfill = false;
		}
		else if (key == 1)
		{
			Isfill = true;
		}
	}
	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str())==0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};
struct mArc
{
	
	int x=-1, y=-1, w=-1, h=-1;
	double start=-1;
	double end=-1;
	bool Isfill;
	vector<string> key = { string("arc"), string("fillarc") };
	bool isReady()
	{
		if (x != -1 && y != -1 && w != -1 && h != -1 && start != -1 && end != -1)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		if(sscanf_s(parameter.c_str(), "%d%d%d%d%lf%lf", &x, &y, &w, &h, &start, &end) != 6)
		{
			
			x = y = w = h = start = end = -1;
			return;
		}
		start = start * 3.1415 / 180;
		end = end * 3.1415 / 180;
		if (key == 0)
		{
			Isfill = false;
		}
		else if (key == 1)
		{
			Isfill = true;
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str())==0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}

	}
};
struct mColor
{
	
	int r=-1, g=-1, b=-1;
	bool IsFront;
	vector<string> key = { string("foregroundcolor"), string("backgroundcolor") };
	bool isReady()
	{
		if (r != -1 && g != -1 && b != -1)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		if (sscanf_s(parameter.c_str(), "%d%d%d", &r, &g, &b) != 3)
		{
			r = g = b = -1;
			return;
		}
		if (key == 0)
		{
			IsFront = true;
		}
		else if (key == 1)
		{
			IsFront = false;
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str())==0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}

	}
};

struct mLine
{
	int x=-1, y=-1, ex=-1, ey=-1;
	vector<string> key = { string("line")};
	bool isReady()
	{
		if (x != -1 && y != -1 && ex != -1 && ey != -1)
		{
			return true;
		}
		return false;
	}
	
	void readparameter(int key, string parameter)
	{
		if (sscanf_s(parameter.c_str(), "%d%d%d%d", &x, &y, &ex, &ey) != 4)
		{
			x = y = ex = ey = -1;
			return;
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str())==0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};

//string 12 12 asdlfsdaf 0 0 adsfj 0 0 0 false false false
struct mString
{
	int x = -1, y = -1;
	string str = string(CMD_LEN, -1);
	int w = 0, h = 0;
	string typeface = string(200, -1);
	int rotateline = 0, rotatealpha = 0, weight = 0;
	int Italic = false, Underline = false, Strikeline = false;

	int n;
	vector<string> key = { string("string") };
	
	bool isReady()
	{
		if (x != -1 && y != -1)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{
		
		n = sscanf_s(parameter.c_str(), "%d%d%*c%[^#]%*c%d%d%[^#]%*c%d%d%d%d%d%d", &x, &y, str.c_str(), str.capacity(),&h, &w, typeface.c_str(), typeface.capacity(), &rotateline, &rotatealpha, &weight,&Italic,&Underline, &Strikeline);
		//cout << "NNNNNNNNNNNNNN:" << n << endl;
		//cout << "XXXX:" << x << endl;
		//cout << "YYYY:" << y << endl;
		//cout << "STRI:" << s2ws(str).c_str() << endl;
		//cout << "WWWW:" << w << endl;
		//cout << "HHHH:" << h << endl;
		switch (n)
		{
		case 0:
		case 1:
		case 2:x = y = -1;
		}

	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str()) == 0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};


//image x y path [width|0] [height|0] [1] [maskpath] [maskwidth|0] [maskheight|0]
struct mImage
{
	int x = -1, y = -1;
	string imgpath = string(CMD_LEN, -1);
	int w0 = -1, h0 = -1;

	int edge = true;
	//black edge: edge =true
	//white edge: dege = false;
	
	string maskpath = string(CMD_LEN, -1);
	int w1 = -1, h1 = -1;
	
	vector<string> key = { string("image") };
	int n;
	bool isReady()
	{
		if (x != -1 && y != -1 )
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{

		n = sscanf_s(parameter.c_str(), "%d%d%*c%[^#]%*c%d%d%d%*c%[^#]%*c%d%d",&x, &y, imgpath.c_str(), imgpath.capacity(), &w0, &h0, &edge, maskpath.c_str(), maskpath.capacity(), &w1, &h1);
		//cout << "NNNNNNNNNNNNNN:" << n << endl;
		//cout << "XXXX:" << x << endl;
		//cout << "YYYY:" << y << endl;
		//cout << "STRI:" << s2ws(str).c_str() << endl;
		//cout << "WWWW:" << w << endl;
		//cout << "HHHH:" << h << endl;
		switch (n)
		{
		case 0:
		case 1:
		case 2:
			x = y = -1;
		}

	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str()) == 0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};

//polygon	[x, y] [x, y] [x, y] [x, y]
//fillpolygon
struct mPolygon
{
	int pts[40] = {0};
	int n;
	int IsFill = false;

	vector<string> key = { string("polygon"), string("fillpolygon") };
	
	bool isReady()
	{
		if (n >= 6)
		{
			return true;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{

		n = sscanf_s(parameter.c_str(), "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", \
			&pts[0], &pts[1], &pts[2], &pts[3], &pts[4], &pts[5], &pts[6], &pts[7], &pts[8], &pts[9], \
			&pts[10], &pts[11], &pts[12], &pts[13], &pts[14], &pts[15], &pts[16], &pts[17], &pts[18], &pts[19], \
			&pts[20],&pts[21], &pts[22], &pts[23], &pts[24], &pts[25], &pts[26], &pts[27], &pts[28], &pts[29], \
			&pts[30], &pts[31], &pts[32], &pts[33], &pts[34], &pts[35], &pts[36], &pts[37], &pts[38], &pts[39]
		);

		if (key == 0)
		{
			IsFill = false;
		}
		else if (key == 1)
		{
			IsFill = true;
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str()) == 0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};

//resize x y
//clear
//output #
struct mSystem
{
	int w0 = -1, h0 = -1;
	string outpath = string(CMD_LEN, -1);
	int n = -1;
	int cmd = -1;	//cmd= 1 clear, cmd =2 output , cmd = 3 resize
	vector<string> key = { string("clear"), string("output"), string("resize") };

	bool isReady()
	{
		switch (cmd)
		{
		case 1:return true; break;
		case 2:if (n == 1)return true; break;
		case 3:if (n == 2)return true; break;
		}
		return false;
	}

	void readparameter(int key, string parameter)
	{	
		if (key == 0)
		{
			cmd = 1;	//clear
		}
		else if (key == 1)
		{
			cmd = 2;	//output
			n = sscanf_s(parameter.c_str(), "%*c%[^#]", outpath.c_str(), outpath.capacity());
		}
		else if (key == 2)
		{
			cmd = 3;	//resize
			n = sscanf_s(parameter.c_str(), "%d%d",  &w0, &h0);
		}
	}

	int match(string cmd, string parameter)
	{
		int i = 0;
		for (string a : key)
		{
			if (strcmp(a.c_str(), cmd.c_str()) == 0)
			{
				break;
			}
			i++;
		}

		if (i >= key.size())
			return -1;
		if (i >= 0)
		{
			readparameter(i, parameter);
		}
	}
};
int width = 640, height = 480;

queue<mRect> rec;				//rectangle
queue<mEllipse> ell;				//ellipse
queue<mCircle> cir;				//circle
queue<mArc> car;				//arc
queue<mColor> col;				//color
queue<mLine> lin;				//line
queue<mString> str;				//string
queue<mImage> img;				//image
queue<mPolygon> pol;			//polygon
queue<mSystem> sys;				//resize, clear, output

queue<int> order;

vector<string> key;


mRect REC = {0, 0, 100, 100, false};				//rectangle
mEllipse ELL = { 0, 0, 100, 100, false };				//ellipse
mCircle CIR = { 50, 50, 50, false};					//circle
mArc ARC = { 0, 0, 100, 100, 0, 2, false };				//arc
mColor COL = { 255, 255, 255 , true };					//color
mLine LIN = { 0, 0, 0, 0};										    //line
mString STR = {0, 0, "123", 0, 0, "", 0, 0, 0, 0};		//string
mImage IMG = {0, 0, "", 0, 0, 0, "", 0, 0};		//string
mPolygon POL;	//polygon
mSystem SYS;	//clear, output, resize

int main(int argc, char* argv[])
{
	
	char linestr[CMD_LEN];
	char templine[TMP_LEN];
	ifstream f1;
	if (argc == 1)
		f1.open("./PainterScript.ps", ios::in);
	else if(argc==2)
		f1.open(argv[1], ios::in);

	if (!f1)
	{
		fstream f2("./PainterScript.ps", ios::trunc | ios::out);
		std::cout << "./PainterScript.ps not exist!!!" << endl;
		system("pause");
		f2.close();
		
	}
	f1.close();
	
	if (argc == 1)
		f1.open("./PainterScript.ps", ios::in);
	else if (argc == 2)
		f1.open(argv[1], ios::in);
	if (!f1)
	{
		f1.close();
		
		std::cout << "some thing wrong !!!" << endl;
		system("pause");
		exit(0);
	}

	key.push_back(string("####"));
	key.push_back(string("width"));
	key.push_back(string("height"));
	for (string a : REC.key)
		key.push_back(a);
	for (string a : ELL.key)
		key.push_back(a);
	for (string a : CIR.key)
		key.push_back(a);
	for (string a : ARC.key)
		key.push_back(a);
	for (string a : COL.key)
		key.push_back(a);
	for (string a : LIN.key)
		key.push_back(a);
	for (string a : STR.key)
		key.push_back(a);
	for (string a : IMG.key)
		key.push_back(a);
	for (string a : POL.key)
		key.push_back(a);
	for (string a : SYS.key)
		key.push_back(a);
	
	//for (string x : key)cout << "OKOKOKKKKKKKOKK" << x.c_str() << endl;
	
	
	string t0(CMD_LEN,-1), t1(CMD_LEN,-1);
	//char line[100];
	
	mRect *mr = NULL;
	mEllipse *me = NULL;
	mCircle *mc = NULL;
	mArc *ma = NULL;
	mColor *mcol = NULL;
	mLine *mlin = NULL;
	mString *mstr = NULL;
	mImage *mimg = NULL;
	mPolygon *mpol = NULL;
	mSystem *msys = NULL;
	while (!f1.eof())
	{
		f1.getline(linestr, CMD_LEN);
		std::cout << "linestr:[" << linestr;
		std::cout << "]\tSTRLEN(linestr):" << strlen(linestr) << endl;
		if (strlen(linestr) == 0)
		{
			continue;
		}
		int dd;
		sscanf_s(linestr, "%[^ ]%[^\n]", t0.c_str(), t0.capacity(),t1.c_str(), t1.capacity());
		//t1 = t.substr(0, 4);
		//
		//t.at(0) = ' ';
		//t.at(1) = ' ';
		//t.at(2) = ' ';
		//t.at(3) = ' ';
		//int a, b, c;
		//sscanf_s(t.c_str(), " %d", &a);

		//cout << t1.c_str() << ">>>>>>>>>>>>>" << t.c_str() <<">>>>>>>>>>>>>"<< a << endl;
		int i = 0;
		
		std::cout << "CMD T0:[" <<t0.c_str()<<"]\tCMD T1:  "<<t1.c_str()<< endl;
		for (i=0;i<key.size();i++)
		{
			std::cout << "KKKKKKKKKKKKKKKKK" << i << key[i].c_str()<<"["<< t0.c_str()<<"]"<< strcmp(key[i].c_str(), t0.c_str()) << endl;
			if (strcmp(key[i].c_str(), t0.c_str()) == 0)
			{
				std::cout << i << endl;
				switch (i)
				{
					case 0: break;	//####
					case 1:/*sscanf_s(t1.c_str(), "%d", &width); */break;
					case 2:/*sscanf_s(t1.c_str(), "%d", &height);*/ break;
					case 3:
					case 4:
						if (mr == NULL) {
							mr = new mRect();
						}
						mr->match(t0, t1);
						if (mr->isReady())
						{
							std::cout << "push a rectangle" << endl;
							rec.push(*mr);
							order.push(1);
							mr = NULL;
						}
						break;
					case 5:
					case 6:
						if (me == NULL) {
							me = new mEllipse();
						}
						me->match(t0, t1);
						if (me->isReady())
						{
							std::cout << "push a ellipse" << endl;
							ell.push(*me);
							order.push(2);
							me = NULL;
						}
						break;
					case 7:
					case 8:
						if (mc == NULL) {
							mc = new mCircle();
						}
						mc->match(t0, t1);
						if (mc->isReady())
						{
							std::cout << "push a circle" << endl;
							cir.push(*mc);
							order.push(3);
							mc = NULL;
						}
						break;
					case 9:
					case 10:
						if (ma == NULL) {
							ma = new mArc();
						}
						ma->match(t0, t1);
						if (ma->isReady())
						{
							std::cout << "push a arc" << endl;
							car.push(*ma);
							order.push(4);
							ma = NULL;
						}
						break;
					case 11:
					case 12:
						if (mcol == NULL) {
							mcol = new mColor();
						}
						std::cout << "CCCCCCCCCCCCCCCCccolor" << endl;
						mcol->match(t0, t1);
						if (mcol->isReady())
						{
							std::cout << "push a color" << endl;
							col.push(*mcol);
							order.push(5);
							mcol = NULL;
						}
						break;
					case 13:
						if (mlin == NULL) {
							mlin = new mLine();
						}
						mlin->match(t0, t1);
						if (mlin->isReady())
						{
							std::cout << "push a line" << endl;
							lin.push(*mlin);
							order.push(6);
							mlin = NULL;
						}
						break;
					case 14:
						if (mstr == NULL) {
							mstr = new mString();
						}
						mstr->match(t0, t1);
						if (mstr->isReady())
						{
							std::cout << "push a string" << endl;
							str.push(*mstr);
							order.push(7);
							mstr = NULL;
						}
						break;
					case 15:
						
						if (mimg == NULL) {
							mimg = new mImage();
						}
						mimg->match(t0, t1);
						if (mimg->isReady())
						{
							std::cout << "push a image" << endl;
							img.push(*mimg);
							order.push(8);
							mimg = NULL;
						}
						break;
					case 16:
					case 17:
						if (mpol == NULL) {
							mpol = new mPolygon();
						}
						mpol->match(t0, t1);
						if (mpol->isReady())
						{
							std::cout << "push a polygon" << endl;
							pol.push(*mpol);
							order.push(9);
							mpol = NULL;
						}
						break;
					case 18:
					case 19:
					case 20:
						if (msys == NULL) {
							msys = new mSystem();
						}
						msys->match(t0, t1);
						if (msys->isReady())
						{
							std::cout << "push a polygon" << endl;
							sys.push(*msys);
							order.push(10);
							msys = NULL;
						}
						break;
				}
				break;
			}//if
		}//for
	}

	initgraph(width, height); // 创建绘图窗口，大小为 640x480 像素
	///Resize(NULL, 400, 400);
	setbkmode(TRANSPARENT);		//OPAQUE  TRANSPARENT
	
	
	/*setlinecolor(RGB(255, 255, 255));
	setfillcolor(RGB(255,255,  255));
	settextcolor(RGB(255, 255, 255));
	setbkcolor(RGB(0, 0, 0));

	setlinecolor(RGB(255, 0, 0));
	setfillcolor(RGB(255, 0, 0));
	settextcolor(RGB(255, 0, 0));*/

	//circle(100, 100, 50);
	//fillcircle(200, 200, 50);

	//rectangle(300, 300, 400, 400);
	//fillrectangle(300, 100, 400, 200);


	//string s = "This is a test";
	//outtext((LPCTSTR)s.c_str());
	//saveimage(_T("C:/Users/wujian/Desktop/test.jpg"));
	
	
	
	//cout << "ok" << endl;

	int i;
	while (!order.empty())
	{
		i = order.front(); order.pop();
		std::cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIII" << i << endl;
		if (i == 1)		//rec
		{
			mRect m = rec.front(); rec.pop();
			if (m.isReady()) //m.isReady()
			{
				if (m.Isfill)
				{
					fillrectangle(m.x, m.y, m.x + m.w, m.y + m.h);
				}
				else
				{
					rectangle(m.x, m.y, m.x + m.w, m.y + m.h);
				}
			}
		}
		else if (i == 2)	//ell
		{
			mEllipse m = ell.front(); ell.pop();
			if (m.isReady())
			{
				if (m.Isfill)
				{
					fillellipse(m.x, m.y, m.x + m.w, m.y + m.h);
				}
				else
				{
					ellipse(m.x, m.y, m.x + m.w, m.y + m.h);
				}

			}
		}
		else if (i == 3)	//cir
		{
			mCircle m = cir.front(); cir.pop();
			if (m.isReady())
			{
				if (m.Isfill)
				{
					fillcircle(m.x, m.y, m.r);
				}
				else
				{
					circle(m.x, m.y, m.r);
				}

			}
		}
		else if (i == 4)	//arc
		{
			mArc m = car.front(); car.pop();
			if (m.isReady())
			{
				if (m.Isfill)
				{
					fillpie(m.x, m.y, m.x + m.w, m.y + m.h, m.start, m.end);
				}
				else
				{
					arc(m.x, m.y, m.x + m.w, m.y + m.h, m.start, m.end);
					//pie(m.x, m.y, m.x + m.w, m.y + m.h, m.start, m.end);
				}

			}
		}
		else if (i == 5)	//col
		{
			mColor m = col.front(); col.pop();
			if (m.isReady())
			{
				if (m.IsFront)
				{
					setlinecolor(RGB(m.r, m.g, m.b));
					setfillcolor(RGB(m.r, m.g, m.b));
					settextcolor(RGB(m.r, m.g, m.b));
					//cout << "CCCCCCCCCCC" << endl;
				}
				else
				{
					setbkcolor(RGB(m.r, m.g, m.b));
					//cout << "CCCCCCCCCCC" << endl;
				}
			}
		}
		else if (i == 6)	//line
		{
			mLine m = lin.front(); lin.pop();
			if (m.isReady())
			{
				line(m.x, m.y, m.ex, m.ey);
			}
		}
		else if (i == 7)	//string
		{
			mString m = str.front(); str.pop();
			if (m.isReady())
			{	//s2ws(m.typeface).c_str()
				setbkmode(TRANSPARENT);
				settextstyle(m.h, m.w, s2ws(m.typeface).c_str(), m.rotateline, m.rotatealpha, m.weight, m.Italic, m.Underline, m.Strikeline);

				wstring ss = s2ws(m.str);
				outtextxy(m.x, m.y, ss.c_str());//wstr.c_str());//
			}
		}
		else if (i == 8)
		{
			mImage m = img.front(); img.pop();
			IMAGE srcimage, maskimage;
			if (m.isReady())
			{	//s2ws(m.typeface).c_str()
				setbkmode(TRANSPARENT);
				
				std::cout <<"GGGGGGGG" <<m.imgpath.c_str() << endl;
				loadimage(&srcimage, s2ws(m.imgpath).c_str(), m.w0, m.h0, true);//, m.w0, m.h0, true
				//loadimage(&srcimage, s2ws(m.imgpath).c_str(), 0, 0, true);//, m.w0, m.h0, true
				if(m.n>=6)
					loadimage(&maskimage, s2ws(m.maskpath).c_str(), m.w1, m.h1, true);//, m.w1, m.h1, true
					//loadimage(&maskimage, L"C:\\Users\\wujian\\Desktop\\mask.gif");//, m.w1, m.h1, true
				
				if (m.edge == 1)//原图白边， 掩码黑边
				{
					putimage(m.x, m.y, &maskimage, NOTSRCERASE);
					putimage(m.x, m.y, &srcimage, SRCINVERT);
				}
				else if (m.edge == 0)//原图黑边， 掩码白边
				{
					putimage(m.x, m.y, &maskimage, SRCAND);
					putimage(m.x, m.y, &srcimage, SRCPAINT);
				}
			}
		}
		else if (i == 9)
		{
			mPolygon m = pol.front(); pol.pop();
			if (m.isReady())
			{
				if (m.IsFill)
				{
					fillpolygon((POINT*)m.pts, m.n/2);
				}
				else
				{
					polygon((POINT*)m.pts, m.n / 2);
				}
			}
		}
		else if (i == 10)
		{
			mSystem m = sys.front(); sys.pop();
			if (m.isReady())
			{
				if (m.cmd == 1)
				{
					cleardevice();
				}
				else if(m.cmd == 2)
				{
					saveimage(s2ws(m.outpath).c_str());
				}
				else if (m.cmd == 3)
				{
					//MessageBox(NULL, L"", L"", MB_OK);
					Resize(NULL, m.w0, m.h0);
				}
			}
		}
		//if elif elif
	}//while(!order.empty)

	//getchar();
	//saveimage( s2ws(path.c_str()).c_str() );
	//saveimage(L"C:/Users/wujian/Desktop/test.jpg");
	//std::cout << path.c_str();
	//getchar();
	closegraph(); // 关闭绘图窗口
	f1.close();
}
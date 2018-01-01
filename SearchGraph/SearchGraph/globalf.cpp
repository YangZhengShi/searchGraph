#include "stdafx.h"
#include "globalf.h"
RECT tmp = { 0, 0, 100, 100 };
MyView* mv = new MyView(ROW, COL, tmp);
std::vector<Point*> vpoint(ROW*COL);
long g_rgb = 0x00ffff00;
RECT region;
Graph<Point> *graph = new Graph<Point>;



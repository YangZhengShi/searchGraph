#ifndef GLOBAL_H
#define GLOBAL_H
#include "POINT.h"
#include "Graph.h"

#include "MyView.h"


#define ROW 30
#define COL 40
//extern std::function<void(int, int, long)> show;
extern MyView* mv;
extern long g_rgb;
class Point;
extern std::vector<Point*> vpoint;
extern RECT region;
extern Graph<Point> *graph;


#endif

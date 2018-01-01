#ifndef POINT_H
#define POINT_H
#include <list>
#include <vector>

enum VertexColor
{
	COLOR_RED = 0x000000ff,
	COLOR_GREEN = 0x0000ff00,
	COLOR_BLUE = 0x00ff0000,
	COLOR_GRAY = 0x00c8c8c8,
	COLOR_WHITE = 0x00ffffff,
	COLOR_BLACK = 0x00000000,

};
class Point
{
public:
	int x, y;
	long color;
	double d;
	Point *parent;

	Point(int x, int y);
	~Point();
	bool operator == (Point& p2);
	int IsAdj(Point *point);
};

#endif



#include "stdafx.h"
#include "POINT.h"
//std::function<void(int, int, long)> show = NULL;


Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
	d = 0;
	color = COLOR_WHITE;
	parent = NULL;
}
bool Point::operator == (Point& p)
{
	return ((p.x == x) && (p.y == y));
}

int Point::IsAdj(Point *point)
{
	if (-1 <= point->x - x && 1 >= point->x - x && -1 <= point->y - y && 1 >= point->y - y)
	{
		if (!(*point == *this))
		{
			return (point->x - x)*(point->x - x) + (point->y - y)*(point->y - y);
		}
	}

	return false;
}
Point::~Point()
{
	//mv->FillColor(x, y, g_rgb--);
}

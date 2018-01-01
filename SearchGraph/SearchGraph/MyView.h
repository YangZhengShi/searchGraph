#ifndef MYVIEW_H
#define MYVIEW_H
#include <windef.h>
class MyView
{
private:
	int _row, _col;
	double _stepx, _stepy;	
	
public:
	RECT _rect;
	HDC _hdc;
	HWND _hwnd;
	MyView(int row, int col, RECT& rect);
	~MyView();
	void DrawBack();
	void ReSetSize(RECT& rect);
	void FillColor(int xindex, int yindex, long rgb, double weight);
	void SetDC(HWND hwnd);
};
#endif

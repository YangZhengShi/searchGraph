#include "stdafx.h"
#include "MyView.h"
#include <stdio.h>


MyView::MyView(int row, int col, RECT& rect)
{
	_row = row;
	_col = col;
	ReSetSize(rect);
	_hdc = NULL;

}
void MyView::SetDC(HWND hwnd)
{
	_hwnd = hwnd;
	HDC hdc = GetDC(hwnd);
	if (hdc)
	{
		_hdc = CreateCompatibleDC(hdc);
		HBITMAP hbmp= CreateCompatibleBitmap(hdc, _rect.right - _rect.left, _rect.bottom - _rect.top);
		SelectObject(_hdc, hbmp);
		DeleteObject(hbmp);
		BitBlt(_hdc, 0, 0, _rect.right - _rect.left, _rect.bottom - _rect.top, _hdc, 0, 0, DSTINVERT);

	}
}
MyView::~MyView()
{
}
void MyView::DrawBack()
{
	if (_hdc)
	{
		for (size_t i = 0; i <= _row; i++)
		{
			MoveToEx(_hdc, _rect.left, i*_stepy, NULL);
			LineTo(_hdc, _rect.right, i*_stepy);
		}
		for (size_t i = 0; i <= _col; i++)
		{
			MoveToEx(_hdc, _rect.left + i*_stepx, _rect.top, NULL);
			LineTo(_hdc, _rect.left + i*_stepx, _rect.bottom);
		}
	}

}
void MyView::ReSetSize(RECT& rect)
{
	_rect = rect;
	if (_col)
	{
		_stepx = (double)(_rect.right - _rect.left) / _col;
	}
	if (_row)
	{
		_stepy = (double)(_rect.bottom - _rect.top) / _row;
	}
}
void MyView::FillColor(int xindex, int yindex, long rgb, double weight)
{
	char text[1000] = { 0 };
	if (_hdc)
	{
		RECT tmpRect;
		tmpRect.left = _rect.left + yindex*_stepx;
		tmpRect.top = _rect.top + xindex*_stepy;

		tmpRect.right = tmpRect.left + _stepx;
		tmpRect.bottom = tmpRect.top + _stepy;

		HBRUSH hbrush = CreateSolidBrush(rgb);
		::FillRect(_hdc, &tmpRect, hbrush);

		sprintf_s(text, "%1.3f", weight);
		TextOutA(_hdc, tmpRect.left, tmpRect.top, text, 4);

		::DeleteObject(hbrush);

	}

}
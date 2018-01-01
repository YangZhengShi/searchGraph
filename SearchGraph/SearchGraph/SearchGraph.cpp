// SearchGraph.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SearchGraph.h"
#include "MyView.h"
#include "Graph.h"
#include "POINT.h"
#include <functional>
#include <thread>
#include "globalf.h"

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

std::queue<AdjList<Point> *> myq;
AdjList<Point> *clr_adjlist;
AdjList<Point> *adjlist;
Point *clr_vertex, *adj_vertex;


int tick = 0;
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SEARCHGRAPH, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEARCHGRAPH));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEARCHGRAPH));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SEARCHGRAPH);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	Point * mpoint;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			mpoint = new Point(i, j);
			vpoint[i * COL + j]=(mpoint);
			//if ( i > 0 && j == 20)
			//{
			//	continue;
			//}
			graph->ins_vertex(mpoint);			
		}
	}
	double weight = 0;
	int index = 0;
	double aweight[] = {1, 1.4142135};
	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end();it++)
	{
		for (auto it1 = graph->_adjlist.begin(); it1 != graph->_adjlist.end(); it1++)
		{
			if (index=((*it)->vertex->IsAdj((*it1)->vertex)))
			{
				graph->ins_edge((*it)->vertex, (*it1)->vertex, aweight[index-1]);
			}
		}
	}


	//for (auto i = (graph->_adjlist).begin(); i != (graph->_adjlist).end(); i++)
	//{
	//	if (*((*i)->vertex) == Point(0, 0))
	//	{
	//		(*i)->vertex->color = COLOR_GRAY;
	//	}
	//	else
	//	{
	//		(*i)->vertex->color = COLOR_WHITE;
	//	}
	//}

	graph->adjlist(&Point(0, 0), &clr_adjlist);
	//将起始点的邻接表入队
	myq.push(clr_adjlist);

	SetTimer(hWnd, 0, 100, NULL);
	//show = std::bind(&MyView::FillColor,
	// *mv,
	// std::placeholders::_1,
	// std::placeholders::_2,
	// std::placeholders::_3);
	RECT tmp = { 0, 0, ::GetSystemMetrics(0), ::GetSystemMetrics(1) };
	mv->ReSetSize(tmp);
	mv->SetDC(hWnd);
   //mv->FillColor(tick, tick, 0x000000ff);
   mv->DrawBack();
   std::list<Point*> path;
   Point start(15, 0);
   Point end(29, 39);
   //auto f = shorttest<Point>;
   auto f = DFS<Point>;
   std::thread th(f, graph, vpoint[0]);
   th.detach();



   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		//if (myq.size())
		//{
		//	adjlist = myq.front();
		//	myq.pop();
		//	for (auto i = adjlist->adjacent->begin(); i != adjlist->adjacent->end(); i++)
		//	{
		//		adj_vertex = (*i);
		//		if (adj_vertex->color == COLOR_WHITE)
		//		{
		//			adj_vertex->color = COLOR_GRAY;
		//			graph->adjlist(adj_vertex, &clr_adjlist);
		//			myq.push(clr_adjlist);
		//		}
		//	}

		//}
		for (auto i = (graph->_adjlist).begin(); i != (graph->_adjlist).end(); i++)
		{
			mv->FillColor((*i)->vertex->x, (*i)->vertex->y, (*i)->vertex->color,
				(*i)->vertex->d);
		}
		mv->DrawBack();
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		GetClientRect(hWnd, &region);
		StretchBlt(hdc, 0, 0, region.right-region.left, region.bottom-region.top,
			mv->_hdc, 0,0,mv->_rect.right-mv->_rect.left,
			mv->_rect.bottom - mv->_rect.top,SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		delete mv;
		for (auto i = vpoint.begin(); i != vpoint.end(); i++)
		{
			delete *i;
		}
		vpoint.clear();
		delete graph;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

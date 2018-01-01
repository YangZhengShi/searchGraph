#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <queue>
#include <set>
#include <thread>
#include <chrono>

//#include "globalf.h"
#define white 0x00ffffffL
#define black 0x00000000L
#define green 0x0000ff00L
#define red 0x000000ffL
//const unsigned int MDBL_MAX = -1;

template <typename T>
struct AdjList
{
	typedef std::pair<T*, double> ele;
	AdjList(T *vertex_){ vertex = vertex_; adjacent = new std::list<ele>; }
	AdjList(AdjList<T> &adjlist)
	{
		if (adjacent)
		{
			adjacent.clear();
		}
		else
		{
			adjacent = new std::list<T*>
		}
		for (auto i = adjlist.adjacent.bengin(); i != adjlist.adjacent.end(); i++)
		{
			adjacent.push_back(*i);
		}
	}
	~AdjList()
	{
		delete adjacent;
	}
	T *vertex;
	std::list<ele> *adjacent;

};
template <typename T>
class Graph
{

private:
	
	
public:
	std::list <AdjList<T>*> _adjlist;
	int _ecount;
	int _vcount;

	Graph()
	{
		_vcount = 0;
		_ecount = 0;
	};
	Graph(Graph<T> &graph)
	{
		_vcount = graph._vcount;
		_ecount = graph._ecount;
		for (auto i = graph._adjlist.begin(); i != graph._adjlist.end(); i++)
		{
			_adjlist.push_back(*i);
		}
	};

	~Graph()
	{
		_adjlist.clear();
	};
	int ins_vertex(T *data)
	{
		AdjList<T> *adjlist;
		int retval = 0;
		for (auto it = _adjlist.begin(); it != _adjlist.end(); it++)
		{
			if (*((*it)->vertex) == *data)
			{
				return 1;
			}
		}
		adjlist = new AdjList<T>(data);
		_adjlist.push_back(adjlist);
		++_vcount;

		return retval;
	};

	int ins_edge(T *data1, T *data2, double weight)
	{
		int retval;
		auto it = _adjlist.begin();
		for (; it != _adjlist.end(); it++)
		{
			if (*((*it)->vertex) == *data2)
			{
				break;
			}
		}
		if (it == _adjlist.end())
		{
			return -1;
		}

		for (it = _adjlist.begin(); it != _adjlist.end(); it++)
		{
			if (*((*it)->vertex) == *data1)
			{
				break;
			}
		}
		if (it == _adjlist.end())
		{
			return -1;
		}
		(*it)->adjacent->push_back(std::make_pair(data2,weight));
		_ecount++;
		return 0;
	};
	//template<typename T>
	//int Graph<T>::rem_vertex(T *data)
	//{
	//	T *element, *temp, *prev=NULL;
	//	AdjList *adllist;
	//	int found = 0;
	//	auto it = _adjlist.begin();
	//	for (; it != _adjlist.end(); it++)
	//	{
	//		it->adjacent->find();
	//	}
	//}

	int adjlist(T *data, AdjList<T> **oadjlist)
	{
		auto it = _adjlist.begin();
			for (; it != _adjlist.end(); it++)
			{
				if (*((*it)->vertex) == *data)
				{
					break;
				}
			}
		if (it == _adjlist.end())
		{
			return -1;
		}
		*oadjlist = *it;
		return 0;
	};
};


template<typename T>
int bfs(Graph<T> *graph, T *start)
{
	//将起始点涂成灰色
	for (auto i = (graph->_adjlist).begin(); i != (graph->_adjlist).end(); i++)
	{
		if (*((*i)->vertex)==*start)
		{
			(*i)->vertex->color = COLOR_GRAY;
		}
		else
		{
			(*i)->vertex->color = COLOR_RED;
		}
	}
	std::queue<AdjList<T> *> myq;
	AdjList<T> *clr_adjlist;
	AdjList<T> *adjlist;
	T *clr_vertex,*adj_vertex;
	graph->adjlist(start, &clr_adjlist);
	//将起始点的邻接表入队
	myq.push(clr_adjlist);
	while (myq.size() > 0)
	{
		adjlist = myq.front();
		myq.pop();

		for (auto i = adjlist->adjacent->begin(); i != adjlist->adjacent->end(); i++)
		{
			adj_vertex = (*i);
			if (adj_vertex->color == COLOR_RED)
			{
				graph->adjlist(adj_vertex, &clr_adjlist);
				myq.push(clr_adjlist);
			}
		}
	}
	return 0;
};
template <typename T>
void relax(T *u, T *v, double weight)
{
	if (v->d > u->d + weight)
	{
		v->d = u->d + weight;
		v->parent = u;
	}
}
template <class T>
struct opless
{
	bool operator()(AdjList<T> *v1, AdjList<T> *v2)
	{
		return v1->vertex->d < v2->vertex->d;
	}
};
template <typename T>
int shorttest(Graph<T> *graph, T *start, T* end)
{
	T *path_vertex;
	int found = 0;
	T *pT= NULL;
	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
	{
		path_vertex = (*it)->vertex;
		if (*path_vertex == *start)
		{
			path_vertex->color = white;
			path_vertex->d = 0;
			path_vertex->parent = NULL;
			found = 1;
		}
		else if (*path_vertex == *end)
		{
			pT = path_vertex;
			path_vertex->color = white;
			path_vertex->d = DBL_MAX;
			path_vertex->parent = NULL;
		}
		else
		{
			path_vertex->color = white;
			path_vertex->d = DBL_MAX;
			path_vertex->parent = NULL;
		}
	}
	if (!found)
	{
		return -1;
	}
	//std::multiset<AdjList<T>*, opless<T>> Q;
	std::list<AdjList<T>*> Q;
	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
	{
		Q.push_back(*it);
	}
	while (!Q.empty())
	{
		Q.sort(opless<T>());
		auto it_mmin = Q.begin();
		AdjList<T> * elemin= *it_mmin;
		for (auto it1 = elemin->adjacent->begin(); it1 != elemin->adjacent->end(); it1++)
		{
			it1->first->color = green;
			relax(elemin->vertex, it1->first, it1->second);
			//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		Q.erase(it_mmin);
	}
	
	while (pT)
	{
		pT->color = red;
		pT = pT->parent;
	}
}
template <typename T>
void DFS(Graph<T> *graph, T *start)
{
	for (auto v : graph->_adjlist)
	{
		v->vertex->color = white;
	}
	DFS_VISIT(graph, start);
}
template <typename T>
void DFS_VISIT(Graph<T> *graph, T* vertex)
{

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	vertex->color = green;
	AdjList<T> *adjlist;
	graph->adjlist(vertex, &adjlist);
	for (auto vertex : *(adjlist->adjacent))
	{
		if (white == (vertex.first)->color)
		{
			DFS_VISIT(graph, vertex.first);
		}

	}


}
#endif


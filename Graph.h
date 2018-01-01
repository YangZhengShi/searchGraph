#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <queue>
#include <map>
#include <thread>
#include <chrono>

//#include "globalf.h"
#define white 0x00ffffffL
#define black 0x00000000L
#define green 0x0000ff00L
#define red 0x00ff0000L
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
template <typename T>
int shorttest(Graph<T> *graph, T *start, T* end)
{
	T *path_vertex;
	int found = 0;
	double min_d = 0;
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
	std::multimap<double, AdjList<T> *> Q;
	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
	{
		Q.insert(std::make_pair((*it)->vertex->d, *it));
	}
	while (!Q.empty())
	{
		typedef std::multimap<double, AdjList<T> *>::iterator MDA;
		auto min = Q.begin();
		min_d = min->first;
		typedef std::pair<MDA, MDA> range;
		range mrange = Q.equal_range(min_d);
		//std::list<std::pair<T*, double>>::iterator it2 = nullptr;
		for (auto it1 = mrange.first; it1 != mrange.second; it1++)
		{
			for (auto it2 = it1->second->adjacent->begin(); it2 != (it1->second->adjacent)->end(); it2++)
			{
				it1->second->vertex->color = green;
				relax(it1->second->vertex, it2->first, it2->second);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				
			}
			
		}
		Q.erase(min_d);
	}

}
//template <typename T>
//int shorttest(Graph<T> *graph, T *start, T* end)
//{
//	AdjList<T> *adjlist = NULL;
//	T *path_vertex, *adj_vertex;
//	double minimum;
//	int found = 0;
//	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
//	{
//		path_vertex = (*it)->vertex;
//		if (*path_vertex == *start)
//		{
//			path_vertex->color = white;
//			path_vertex->d = 0;
//			path_vertex->parent = NULL;
//			found = 1;
//		}
//		else
//		{
//			path_vertex->color = white;
//			path_vertex->d = DBL_MAX;
//			path_vertex->parent = NULL;
//		}
//	}
//	if (!found)
//	{
//		return -1;
//	}
//	int i = 0;
//	while (i < graph->_vcount)
//	{
//		/*Select the white vertex with the smallest shortest-path estimate*/
//		minimum = DBL_MAX;
//		for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
//		{
//			path_vertex = (*it)->vertex;
//			if (path_vertex->color == white && path_vertex->d < minimum)
//			{
//				minimum = path_vertex->d;
//				adjlist = (*it);
//			}
//		}
//		adjlist->vertex->color = green;
//		for (auto it = adjlist->adjacent->begin(); it != adjlist->adjacent->end(); it++)
//		{
//			adj_vertex = *it;
//			for (auto it1 = graph->_adjlist.begin(); it1 != graph->_adjlist.end(); it1++)
//			{
//				path_vertex = (*it1)->vertex;
//				if (*path_vertex==*adj_vertex)
//				{
//					relax(adjlist->vertex, path_vertex, adj_vertex->weight);
//				}
//			}
//		}
//		i++;
//	}
//	T * tmp = NULL;
//	for (auto it = graph->_adjlist.begin(); it != graph->_adjlist.end(); it++)
//	{
//		if (*end == *((*it)->vertex))
//		{
//			tmp = (*it)->vertex;
//		}
//	}
//	while (0==(*tmp==*start))
//	{
//		tmp->color = red;
//		tmp = tmp->parent;
//	}
//	return 0;
//}

#endif


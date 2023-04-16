#pragma once
#ifndef GROUPH_H
#define GROUPH_H
#include<iostream>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<climits>
#include<cmath>
#include<format>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include "setGraph.h"
using namespace std;

//邻接表法
template<typename T>
class nodeTable;
template<typename T>
class edgeTable;

template<typename T>
class nodeTable
{
public:
	T value;
	int in;
	int out;
	vector<nodeTable<T>*> nexts;
	vector<edgeTable<T>*> edges;
	nodeTable(int in = 0, int out = 0, T value = 0)
	{
		this->value = value;
		this->in = in;
		this->out = out;
	}
	nodeTable(int val) :value(val) {}
	nodeTable* operator=(const nodeTable<T>& node)
	{
	
		this->value = node.value;
		this->in = node.in;
		this->out = node.out;
		this->nexts = node.nexts;
		this->edges = node.edges;
		
		return this;
	}
	bool operator==(const nodeTable<T>& node)
	{
		return this == &node;
	}
};
template<typename T>
class edgeTable
{
public:
	int weight;
	nodeTable<T>* from;
	nodeTable<T>* to;
	edgeTable(int weight, nodeTable<T> *from, nodeTable<T> *to)
	{
		this->weight = weight;
		this->from = from;
		this->to = to;
	}
};
template<typename T>
class Compare_Edge_Max
{
public:
	bool operator()(const edgeTable<T>* e1, const edgeTable<T>* e2)const
	{
		return e1->weight < e2->weight;
	}
};
template<typename T>
class Compare_Edge_Min
{
public:
	bool operator()(const edgeTable<T>* e1, const edgeTable<T>* e2)const
	{
		return e1->weight > e2->weight;
	}
};
template<typename T>
class Compare_Node
{
public:
	bool operator()(const nodeTable<T>* n1, const nodeTable<T>* n2)const
	{
		return n1->value < n2->value;
	}
};
template<typename T>
class graphTable
{
public:
	map<int, nodeTable<T>*>nodes;
	set<edgeTable<T>*>edges;
};

template<typename T>
class Graph
{
public:
	bool Adjacent(const graphTable<T>& gt, const int from, const int to);
	vector<vector<edgeTable<T>*>> Neighbors(const graphTable<T>& gt, const nodeTable<T>& node);
	bool InsertNode(graphTable<T>& gt, T x);
	bool DeleteNode(graphTable<T>& gt, nodeTable<T>& node);
	bool AddEdge(graphTable<T>& gt, int f, int t, int weight);
	bool RemoveEdge(graphTable<T>& gt, int f, int t);
	nodeTable<T>* ReturnFistNode(graphTable<T>& gt, int x);
	nodeTable<T>* ReturnNextNode(graphTable<T>& gt, int x);
	void SetEdgeValue(graphTable<T>& gt, int f, int t, int v);
	int  GetEdgeValue(graphTable<T>& gt, int f, int t);
	void bfs(nodeTable<T>* node);
	void dfs(nodeTable<T>* node);
	int transformArraysDirected(graphTable<T>& gt, vector<vector<int>> arrays);
	int transformArraysUndirected(graphTable<T>& gt, vector<vector<int>> arrays);
	vector<nodeTable<T>*> sortedToplogy(graphTable<T>& gt);
	bool sortedToplogyForCritical(graphTable<T>& gt,stack<nodeTable<T>*>&s,vector<int> &etv);//为关键路径准备的拓扑排序 返回etv
	bool CriticalPath(graphTable<T>& gt);
	set<edgeTable<T>*, Compare_Edge_Max<T>> primMST(graphTable<T>& gt);
	Graph(graphTable<T>& g):gt(g) {};

private:
	graphTable<T> gt;
};


//邻接矩阵法
template<typename T>
bool Graph<T>::Adjacent(const graphTable<T>& gt, const int from, const int to)
{
	const auto& r1 = gt.nodes.find(from);
	const auto& r2 = gt.nodes.find(to);
	if (r1 != gt.nodes.end() && r2 != gt.nodes.end())
	{
		if (r1->second->edges.size() == 0 && r1->second->nexts.size() == 0)
			return false;

		for (const auto& edge : r1->second->edges)
		{
			if (edge->to == r2->second)
			{
				cout << format("存在边{}到{}", edge->from->value, edge->to->value) << endl;
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
	return true;
}
template<typename T>
vector<std::vector<edgeTable<T>*>> Graph<T>::Neighbors(const graphTable<T>& gt, const nodeTable<T>& node)
{
	vector<edgeTable<T>*> fromto;
	vector<edgeTable<T>*> tofrom;
	vector<vector<edgeTable<T>*>> res;

	if (&node == nullptr)
	{
		cout << "节点为空" << endl;
		return false;
	}
	for (const auto& edge : gt.edges)
	{
		if (edge->from == &node)
		{
			cout << format("存在边{}到{}", edge->from->value, edge->to->value) << endl;
			fromto.push_back(edge);
		}
		if (edge->to == &node)
		{
			cout << format("存在边{}到{}", edge->from->value, edge->to->value) << endl;
			tofrom.push_back(edge);
		}
	}
	res.push_back(fromto);
	res.push_back(tofrom);
	return res;
}
template<typename T>
bool Graph<T>::InsertNode(graphTable<T>& gt, T x)
{
	nodeTable<T>* node = new nodeTable<T>(0, 0, x);
	gt.nodes.emplace(node->value, node);
	if (node != nullptr)
		return true;
	return false;
}
template<typename T>
bool Graph<T>::DeleteNode(graphTable<T>& gt, nodeTable<T>& node)
{
	if (&node == nullptr)
		return true;
	auto&& neighbors = Neighbors(gt, node);

	if (node.in != 0)
	{
		for (auto& edge : neighbors[1])
		{
			(edge->from->out)--;
			gt.edges.erase(edge);
			edge = nullptr;
			delete edge;
		}
	}
	if (node.out != 0)
	{
		for (auto& edge : neighbors[0])
		{
			(edge->to->in)--;
			edge = nullptr;
			gt.edges.erase(edge);
			delete edge;
		}
	}
}
template<typename T>
bool Graph<T>::AddEdge(graphTable<T>& gt, int f, int t, int weight)
{
	bool isIn = Adjacent(gt, f, t);
	auto& from = gt.nodes[f];
	auto& to = gt.nodes[t];
	if (!isIn)
	{
		edgeTable<T>* edge = new edgeTable<T>(weight, from, to);
		from->out += 1;
		to->in += 1;

		from->nexts.push_back(to);
		from->edges.push_back(edge);

		gt.edges.insert(edge);
	}

	return false;

}
template<typename T>
bool Graph<T>::RemoveEdge(graphTable<T>& gt, int f, int t)
{
	bool isIn = Adjacent(gt, f, t);
	auto& from = gt.nodes[f];
	auto& to = gt.nodes[t];
	if (isIn)
	{
		edgeTable<T>* p;
		edgeTable<T>* it = nullptr;

		for (auto& edge : from->edges)
		{
			if (edge->to == to)
			{
				p = edge;
				it = p;
				break;
			}
		}
		(from->out)--;
		(to->in)--;

		from->nexts.erase(find(from->nexts.begin(), from->nexts.end(), it->to));
		gt.edges.erase(p);
	}
	return true;
}
template<typename T>
nodeTable<T>* Graph<T>::ReturnFistNode(graphTable<T>& gt, int x)
{
	if (gt.nodes[x]->nexts.size())
	{
		return gt.nodes[x]->nexts[0];
	}
	return nullptr;
}
template<typename T>
nodeTable<T>* Graph<T>::ReturnNextNode(graphTable<T>& gt, int x)
{
	size_t size = gt.nodes[x]->nexts.size();
	if (size > 1)
	{
		if (size == 2)
			return nullptr;

		return gt.nodes[x]->nexts[1];
	}
	return nullptr;
}
template<typename T>
void Graph<T>::SetEdgeValue(graphTable<T>& gt, int f, int t, int v)
{
	bool isIn = Adjacent(gt, f, t);
	if (!isIn)
		return;
	auto& from = gt.nodes[f];
	auto& to = gt.nodes[t];
	for (auto& edge : from->edges)
	{
		if (edge->to == to)
		{
			edge->weight = v;
		}
	}
}
template<typename T>
int  Graph<T>::GetEdgeValue(graphTable<T>& gt, int f, int t)
{
	bool isIn = Adjacent(gt, f, t);
	if (!isIn)
		return -1;
	auto& from = gt.nodes[f];
	auto& to = gt.nodes[t];
	for (auto& edge : from->edges)
	{
		if (edge->to == to)
		{
			return edge->weight;
		}
	}
	return -1;
}
template<typename T>
void Graph<T>::bfs(nodeTable<T>* node)
{
	if (node == nullptr)
		return;
	queue<nodeTable<T>*> qu;
	set<nodeTable<T>*> s;

	qu.push(node);
	s.insert(node);
	nodeTable<T>* q;
	while (!qu.empty())
	{
		q = qu.front();
		qu.pop();
		cout << format("value is {}", q->value) << endl;
		if (q->nexts.size() != 0)
		{
			for (auto& next : q->nexts)
			{
				if (s.count(next) == 0)
				{
					qu.push(next);
					s.insert(next);
				}
			}
		}
	}

}
template<typename T>
void Graph<T>::dfs(nodeTable<T>* node)
{
	if (node == nullptr)
		return;
	stack<nodeTable<T>*>sta;
	set<nodeTable<T>*>s;
	nodeTable<T>* q;

	sta.push(node);
	s.insert(node);
	q = node;
	cout << "value is " << q->value << endl;
	while (!sta.empty())
	{
		q = sta.top();
		sta.pop();
		for (auto& next : q->nexts)
		{
			if (s.count(next) == 0)
			{
				cout << format("value is {}", next->value) << endl;
				sta.push(q);
				sta.push(next);
				s.insert(next);
				break;
			}
		}
	}
}
template<typename T>
int Graph<T>::transformArraysDirected(graphTable<T>& gt, vector<vector<int>> arrays)
{
	int size = arrays.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i)
				continue;
			if (arrays[i][j] == INT_MAX)
				continue;
			InsertNode(gt, i + 1);
			InsertNode(gt, j + 1);
			AddEdge(gt, i + 1, j + 1, arrays[i][j]);

		}
	}

	return 1;
}
template<typename T>
int Graph<T>::transformArraysUndirected(graphTable<T>& gt, vector<vector<int>> arrays)

{
	int size = arrays.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			if (j == i)
				continue;
			if (arrays[i][j] == 0)
				continue;
			InsertNode(gt, i + 1);
			InsertNode(gt, j + 1);
			AddEdge(gt, i + 1, j + 1, arrays[i][j]);

		}
	}

	return 1;
}
template<typename T>
vector<nodeTable<T>*> Graph<T>::sortedToplogy(graphTable<T>& gt)
{
	map<nodeTable<T>*, int> inMap;
	queue<nodeTable<T>*> zeroQueue;

	for (auto& node : gt.nodes)
	{
		inMap.emplace(node.second,node.second->in);
		if (node.second->in == 0)
		{
			zeroQueue.push(node.second);
		}
	}
	vector<nodeTable<T>*>res;
	while (!zeroQueue.empty())
	{
		auto& p = zeroQueue.front();
		zeroQueue.pop();
		res.push_back(p);

		for (auto& next : p->nexts)
		{
			inMap.at(next) -= 1;
			if (inMap.at(next) == 0)
			{
				zeroQueue.push(next);
			}
		}
	}
	return res;
}

template<typename T>
bool Graph<T>::sortedToplogyForCritical(graphTable<T>& gt, stack<nodeTable<T>*>& s,vector<int>&etv)
{
	int count = 0;
	map<nodeTable<T>*, int> inMap;
	stack<nodeTable<T>*> zeroQueue;

	for (auto& node : gt.nodes)
	{
		inMap.emplace(node.second, node.second->in);
		if (node.second->in == 0)
		{
			zeroQueue.push(node.second);
		}
	}
	while (!zeroQueue.empty())
	{
		auto& p = zeroQueue.top();
		zeroQueue.pop();

		s.push(p);
		count++;

		for (auto& edge: p->edges)
		{
			inMap.at(edge->to) -= 1;
			if (inMap.at(edge->to) == 0)
			{
				zeroQueue.push(edge->to);
			}
			if ((etv[edge->from->value-1] + edge->weight) > etv[edge->to->value-1])
			{
				etv[edge->to->value-1] = etv[edge->from->value-1] + edge->weight;
			}
		}
	}
	if (count < gt.nodes.size())
	{
		return false;
	}
	return true;
}
template<typename T>
bool Graph<T>::CriticalPath(graphTable<T>&gt)
{
	stack<nodeTable<T>*> s;
	vector<int>etv(gt.nodes.size(), 0);
	this->sortedToplogyForCritical(gt, s, etv);
	
	vector<int> ltv( gt.nodes.size(),0 );
	for (int i = 0; i < etv.size(); ++i)
	{
		ltv[i] = etv[etv.size() - 1];
	}

	while (!s.empty())
	{
		auto& p = s.top();
		s.pop();
		
		for (auto& edge : p->edges)
		{
			if (ltv[edge->to->value-1] - edge->weight < ltv[edge->from->value-1])
			{
				ltv[edge->from->value- 1] = ltv[edge->to->value - 1] - edge->weight;
			}
		}
	}


	int ete = 0;
	int lte = 0;
	for (int i = 1; i < gt.nodes.size()+1; ++i)
	{
		for (auto &edge:gt.nodes[i]->edges)
		{
			ete = etv[i-1];
			lte = ltv[edge->to->value-1] - edge->weight;

			if (ete == lte)
			{
				cout << format("({},{}):length{}", edge->from->value, edge->to->value, edge->weight) << endl;
			}
		}
	}
	return true;
}
template<typename T>
set<edgeTable<T>*, Compare_Edge_Max<T>> Graph<T>::primMST(graphTable<T>& gt)
{
	priority_queue<edgeTable<T>*, vector<edgeTable<T>*>, Compare_Edge_Min<T>> pq;
	set<nodeTable<T>*,Compare_Node<T>> nodes;
	set<edgeTable<T>*,Compare_Edge_Max<T>> edges;
	for (auto& node : gt.nodes)
	{
		if (!nodes.count(node.second))
		{
			nodes.insert(node.second);
			for(auto& edge:node.second->edges)
			{
				pq.push(edge);
			}
			while (!pq.empty())
			{
				auto edge = pq.top();
				pq.pop();
				if (!nodes.count(edge->to))
				{
					nodes.insert(edge->to);
					edges.insert(edge);
					for (auto& ed : edge->to->edges)
					{
						pq.push(ed);
					}
				}
			}
		}
	}

	return edges;
}
#endif //
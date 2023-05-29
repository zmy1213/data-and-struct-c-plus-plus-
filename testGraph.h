#include<iostream>
#include "grouph.h"
#include <cstdlib>
#include <ctime>

static const int INF = INT_MAX; // 表示正无穷
template<typename T>
void ContainerPrintOneDimension(T values);//输出一维数组
template<typename T>
void ContainerPrintTwoDimension(T values);//输出二维数组
vector<vector<int>> RandomMatrix(int n);//生产随机数组
void Print(auto& p);//输出数组
void PrintEdge(auto& values);//输出边的权重

void init1(Graph<int>& g, graphTable<int>& gt);
void init2(Graph<int>& g, graphTable<int>& gt);
void Init3(Graph<int>& g, graphTable<int>& gt);
void TestGraph();
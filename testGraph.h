#include<iostream>
#include "grouph.h"
#include <cstdlib>
#include <ctime>

static const int INF = INT_MAX; // ��ʾ������
template<typename T>
void ContainerPrintOneDimension(T values);//���һά����
template<typename T>
void ContainerPrintTwoDimension(T values);//�����ά����
vector<vector<int>> RandomMatrix(int n);//�����������
void Print(auto& p);//�������
void PrintEdge(auto& values);//����ߵ�Ȩ��

void init1(Graph<int>& g, graphTable<int>& gt);
void init2(Graph<int>& g, graphTable<int>& gt);
void Init3(Graph<int>& g, graphTable<int>& gt);
void TestGraph();
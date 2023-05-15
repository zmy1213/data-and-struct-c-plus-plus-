#include<iostream>

#include "grouph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<ctime>

#include "RBT.h"
#include "AVLMeau.h"
using namespace std;

const int INF = INT_MAX; // ��ʾ������
template<typename T>
void ContainerPrintOneDimension(T values)
{
	for (auto value : values)
	{
		cout << value << " ";
		
	}
	cout << endl;

}
template<typename T>
void ContainerPrintTwoDimension(T values)
{
	for (auto con : values)
	{
		for (auto value : con)
		{
			cout << value << " ";
		}
		cout << endl;
	}

}
vector<vector<int>> RandomMatrix(int n)
{
	srand(time(NULL)); // �����������
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	 //������ɾ���
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][j] = 0; // �Խ����ϵ�Ԫ��Ϊ 0
			}
			else {
				matrix[i][j] = rand() % 10 + 1; // ������� 1~10 ֮�������
				if (matrix[i][j] == 1) { // ������ֻ�·
					matrix[i][j] = INF;
				}
			}
		}
	}
	return matrix; 
}
void Print(auto& p)
{
	for (auto c : p)
	{
		cout << c->value << endl;
	}
}
void PrintEdge(auto& values)
{
	for (auto& val : values)
	{
		cout << format("weight:{},from node{},to node{}", val->weight, val->from->value, val->to->value) << endl;
	}
	cout << endl;
}

void init1(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 1; i < 10; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 1, 2, 6);
	g.AddEdge(gt, 2, 5, 1);
	g.AddEdge(gt, 5, 7, 9);
	g.AddEdge(gt, 7, 9, 2);

	g.AddEdge(gt, 1, 3, 4);
	g.AddEdge(gt, 3, 5, 1);
	g.AddEdge(gt, 5, 8, 7);
	g.AddEdge(gt, 8, 9, 4);

	g.AddEdge(gt, 1, 4, 5);
	g.AddEdge(gt, 4, 6, 2);
	g.AddEdge(gt, 6, 8, 4);
}
void init2(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 1; i < 7; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 1, 2, 6);
	g.AddEdge(gt, 1, 3, 1);
	g.AddEdge(gt, 1, 4, 5);

	g.AddEdge(gt, 2, 3, 5);
	g.AddEdge(gt, 2, 1, 6);
	g.AddEdge(gt, 2, 5, 3);

	g.AddEdge(gt, 3, 1, 1);
	g.AddEdge(gt, 3, 2, 5);
	g.AddEdge(gt, 3, 4, 5);
	g.AddEdge(gt, 3, 5, 6);
	g.AddEdge(gt, 3, 6, 4);

	g.AddEdge(gt, 4, 3, 5);
	g.AddEdge(gt, 4, 1, 5);
	g.AddEdge(gt, 4, 6, 2);

	g.AddEdge(gt, 5, 2, 3);
	g.AddEdge(gt, 5, 3, 6);
	g.AddEdge(gt, 5, 6, 6);

	g.AddEdge(gt, 6, 3, 4);
	g.AddEdge(gt, 6, 4, 2);
	g.AddEdge(gt, 6, 5, 6);

}
void Init3(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 1; i < 6; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 1, 2, 10);
	g.AddEdge(gt, 1, 5, 5);

	g.AddEdge(gt, 2, 5, 2);
	g.AddEdge(gt, 2, 3, 1);

	g.AddEdge(gt, 3, 4, 4);

	g.AddEdge(gt, 4, 1, 7);
	g.AddEdge(gt, 4, 3, 6);

	g.AddEdge(gt, 5, 2, 3);
	g.AddEdge(gt, 5, 3, 9);
	g.AddEdge(gt, 5, 4, 2);
}
void TestGraph()
{
	graphTable<int> gt;
	vector<vector<int>> arrays{
		{INT_MAX,5,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
		{INT_MAX,INT_MAX,4,INT_MAX,INT_MAX,INT_MAX},
		{8,INT_MAX,INT_MAX,INT_MAX,INT_MAX,9},
		{INT_MAX,INT_MAX,5,INT_MAX,INT_MAX,6},
		{INT_MAX,INT_MAX,INT_MAX,5,INT_MAX,INT_MAX},
		{3,INT_MAX,INT_MAX,INT_MAX,1,INT_MAX}
	};
	vector<vector<int>> arrays1{
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,0},
		{0,0,1,0}
	};
	vector<vector<int>> arrays2{
		{0,6,13},
		{10,0,4},
		{5,INT_MAX,0}
	};
	Graph<int> g(gt);
	init2(g, gt);
	auto r1 = g.primMST(gt);
	auto  r2 = g.krukalMST(gt);

	PrintEdge(r1);
	PrintEdge(r2);
	Init3(g, gt);
	auto res = g.dijkstra((gt.nodes[1]));
	g.createArrayByGraph(gt);
	g.Floyd(gt,arrays2);//����ֵ dan������ֵ�Ļ�·
	auto matrix = RandomMatrix(4);
	ContainerPrintTwoDimension(matrix);
	g.transformArraysUndirected(gt, matrix);
	cout << endl;
	g.Floyd(gt, matrix);

	ContainerPrintTwoDimension(matrix);
	cout << endl;
	ContainerPrintTwoDimension(g.path);
	g.PrintPath(2, 4);
}

void TestRBT()
{

	RedBlackTree<int> rbt1;
	vector<int> t{ 20,10,5,30,40,57,3,2,4,35,25,18,22,23,24,19};
	for (auto& val : t)
	{
		rbt1.insert(val);
		rbt1.PrintRBTree();
		cout << "---------------------" << endl;
	}
	//rbt1.PrintRBTree();
}
//AVL
//���顢˳���Ķ��ֲ���
template<class ElementType>
int BinarySearch(ElementType A[], int n, ElementType x)
{
	int mid, low = 0, high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x == A[mid])
		{
			return mid;
		}
		else if (x < A[mid])
		{
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;
}
//��ʼ������
void initArray(int A[])
{
	int i = 0;
	for (i; i < 100; i++)
		A[i] = 0;
}
int Meau()
{
	int x, y;
	int i = 1;
	int level = 1;
	int A[100] = { 0 };
	int B[100] = { 0 };
	int length = 0;       //�洢����A����ЧԪ�ظ���
	Node<int>* root;
	Node<int>* p;
	BalanceBiTree<int> T(root);
	BalanceBiTree<int>::menu();
	cout << "������ִ����ţ�";
	cin >> x;
	while (x != 0)
	{
		switch (x)
		{
		case 1:
			if (root != NULL)
				T.destory(root);
			length = 0;
			cout << "����������Ԫ�ص�ֵ��";
			cin >> y;
			while (y != -9999)
			{
				A[length] = y;
				length++;
				cout << "����������Ԫ�ص�ֵ��";
				cin >> y;
			}
			cout << "������Ҫ��ѯԪ�ص�ֵ��";
			cin >> x;
			if (BinarySearch(A, length + 1, x) == -1)
				cout << "����i=1;�ڣ�" << endl;
			else {
				cout << "���ڣ����±�Ϊ��" << BinarySearch(A, length + 1, x) << endl;
			}
			break;
		case 2:
			T.createSubBalanceBiTree(root);
			break;
		case 3:
			cout << "������Ҫ��ѯԪ�ص�ֵ��";
			cin >> x;
			T.search(root, p, x);
			if (p != NULL)
			{
				if (p->data == x)
					cout << "Ԫ�ش��ڣ�" << endl;
				else
					cout << "Ԫ�ز����ڣ�" << endl;
			}
			else {
				cout << "Ԫ�ز����ڣ�" << endl;
			}
			break;
		case 4:
			i = 1;
			initArray(A);
			level = 1;
			cout << "������Ҫɾ��Ԫ�ص�ֵ��";
			cin >> x;
			T.deleteOperate(root, x);
			T.inOrderTraverse(root, level);
			T.BiTreeToArray(root, A, i, length);
			cout << "����״ͼΪ��" << endl;
			T.LevelTraverse(root, A, length);
			break;
		case 5:
			initArray(A);
			if (root != NULL)
				T.destory(root);
			length = 0;
			y = 1;
			for (y; y <= 26; y++)
			{
				A[length] = y;
				length++;
			}
			T.createBalanceBiTreeFromArray(root, A, length);
			level = 1;
			i = 1;
			T.inOrderTraverse(root, level);
			cout << endl;
			initArray(A);
			T.BiTreeToArray(root, A, i, length);
			cout << "����״ͼΪ��" << endl;
			T.LevelTraverse(root, A, length);
			break;
		case 6:
			i = 1;
			initArray(A);
			T.AllAdjust(root);
			T.BiTreeToArray(root, A, i, length);
			cout << "����״ͼΪ��" << endl;
			T.LevelTraverse(root, A, length);
			break;
		}
		system("PAUSE");
		system("CLS");
		BalanceBiTree<int>::menu();
		cout << "������ִ����ţ�";
		cin >> x;
	}
	if (root != NULL)
		T.destory(root);
	return 0;
}
int main()
{
	TestRBT();
	Meau();
	return 0;
}

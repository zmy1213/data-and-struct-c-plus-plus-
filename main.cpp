#include<iostream>

#include "grouph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<ctime>

#include "RBT.h"
#include "AVLMeau.h"
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "BPlusTree.h"
#include "Context.h"

void TestBTree()
{

	/*************************************直接调用B  B+ 的调度使用****************************************/
	/************************************* Direct call B + B method ****************************************/
	BTree bt;
	BPlusTree bpt;

	int arr[] = { 18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bt.insert(arr[i]);
		bpt.insert(arr[i]);
	}
	printf("no delete data:\n");
	printf("display about B-Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n\n");

	printf("display about B+ Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n");
	bpt.linear_print();
	printf("\n");
	bt.NodeNum_print();
	bpt.NodeNum_print();
	printf("delete data...\n");
	int todel[] = { 15, 18, 23, 30, 31, 52, 50 };

	for (int i = 0; i < sizeof(todel) / sizeof(int); i++) {
		printf("after delete %d\n", todel[i]);
		bt.del(todel[i]);
		bpt.del(todel[i]);
	}

	bt.NodeNum_print();
	bpt.NodeNum_print();

	printf("\n\ndelete after data:\n");
	printf("display about B-Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n\n");

	printf("display about B+ Tree:\n");
	bpt.level_display();
	bpt.inorder_print();
	printf("\n");
	bpt.linear_print();
	printf("\n");

	/***************************************************************************************************/
	/***************************************************************************************************/
	/************************************* 用策略方法的调用B    ****************************************/
	/************************************* strategy pattern method ****************************************/

	printf("strategy method start\n");

	//“具体策略类”只在定义多个“调度类”时使用
	Context* Context_A = new Context(new BTree()),
		* Context_B = new Context(new BPlusTree());

	//调用方法，只通过“调度类”实现，算法之间的差异已被屏蔽
	int arrnum[] = { 10, 2, 3, 4, 5, 9, 8, 7, 6,1 };
	for (int i = 0; i < sizeof(arrnum) / sizeof(int); i++) {
		Context_A->Insert(arrnum[i]);
		Context_B->Insert(arrnum[i]);
	}
	Context_A->Inorder_Print();
	printf("\n\n");
	Context_B->LevelDisplay();

	/***************************************************************************************************/
	/***************************************************************************************************/
}
const int INF = INT_MAX; // 表示正无穷
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
	srand(time(NULL)); // 设置随机种子
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	 //随机生成矩阵
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][j] = 0; // 对角线上的元素为 0
			}
			else {
				matrix[i][j] = rand() % 10 + 1; // 随机生成 1~10 之间的整数
				if (matrix[i][j] == 1) { // 避免出现环路
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
	g.Floyd(gt,arrays2);//允许负值 dan不允许负值的回路
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
//数组、顺序表的二分查找
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
//初始化数组
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
	int length = 0;       //存储数组A的有效元素个数
	Node<int>* root;
	Node<int>* p;
	BalanceBiTree<int> T(root);
	BalanceBiTree<int>::menu();
	cout << "请输入执行序号：";
	cin >> x;
	while (x != 0)
	{
		switch (x)
		{
		case 1:
			if (root != NULL)
				T.destory(root);
			length = 0;
			cout << "请输入数组元素的值：";
			cin >> y;
			while (y != -9999)
			{
				A[length] = y;
				length++;
				cout << "请输入数组元素的值：";
				cin >> y;
			}
			cout << "请输入要查询元素的值：";
			cin >> x;
			if (BinarySearch(A, length + 1, x) == -1)
				cout << "不存i=1;在！" << endl;
			else {
				cout << "存在，其下标为：" << BinarySearch(A, length + 1, x) << endl;
			}
			break;
		case 2:
			T.createSubBalanceBiTree(root);
			break;
		case 3:
			cout << "请输入要查询元素的值：";
			cin >> x;
			T.search(root, p, x);
			if (p != NULL)
			{
				if (p->data == x)
					cout << "元素存在！" << endl;
				else
					cout << "元素不存在！" << endl;
			}
			else {
				cout << "元素不存在！" << endl;
			}
			break;
		case 4:
			i = 1;
			initArray(A);
			level = 1;
			cout << "请输入要删除元素的值：";
			cin >> x;
			T.deleteOperate(root, x);
			T.inOrderTraverse(root, level);
			T.BiTreeToArray(root, A, i, length);
			cout << "其树状图为：" << endl;
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
			cout << "其树状图为：" << endl;
			T.LevelTraverse(root, A, length);
			break;
		case 6:
			i = 1;
			initArray(A);
			T.AllAdjust(root);
			T.BiTreeToArray(root, A, i, length);
			cout << "其树状图为：" << endl;
			T.LevelTraverse(root, A, length);
			break;
		}
		system("PAUSE");
		system("CLS");
		BalanceBiTree<int>::menu();
		cout << "请输入执行序号：";
		cin >> x;
	}
	if (root != NULL)
		T.destory(root);
	return 0;
}
int main()
{
	/*TestRBT();
	Meau();*/
	TestBTree();
	return 0;
}

#pragma once
#include "AVL.h"
//调用AVLMEAU即可
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
}//二分查找
//初始化数组
void initArray(int A[])
{
	int i = 0;
	for (i; i < 100; i++)
		A[i] = 0;
}
int AVLMeau()
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

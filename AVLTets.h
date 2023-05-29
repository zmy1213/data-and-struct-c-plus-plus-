#pragma once
#include "AVL.h"
//����AVLMEAU����
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
}//���ֲ���
//��ʼ������
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

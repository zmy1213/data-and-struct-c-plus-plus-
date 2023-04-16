#pragma once
#ifndef THREADED_BINARY_TREE_H
#define THREADED_BINARY_TREE_H
#include<iostream>
#include<type_traits>
#include<vector>
using namespace std;
template<typename T>
concept Type = true;

using PointerTag = enum tag{Link,Thread};

template<Type T>
struct BiThrNode
{
	T data;
	struct BiThrNode<T>* lchild;
	struct BiThrNode<T>* rchild;
	PointerTag LTag;
	PointerTag RTag;
	BiThrNode()
	{
		lchild = rchild = nullptr;
	}
};

template<Type T>
using BiThrTree = BiThrNode<T>*;

template<Type T>
BiThrNode<T>* CreateBiThrNode(BiThrTree<T> B,vector<T> &values,int start)
{
	if (start >= values.size() - 1)
		return nullptr;

	B = new BiThrNode<T>;
	B->data = values[start];
	B->LTag = Link;
	B->RTag = Link;

	if (2 * start + 1 < values.size())
	{	
		CreateBiThrNode(B->lchild, values, 2*start + 1);
	}
	if (2 * start + 2 < values.size())
	{
		CreateBiThrNode((B->rchild), values, 2*start+2);
	}
	return B;
}
template<Type T>
void InThreading(BiThrTree<T> &B, BiThrTree<T>& pre)
{
	if (!B) return;
	InThreading(B->lchild, pre);

	if (B->lchild==nullptr)
	{
		B->LTag = Thread;
		B->lchild = pre;
	}

	if (pre!=nullptr&&pre->rchild==nullptr)
	{
		pre->RTag = Thread;
		pre->rchild = B;
	}
	pre = B;
	InThreading(B->rchild, pre);
}

template<Type T>
int InOrderThreading(BiThrTree<T> &Thrt, BiThrTree<T> &BT)
{
	Thrt = new BiThrNode<T>;
	Thrt->data = -1;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;

	if (!BT)
	{
		Thrt->lchild = Thrt;
		return true;
	}

	BiThrTree<T> pre;
	pre = Thrt;
	Thrt->lchild = BT;
	InThreading(BT, pre);

	pre->rchild = Thrt;
	pre->RTag = Thread;
	Thrt->rchild = pre;
	
}

template<Type T>
void InOrderPrint(const BiThrTree<T>&BT)
{
	BiThrNode<T>* p = BT->lchild;
	while (p != BT)
	{
		while (p->LTag == Link)
			p = p->lchild;
		cout << p->data << " ";
		while (p->RTag == Thread && p->rchild != BT)
		{
			p = p->rchild;
			cout << p->data << " ";
		}
		p = p->rchild;
	}
}
#endif // !THREADED_BINARY_TREE

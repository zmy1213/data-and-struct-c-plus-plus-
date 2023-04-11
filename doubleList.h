#ifndef doubleList_H
#define doubleList_H
#include<iostream>
#include<type_traits>
#include<vector>
using namespace std;
template<typename T>
concept isBasicType = is_arithmetic_v<T>;

template<typename T>
concept always_satisfied = true;

template<isBasicType T>
struct DNode
{
	T data;
	struct DNode* prior, * next;
};

template<isBasicType T>
using DLinkList = DNode<T>*;

template<isBasicType T>
bool InitNode(DLinkList<T> head)
{
	if (head == nullptr)
		return false;
	head->next = nullptr;
	head->prior = nullptr;
}
template<isBasicType T>
DNode<T>* LocateNode(const DLinkList<T> head, int value)
{
	if (head == nullptr)
		return nullptr;
	size_t t = 0;
	DNode<T>* tm = head->next;
	while (tm->next)
	{
		if (tm->next->data = value)
			return tm;
		tm = tm->next;
	}
	return nullptr;
}

template<isBasicType T>
bool InsertNode(DLinkList<T> head, int value, int index)
{
	if (head == nullptr)
		return false;

	DNode<T>* findNode = LocateNode<T>(head, index);
	if (findNode == nullptr)
		return false;

	DNode<T>* newNode = new DNode<T>;
	newNode->data = value;

	newNode->next = findNode->next;
	findNode->next->prior = newNode;
	findNode->next = newNode;
	newNode->prior = findNode;

	return true;
}
template<isBasicType T>
bool DeleteNode(DLinkList<T> head, int val)
{
	if (head == nullptr)
		return false;

	DNode<T>* findNode = LocateNode<T>(head, val);
	if (findNode == nullptr)
		return false;

	DNode<T>* delNode = findNode->next;

	findNode->next = findNode->next->next;
	findNode->next->prior = findNode;

	delNode->next = nullptr;
	delNode->prior = nullptr;

	return true;
}
template<isBasicType T>
bool InsertHead(DLinkList<T> head, vector<T> vals)
{
	if (head == nullptr)
		return false;
	DNode<T>* p;
	for (auto val : vals)
	{
		p = new DNode<T>;

		p->next = head->next;
		p->prior = head;
		if (p->next != nullptr)
			head->next->prior = p;
		head->next = p;
		p->data = val;
	}
	return true;
}
template<isBasicType T>
void Print(const DLinkList<T> head)
{
	DNode<T>* t = head->next;
	while (t)
	{
		cout << t->data << " ";
		t = t->next;
	}
	cout << endl;
}
#endif // !1

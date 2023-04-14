#ifndef SingleList_H
#define  SingleList_H
#include<iostream>
#include<type_traits>
#include<vector>
using namespace std;
//不带头节点
template<typename T>
struct LinkNode
{
	T data;
	struct LinkNode<T>* next;
	LinkNode() {}
	LinkNode(T val) :data(val) {}
};
template<typename T>
using LinkList = LinkNode<T>*;
template<typename T>
bool InitList(LinkList<T> L)
{
	if (L == nullptr)
		return false;
	L->data = 0;
	L->next = nullptr;//带头结点的设置next为nullptr
	return true;
}
template<typename T>
bool IsEmpty(const LinkList<T> L)
{
	return (L->next == nullptr);
}
template<typename T>
bool InsertNode(LinkList<T> L, int index, T& ele)//不带头节点对等于1特殊处理
{
	if (L == nullptr)
		return false;
	if (index < 1)
		return false;

	int t = 1;
	LinkNode<T>* tn = new LinkNode<T>;
	tn = L;
	while (t < index && tn)
	{
		t++;
		tn = tn->next;
	}
	//NextInsert(tn, ele);
	FrontInsert(tn, ele);
	return true;
}
template<typename T>
void Print(const LinkList<T> L)
{
	LinkNode<T>* p;
	p = L;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
template<typename T>
bool DeleteNode(LinkList<T> L, int index, T& ele)
{
	if (L == nullptr)
		return false;
	if (index < 1)
		return false;
	LinkNode<T>* p = new LinkNode<T>;
	p = L;
	int i = 1;
	while (i < index && p)
	{
		p = p->next;
		++i;
	}
	LinkNode<T>* t = new LinkNode<T>;
	ele = p->next->data;
	t = p->next;
	p->next = t->next;
	t->next = nullptr;

	t = nullptr;
	delete t;
	return true;
}
template<typename T>
bool FrontInsert(LinkList<T> p, T ele)
{
	if (p == nullptr)
		return false;
	LinkNode<T>* fro = new LinkNode<T>;
	if (fro == nullptr)
		return false;


	fro->next = p->next;
	p->next = fro;

	fro->data = ele;

	fro = nullptr;
	delete fro;
	return true;
}
template<typename T>
bool NextInsert(LinkList<T> p, T ele)
{
	if (p == nullptr)
		return false;

	LinkNode<T>* in = new LinkNode<T>;
	if (in == nullptr)
		return false;

	in->next = p->next;
	p->next = in;
	in->data = ele;

	in = nullptr;
	delete in;

	return true;

}
template<typename T>
bool DeleteNode(LinkNode<T>* p)
{
	if (p == nullptr)
		return false;
	if (p->next == nullptr)
	{
		p = nullptr;
	}
	LinkNode<T>* q = p->next;
	p->data = p->next->data;
	p->next = q->next;

	q = nullptr;
	return true;
}
template<typename T>
LinkNode<T>* LocateNode(LinkList<T> L, int i)
{
	if (i < 0)
		return nullptr;
	LinkNode<T>* p;
	int index = 0;
	p = L;
	while (p != nullptr && index < i)
	{
		p = p->next;
		++index;
	}
	return p;
}
template<typename T>
LinkNode<T>* LoacateByValue(LinkList<T> L, int v)
{
	if (L == nullptr || L->next == nullptr)
		return nullptr;
	LinkNode<T>* ln = L;
	while (ln->data != v)
	{
		if (ln != nullptr)
		{
			ln = ln->next;
		}
		else {
			return nullptr;
		}
	}
	return ln;
}
template<typename T>
LinkList<T> TailInsert(LinkList<T> L, vector<T> values)
{
	L = new LinkNode<T>;
	InitList(L);
	LinkNode<T>* s, * r;
	r = L;
	int size = 0;
	while (size < values.size())
	{
		s = new LinkNode<T>(values[size]);
		r->next = s;
		r = s;
		size++;

	}
	r->next = nullptr;
	return L;
}
template<typename T>
LinkList<T> HeadInsert(LinkList<T> L, vector<T> values)
{
	L = new LinkNode<T>;
	InitList(L);
	LinkNode<T>* s;
	int size = 0;
	while (size < values.size())
	{

		s = new LinkNode<T>(values[size]);
		s->next = L->next;
		L->next = s;
		size++;

	}
	return L;
}

//int main()
//{
//	srand(time(NULL));
//
//	LinkList<int> l = new LinkNode<int>;
//	InitList(l);
//	LinkNode<int>* p = new LinkNode<int>;
//	vector<int> vs;
//	for (int i = 1; i <= 20; ++i)
//	{
//		InsertNode(l, i, i);
//		vs.push_back(rand()%20);
//	}
//	int t = 0;
//	DeleteNode(l,3,t);
//	auto res = LocateNode(l, 2);
//	cout << res->data << endl;
//	auto res1 = LoacateByValue(l, 12);
//	cout << res1->data << endl;
//
//	LinkList<int> ll = new LinkNode<int>;
//	InitList(ll);
//	auto tailList = TailInsert(ll, vs);
//	Print(tailList);
//	auto headList = HeadInsert(ll, vs);
//	Print(headList);
//	Print(l);
//}
#endif // !SingleList_H


#include<iostream>
using namespace std;
const int MAXSIZE = 1000;
template<typename T>
struct SeqList
{
	T* data;
	int MaxSize;
	int length;
};
template<typename T>
using SeqListP = SeqList<T>*;
template<typename T>
void InitList(SeqListP<T> L)
{
	L->length = 0;
	L->MaxSize = MAXSIZE;
	L->data = new T[MAXSIZE];
	/*for (int i = 0; i < MAXSIZE; ++i)
	{
		L->data[i] = 0;
	}*/

}
template<typename T>
void IncreaseSize(SeqListP<T> L, int len)
{
	if (L == nullptr)
		return;
	T* p = L->data;
	L->data = new T[(L->MaxSize) + len];
	for (int i = 0; i < L->length; ++i)
	{
		L->data[i] = p[i];
	}
	delete p;
	L->MaxSize = L->MaxSize + len;

}
template<typename T>
bool InsertValue(SeqListP<T> L, int index, int ele)
{
	if (L == nullptr)
		return false;
	if (index > L->MaxSize||index < 1)
		return false;
	if (L->length == L->MaxSize)
		return false;
	for (int i = L->length; i >= index; i--)
	{
		L->data[i] = L->data[i-1];
	}
	L->data[index-1] = ele;
	L->length += 1;
	return true;
}
template<typename T>
bool DeleteValue(SeqListP<T> L,int index, T&ele)
{
	if (index<0 || index>L->MaxSize)
		return false;
	if (L == nullptr)
		return false;

	ele = L->data[index - 1];
	for (int i = index; i < L->length; ++i)
	{
		L->data[i - 1] = L->data[i];
	}
	L->length--;
	return true;
}
template<typename T>
void Print(const SeqListP<T> L)
{
	for (int i = 0; i < L->length; ++i)
	{
		cout << L->data[i] << " ";
	}
	cout << endl;
}
template<typename T>
T GetLocateValue(const SeqListP<T> L, int index) { return L->data[index - 1]; }
template<typename T>
int LocateEle(const SeqListP<T> L, T ele)
{
	for (int i = 0; i < L->length; ++i)
	{
		if (L->data[i] == ele)
			return i+1;
	}
	return 0;
}
//int main()
//{
//	SeqListP<int> l = new SeqList<int>;
//	InitList(l);
//	IncreaseSize(l, 30);
//
//	for (int i = 0; i < 20; ++i)
//	{
//		l->data[i] = i;
//		l->length++;
//	}
//
//	InsertValue(l, 10, 1000);
//	Print(l);
//	int e = 0;
//	DeleteValue(l, 10,e);
//	Print(l);
//	cout << "e:" << e << endl;
//	auto res_in = LocateEle(l, 18);
//	auto res_val = GetLocateValue(l, 13);
//	cout << "index:" << res_in << endl;
//	cout << "value (index13):" << res_val << endl;
//	return 0;
//}
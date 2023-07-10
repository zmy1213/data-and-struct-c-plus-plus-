#include<iostream>

using namespace std;

const int MAXSIZE = 100;

typedef struct
{
	int next;
	int value;
	int len;
}StaticList[MAXSIZE];

void InitList(StaticList sl)
{
	sl[0].next = -1;

	for (int i = 1; i < MAXSIZE; ++i)
	{
		sl[i].next = -2;
	}
}
bool Isempty(StaticList sl)
{
	if (sl->next == -1)
		return true;
	else
		return false;
}
int CalculateLen(StaticList sl)
{
	if (sl[0].next == -1) return 0;

	int len = 0;
	int index = sl[0].next;
	while (sl[index].next != -1)
	{
		len += 1;
		index = sl[index].next;
	}
	return len;
}
int FindFreeSpace(StaticList sl)
{
	for (int i = 0; i < MAXSIZE; ++i)
	{
		if (sl[i].next == -2)
			return i;
	}
	return -1;
}
bool InsertValue(StaticList sl, int index, int value)
{
	if (sl[0].next == -1)return false;

	int i = 0;
	int insert_index = 0;
	int len = CalculateLen(sl);
	int free_index = FindFreeSpace(sl);

	if (index<0 || index>MAXSIZE)return false;
	if (index > len)return false;
	if (len + 1 > MAXSIZE)return false;


	for (i = 0; i < index - 1; ++i)
	{
		insert_index = sl[insert_index].next;
	}

	sl[free_index].value = value;
	sl[free_index].next = sl[insert_index].next;
	sl[insert_index].next = free_index;

}
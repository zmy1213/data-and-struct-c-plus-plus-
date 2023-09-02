#include<iostream>
using namespace std;

void SwapBubblekSort(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void BubbleSort(int* arr, int len)
{
	int i, j;
	for (i = 0; i < len - 1; i++)
	{
		bool flag = false;
		for (j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				SwapBubblekSort(arr[j], arr[j + 1]);
				flag = true;
			}
		}
		if (flag == false)
			return;
	}
}
#include<iostream>
using namespace std;
void SwapQuickSort(int&a, int&b)
{
	if (a != b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
}
int Partition(int* arr, int p, int r)
{
	int x = arr[r];//»ù×¼
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			SwapQuickSort(arr[i], arr[j]);
		}
	}
		
	SwapQuickSort(arr[++i], arr[r]);
	return i;
}
void QuickSort(int* arr, int p, int r)
{
	if (p < r)
	{
		int q = Partition(arr, p, r);
		QuickSort(arr, p, q - 1);
		QuickSort(arr, q + 1, r);
	}
}


//int main()
//{
//	int arr[12] = { 2,7,4,9,8,5,7,8,2,0,7,-4 };
//	QuickSort(arr, 0, 11);
//	for (int i = 0; i < 12; i++)
//	{
//		cout << arr[i] << " ";
//	}
//	return 0;
//}
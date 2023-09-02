#include"InsertSort.h"
void InsertSort(int* arr, int n)
{
	int temp;
	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;

	}
}
void OptimizedInsertSort(int* arr, int n)//折半查找优化
{
	int i, j, low, high, mid;
	for (i = 2; i <= n; ++i)
	{
		arr[0] = arr[i];
		low = 1; high = i - 1;

		while (low <= high)
		{
			mid = (low + high) / 2;
			if (arr[mid] > arr[0])
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j >= high + 1; --j)
		{
			arr[j + 1] = arr[j];//从low - i-1 向右移动一位
		}
		arr[high + 1] = arr[0];//arr[mid] = arr[0];//找到插入的位置
	}
}
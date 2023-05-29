#pragma once
#include"config.h"
//void ShellSort(int* arr, int n)
//{
//	int d, i, j;
//	for (d = n / 2; d >= 1; d = d / 2)
//	{
//		for (i = d + 1; i <= n; ++i)
//		{
//			if (arr[i] < arr[i - d])
//			{
//				arr[0] = arr[i];
//			}
//			for (j = i - d; j > 0 && arr[0] < arr[j]; j -= d)
//			{
//				arr[j + d] = arr[j];
//			}
//			arr[j + d] = arr[0];
//		}
//	}
//}

void shellSort(vector<int>& arr, int n);
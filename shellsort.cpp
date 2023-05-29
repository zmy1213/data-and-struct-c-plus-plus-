#include"shellsort.h"
void shellSort(vector<int>& arr, int n)
{
	// 使用希尔增量序列
	for (int gap = n / 2; gap > 0; gap /= 2) {
		// 对每个增量间隔进行插入排序
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}
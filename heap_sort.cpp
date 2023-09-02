#include<iostream>
#include<queue>
using namespace std;
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void heapInsert(int* arr, int index)
{
	while (arr[index] > arr[(index - 1) / 2])
	{
		swap(arr[index], arr[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
void heapify(int* arr, int index, int heapSize)
{
	int left = index * 2 + 1;
	while (left < heapSize)
	{
		int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
		largest = arr[largest] > arr[index] ? largest : index;
		if (largest == index)
		{
			break;
		}
		swap(arr[index], arr[largest]);
		index = largest;
		left = index * 2 + 1;
	}
}
void heapsort(int* arr, int length)
{
	if (arr == NULL || length < 2)
	{
		return;
	}
	for (int i = 0; i < length; i++)
	{
		heapInsert(arr, i);
	}
	int heapSize = length;
	while (heapSize > 0)
	{
		heapify(arr, 0, heapSize);
		swap(arr[0], arr[--heapSize]);
	}
}
int main()
{
	int arr[] = { 16,4,10,14,9,3,2,8,1 };
	int size = sizeof(arr) / sizeof(arr[0]);
	heapsort(arr, size);
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	//cout << endl;
	priority_queue<int, vector<int>, less<int>> pq;
	for (int i = 0; i < size; ++i)
	{
		pq.push(arr[i]);
	}
	for (int i = 0; i < size; ++i)
	{
		cout << pq.top() << " ";
		pq.pop();
	}

	return 0;
}
#include<iostream>
#include<queue>
using namespace std;
void swapHeapSort(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void heapInsert(int* arr, int index)
{
	while (arr[index] > arr[(index - 1) / 2])
	{
		swapHeapSort(arr[index], arr[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
void heapDelete(int* arr, int index,int heapSize)
{
	int left = index * 2 + 1;
	heapSize = heapSize - 1;

	while (left < heapSize)
	{
		int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
		largest = arr[largest] > arr[index] ? largest : index;
		if (largest == index)
		{
			break;
		}
		swapHeapSort(arr[index], arr[largest]);
		index = largest;
		left = index * 2 + 1;
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
		swapHeapSort(arr[index], arr[largest]);
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
		swapHeapSort(arr[0], arr[--heapSize]);
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

	cout << endl;
	priority_queue<int, vector<int>,greater<int>> pq;
	for (int i = 0; i < size; ++i)
	{
		pq.push(arr[i]);
	}
	for (int i = 0; i < size; ++i)
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	bool end = true;
	cout << endl;
	int* newArr = nullptr;
	while (true)
	{
		int oper;
		cout << "删除0，插入1,结束2" << endl;
		cin >> oper;
		switch (oper)
		{
		case 0:
		{
			int index = 0;
			cout << "删除的下表" << endl;
			cin >> index;
			size -= 1;
			swapHeapSort(arr[index], arr[size - 1]);
			heapify(arr, index, size);
			int* newArr = new int[size];
			for (int i = 0; i < size - 1; ++i)
			{
				newArr[i] = arr[i];
			}
			heapsort(arr, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			break;
		}
		case 1:
		{
			int data = 0;
			cout << "插入的数据" << endl;
			cin >> data;
			size += 1;
			int* newArr = new int[size];
			for (int i = 0; i < size - 1; ++i)
			{
				newArr[i] = arr[i];
			}
			arr[size - 1] = data;
			heapInsert(arr, data);
			heapsort(arr, size);
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			break;
		}
		case 2:
		{
			end = false;
			break;
		}
		default:
			cout << "oper 错误，重新输入" << endl;
			break;
		}
	}
	return 0;
}
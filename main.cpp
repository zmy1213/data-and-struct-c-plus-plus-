#include<iostream>
#include"testGraph.h"
//#include"bPlusTreeTest.h"
//#include"BTreeTest.h"
#include"RBTtest.h"
#include "shellsort.h"
//B���ͺ��������һ����,�����ظ�
using namespace std;

void testSort()
{
	vector<int>  values{21, 12, 1, 4, 90, 14, 75, 30, 65};
	shellSort(values, values.size());
	for (auto val : values)
	{
		cout << val << " ";
	}
	cout << endl;
}
int main()
{
	//TestGraph();
	//TestBPTree();
	TestRBT();
	testSort();
	return 0;
}

#include"RBTtest.h"
void TestRBT()
{

	RedBlackTree<int> rbt1;
	vector<int> t{ 20, 10, 5, 30, 40, 57, 3, 2, 4, 35, 25, 18, 22, 23, 24, 19};
	for (auto& val : t)
	{
		rbt1.insert(val);
		rbt1.PrintRBTree();
		cout << "---------------------" << endl;
	}
	rbt1.PrintRBTree();
}

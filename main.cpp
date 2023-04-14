#include"threaded binary tree.h"
int main()
{
	BiThrTree<int> B = new BiThrNode<int>;
	BiThrTree<int> t = new BiThrNode<int>;
	vector<int> vals{ 1,1232,31,12,2,56,54,46};
	CreateBiThrNode(B,vals,0);
	InOrderThreading(t,B);
	InOrderPrint(t);

	t = nullptr;
	B = nullptr;
	delete B;
	delete t;
}
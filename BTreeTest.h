#pragma once
#include"BTRee.h"
using namespace std;
_CMP cmp(const int& a, const int& b) {
	if (a < b) {
		return SMALLER;
	}
	else if (a > b) {
		return BIGGER;
	}
	else {
		return EQUAL;
	}
}
void inorder(TreeNode<int>* h, int level) {
	if (h == NULL) {
		return;
	}
	KeyNode<int>* k = h->key;
	TreeNode<int>* child = h->child;
	cout << "level:" << level << " ";
	while (k != NULL) {
		cout << k->value << " ";
		k = k->next;
	}
	cout << endl;
	while (child != NULL) {
		inorder(child, level + 1);
		child = child->next;
	}
}
void TestBTree() {
	int map[] = {
		25,38,49,60,80,90,99,88,83,87,70,92,93,94,73,74,75,71,72,76,77,86,87,82
	};
	int len = sizeof(map) / sizeof(int);
	BTree<int> tree;
	tree.init(5, &cmp);
	for (int i = 0; i < len; i++) {
		tree.put(map[i]);
		inorder(tree.getHead(), 0);
		cout << "----------------" << endl;
	}

	tree.remove(60);
	inorder(tree.getHead(), 0);
	cout << "----------------" << endl;
	tree.remove(80);
	inorder(tree.getHead(), 0);
	cout << "----------------" << endl;
	inorder(tree.getHead(), 0);
}
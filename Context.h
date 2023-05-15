#pragma once
#include "Tree.h"
/*************************************������****************************************/
//������,���ݴ������Ĳ���,ѡ�����ĳ������
class Context
{
private:
	Tree* strategyChild;
public:
	Context(Tree* child)
	{
		strategyChild = child;
	}

	void Insert(int target)
	{
		strategyChild->insert(target);
	}
	void LevelDisplay()
	{
		strategyChild->level_display();
	};

	void Del(int target)
	{
		strategyChild->del(target);
	};

	void Inorder_Print()
	{
		strategyChild->inorder_print();
	};

	// tree node num
	void NodeNum_Print()
	{
		strategyChild->NodeNum_print();
	};
};
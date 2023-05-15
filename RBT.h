#ifndef REDBLACKTREE
#define REDBLACKTREE
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

//===========红黑树结点的颜色===========
enum RBTreeColor
{
	RED,	//红色
	BLACK	//黑色
};

//===========红黑树的结点===========
template <typename T>
struct TreeNode
{
	T key;	//结点中存储的数据
	RBTreeColor color;	//结点的颜色
	TreeNode<T>* left;	//结点的左孩子
	TreeNode<T>* right;	//结点的右孩子
	TreeNode<T>* parent;	//结点的父亲
	//结点的构造函数
	TreeNode(T x, RBTreeColor _color)
	{
		key = x;
		color = _color;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

//===========红黑树===========
template <typename T>
class RedBlackTree
{
private:
	TreeNode<T>* root;	//根结点
	void printRedBlackTree(TreeNode<T>*& root, std::string indent, bool isLeft);//输出树形图
public:
	RedBlackTree();	//无参构造函数
	RedBlackTree(T x);	//创建一个根结点
	RedBlackTree(TreeNode<T>* _root);	//用一个已有的根结点赋值给根结点
	RedBlackTree(RedBlackTree<T>& _root);	//拷贝构造函数
	RedBlackTree(vector<T> v);	//用一个数组来创建红黑树
	~RedBlackTree();	//析构函数
	vector<T> PerOrderTraverse();	//先序遍历
	vector<T> InOrderTraverse();	//中序遍历
	vector<T> PostOrderTraverse();	//后序遍历
	vector<T> LevelOrderTraverse();	//层序遍历
	void clear();	//清空二叉树
	bool isEmpty();	//判断二叉树是否为空
	bool isBalanced();	//判断是否为平衡二叉树
	int height();	//获取树的高度
	int size();	//获取结点个数
	T maximum();	//获取最大值
	T minimum();	//获取最小值
	TreeNode<T>* search(T e);	//搜索结点
	bool insert(T e);	//插入节点
	bool remove(T e);	//删除结点
	T operator[] (int r);	//重载[]操作符
	RBTreeColor getColor(T e);	//获取结点的颜色
	void PrintRBTree() { this->printRedBlackTree(this->root, "",false); }
};

//===========函数的具体实现===========
/*
	无参构造函数
*/
template <typename T>
RedBlackTree<T>::RedBlackTree()
{
	root = nullptr;
}

//------------------------------------------------------
/*
	有参构造函数
	T x:二叉树根结点的值
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(T x)
{
	root = new TreeNode<T>(x, BLACK);
}

//------------------------------------------------------
/*
	复制一个二叉树到新的内存中
	TreeNode<T>* &_root:被复制的根结点
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* copyBiTree(TreeNode<T>*& root)
{
	if (root)
	{
		TreeNode<T>* another;
		another = new TreeNode<T>(root->key, root->color);
		if (root->left)
			another->left = copyBiTree(root->left);
		if (root->right)
			another->right = copyBiTree(root->right);

		return another;
	}
	else
		return nullptr;
}

//------------------------------------------------------
/*
	用一个已有的根结点赋值给根结点
	TreeNode<T>* _root:已有的根结点
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(TreeNode<T>* _root)
{
	root = nullptr;
	TreeNode<T>* copy = nullptr;
	vector<T> v;
	In(_root, v);
	for (unsigned int i = 0; i < v.size(); i++)
	{
		copy = new TreeNode<T>(v[i], BLACK);
		insertIn(root, copy);
	}
}

//------------------------------------------------------
/*
	拷贝构造函数
	RedBlackTree<T> &_root:被拷贝的红黑树
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree<T>& _root)
{
	root = copyBiTree(_root.root);
}

//------------------------------------------------------
/*
	用一个数组来创建红黑树
	vector<T> v:用来创建红黑树的数组
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(vector<T> v)
{
	root = nullptr;
	TreeNode<T>* node = nullptr;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		node = new TreeNode<T>(v[i], BLACK);
		insertIn(root, node);
	}
}

//------------------------------------------------------
/*
	销毁一个二叉树
	TreeNode<T>* &root:二叉树的根结点
	@Return void
*/
template <typename T>
void destroyBiTree(TreeNode<T>*& root)
{
	if (root)
	{
		TreeNode<T>* left;
		TreeNode<T>* right;
		left = root->left;
		right = root->right;
		delete root;
		root = nullptr;
		if (left)
			destroyBiTree(left);
		if (right)
			destroyBiTree(right);
	}
}

//------------------------------------------------------
/*
	析构函数
*/
template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
	destroyBiTree(root);
}

//------------------------------------------------------
/*
	先序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组
	@Return void
*/
template <typename T>
void Per(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		v.push_back(root->key);
		Per(root->left, v);
		Per(root->right, v);
	}
}

//------------------------------------------------------
/*
	先序遍历,并把遍历结果返回到一个数组上
	@Return vector<T>
*/
template <typename T>
vector<T> RedBlackTree<T>::PerOrderTraverse()
{
	vector<T> v;
	Per(root, v);
	return v;
}

//------------------------------------------------------
/*
	中序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组
	@Return void
*/
template <typename T>
void In(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		In(root->left, v);
		v.push_back(root->key);
		In(root->right, v);
	}
}

//------------------------------------------------------
/*
	中序遍历,并把遍历结果返回到一个数组上
	@Return vector<T>
*/
template <typename T>
vector<T> RedBlackTree<T>::InOrderTraverse()
{
	vector<T> v;
	In(root, v);
	return v;
}

//------------------------------------------------------
/*
	后序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组
	@Return void
*/
template <typename T>
void Post(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		Post(root->left, v);
		Post(root->right, v);
		v.push_back(root->key);
	}
}

//------------------------------------------------------
/*
	后序遍历,并把遍历结果返回到一个数组上
	@Return vector<T>
*/
template <typename T>
vector<T> RedBlackTree<T>::PostOrderTraverse()
{
	vector<T> v;
	Post(root, v);
	return v;
}

//------------------------------------------------------
/*
	层序遍历,并把遍历结果返回到一个数组上
	@Return vector<T>
*/
template <typename T>
vector<T> RedBlackTree<T>::LevelOrderTraverse()
{
	vector<T> v;
	if (!root)
		return v;

	queue<TreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		TreeNode<T>* Node;
		Node = q.front();
		v.push_back(Node->key);
		q.pop();
		if (Node->left)
			q.push(Node->left);
		if (Node->right)
			q.push(Node->right);
	}
	return v;
}

//------------------------------------------------------
/*
	清空二叉树
	@Return void
*/
template <typename T>
void RedBlackTree<T>::clear()
{
	destroyBiTree(root);
}

//------------------------------------------------------
/*
	判断二叉树是否为空
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::isEmpty()
{
	return !root;
}

//------------------------------------------------------
/*
	判断是否为平衡二叉树
	TreeNode<T>* &root:二叉树的根结点
	@Return bool
*/
template <typename T>
bool isBalancedBiTree(TreeNode<T>*& root)
{
	if (!root)
		return true;

	if (!root->left && !root->right)
		return true;
	else if (abs(getHeight(root->left) - getHeight(root->right)) > 1)
		return false;
	else
		return isBalancedBiTree(root->left) && isBalancedBiTree(root->right);
}

//------------------------------------------------------
/*
	判断是否为平衡二叉树
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::isBalanced()
{
	return isBalancedBiTree(root);
}

//------------------------------------------------------
/*
	返回二叉树的高度
	TreeNode<T>* &root:二叉树的根结点
	@Return int
*/
template <typename T>
int getHeight(TreeNode<T>*& root)
{
	if (root)
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;
}

//------------------------------------------------------
/*
	返回二叉树的高度
	@Return int
*/
template <typename T>
int RedBlackTree<T>::height()
{
	return getHeight(root);
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数
	TreeNode<T>* &root:二叉树的根结点
	@Return int
*/
template <typename T>
int getSize(TreeNode<T>*& root)
{
	if (root)
		return 1 + getSize(root->left) + getSize(root->right);
	else
		return 0;
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数
	@Return int
*/
template <typename T>
int RedBlackTree<T>::size()
{
	return getSize(root);
}

//------------------------------------------------------
/*
	返回红黑树中存储最大值的结点
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* getMax(TreeNode<T>*& root)
{
	if (!root)
		return nullptr;

	TreeNode<T>* temp;
	temp = root;
	while (temp->right)
		temp = temp->right;
	return temp;
}

//------------------------------------------------------
/*
	返回红黑树中存储的最大值
	@Return T
*/
template<typename T>
T RedBlackTree<T>::maximum()
{
	if (!root)
		return NULL;

	TreeNode<T>* Maximum;
	Maximum = getMax(root);
	return Maximum->key;
}

//------------------------------------------------------
/*
	返回红黑树中存储最小值的结点
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* getMin(TreeNode<T>*& root)
{
	if (!root)
		return nullptr;

	TreeNode<T>* temp;
	temp = root;
	while (temp->left)
		temp = temp->left;
	return temp;
}

//------------------------------------------------------
/*
	返回红黑树中存储的最小值
	@Return T
*/
template <typename T>
T RedBlackTree<T>::minimum()
{
	if (!root)
		return NULL;

	TreeNode<T>* Minimum;
	Minimum = getMin(root);
	return Minimum->key;
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	TreeNode<T>* &root:红黑树的根结点
	T val:要搜索的值
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* searchIn(TreeNode<T>*& root, T val)
{
	if (root == nullptr)
		return nullptr;

	if (root->key == val)
		return root;
	else
		if (root->key > val)
			return searchIn(root->left, val);
		else
			return searchIn(root->right, val);
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	T e:要搜索的值
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* RedBlackTree<T>::search(T e)
{
	return searchIn(root, e);
}

//------------------------------------------------------
/*
	对红黑树的节点(x)进行左旋转
	TreeNode<T>* &root:要旋转的红黑树根结点
	TreeNode<T>* &x:要旋转的结点
	@Return void
*/
template <typename T>
void leftRotate(TreeNode<T>*& root, TreeNode<T>*& x)
{
	// 设置x的右孩子为y
	TreeNode<T>* y = x->right;

	// 将 "y的左孩子" 设为 "x的右孩子"
	// 如果y的左孩子非空,将 "x" 设为 "y的左孩子的父亲"
	x->right = y->left;
	if (y->left)
		y->left->parent = x;

	// 将 "x的父亲" 设为 "y的父亲"
	y->parent = x->parent;

	if (!x->parent)
		root = y;	// 如果 "x的父亲" 是空节点,则将y设为根节点
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;	// 如果 x 是它父节点的左孩子,则将y设为"x的父节点的左孩子"
		else
			x->parent->right = y;	// 如果 x 是它父节点的右孩子,则将y设为"x的父节点的右孩子"
	}

	// 将 "x" 设为 "y的左孩子"
	y->left = x;
	// 将 "x的父节点" 设为 "y"
	x->parent = y;
}

//------------------------------------------------------
/*
	对红黑树的节点(y)进行右旋转
	TreeNode<T>* &root:要旋转的红黑树根结点
	TreeNode<T>* &x:要旋转的结点
	@Return void
*/
template <typename T>
void rightRotate(TreeNode<T>*& root, TreeNode<T>*& y)
{
	// 设置x是当前节点的左孩子
	TreeNode<T>* x = y->left;

	// 将 "x的右孩子" 设为 "y的左孩子"
	// 如果 "x的右孩子" 不为空的话,将 "y" 设为 "x的右孩子的父亲"
	y->left = x->right;
	if (x->right)
		x->right->parent = y;

	// 将 "y的父亲" 设为 "x的父亲"
	x->parent = y->parent;

	if (!y->parent)
		root = x;	// 如果 "y的父亲" 是空节点,则将x设为根节点
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;	// 如果 y 是它父节点的右孩子，则将x设为"y的父节点的右孩子"
		else
			y->parent->left = x;	// 如果 y 是它父节点的左孩子，则将x设为"y的父节点的左孩子"
	}

	// 将 "y" 设为 "x的右孩子"
	x->right = y;
	// 将 "y的父节点" 设为 "x"
	y->parent = x;
}

//------------------------------------------------------
/*
	红黑树插入修正函数
	TreeNode<T>* &root:插入的红黑树根结点
	TreeNode<T>* &node:被插入的结点
	@Return void
*/
template <typename T>
void insertFixUp(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* _parent = node->parent;
	TreeNode<T>* _gparent;

	// 若父节点存在,并且父节点的颜色是红色
	while (_parent && _parent->color == RED)
	{
		_gparent = _parent->parent;

		//若"父节点"是"祖父节点的左孩子"
		if (_parent == _gparent->left)
		{
			TreeNode<T>* uncle = _gparent->right;
			if (uncle && uncle->color == RED)
			{
				//叔叔节点是红色的情况
				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				_parent = node->parent;
				continue;
			}
			if (node == node->parent->right)
			{
				//叔叔是黑色,且当前节点是右孩子的情况
				leftRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			//叔叔是黑色,且当前节点是左孩子的情况
			_parent->color = BLACK;
			_gparent->color = RED;
			rightRotate(root, _gparent);
		}
		//若"z的父节点"是"z的祖父节点的右孩子"
		else
		{
			TreeNode<T>* uncle = _gparent->left;
			if (uncle && uncle->color == RED)
			{
				//叔叔节点是红色的情况
				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				_parent = node->parent;
				continue;
			}
			if (node->parent->left == node)
			{
				//叔叔是黑色,且当前节点是左孩子的情况
				rightRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			//叔叔是黑色,且当前节点是右孩子的情况
			_parent->color = BLACK;
			_gparent->color = RED;
			leftRotate(root, _gparent);
		}
	}
	//将根节点设为黑色
	root->color = BLACK;
}

//------------------------------------------------------
/*
	将结点插入到红黑树中
	TreeNode<T>* &root:插入的红黑树根结点
	TreeNode<T>* &node:被插入的结点
	&Return void
*/
template <typename T>
void insertIn(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* y = nullptr;
	TreeNode<T>* x = root;

	//1.将红黑树当作一颗二叉查找树,将节点添加到二叉查找树中
	while (x)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	node->parent = y;
	if (y)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	//2.设置节点的颜色为红色
	node->color = RED;

	//3.将它重新修正为一颗红黑树
	insertFixUp(root, node);
}

//------------------------------------------------------
/*
	插入结点,若插入成功则返回true,失败则返回false
	T e:要插入的值
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::insert(T e)
{
	if (search(e))
		return false;

	TreeNode<T>* node;
	node = new TreeNode<T>(e, RED);

	insertIn(root, node);
	return true;
}

//------------------------------------------------------
/*
	红黑树删除修正函数
	TreeNode<T>* &root:红黑树的根结点
	TreeNode<T>* &node:被删除的结点
	TreeNode<T>* &parent:父结点
	@Return void
*/
template <typename T>
void removeFixUp(TreeNode<T>*& root, TreeNode<T>*& node, TreeNode<T>*& parent)
{
	while ((!node || node->color == BLACK) && node != root)
	{
		if (parent->left == node)
		{
			TreeNode<T>* other = parent->right;
			if (other->color == RED)
			{
				//x的兄弟w是红色的情况
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//x的兄弟w是黑色,且w的俩个孩子也都是黑色的情况
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color == BLACK)
				{
					//x的兄弟w是黑色的,并且w的左孩子是红色,右孩子为黑色的情况
					other->left->color = BLACK;
					other->color = RED;
					rightRotate(root, other);
					other = parent->right;
				}
				//x的兄弟w是黑色的,并且w的右孩子是红色的,左孩子任意颜色的情况
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			TreeNode<T>* other = parent->left;
			if (other->color == RED)
			{
				//x的兄弟w是红色的情况
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//x的兄弟w是黑色,且w的俩个孩子也都是黑色的情况
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					//x的兄弟w是黑色的,并且w的左孩子是红色,右孩子为黑色的情况
					other->right->color = BLACK;
					other->color = RED;
					leftRotate(root, other);
					other = parent->left;
				}
				//x的兄弟w是黑色的,并且w的右孩子是红色的,左孩子任意颜色的情况
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if (node)
		node->color = BLACK;
}

//------------------------------------------------------
/*
	删除红黑树中的结点
	TreeNode<T>* &root:红黑树的根结点
	TreeNode<T>* &node:被删除的结点
	@Return void
*/
template <typename T>
void removeAt(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* child;
	TreeNode<T>* parent;
	RBTreeColor color;

	//被删除节点的"左右孩子都不为空"的情况
	if (node->left && node->right)
	{
		//被删节点的后继节点,称为"取代节点"
		//用它来取代"被删节点"的位置,然后再将"被删节点"去掉
		TreeNode<T>* replace = node;

		//获取后继节点
		replace = replace->right;
		while (replace->left)
			replace = replace->left;

		//"node节点"不是根节点(只有根节点不存在父节点)
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			//"node节点"是根节点,更新根节点
			root = replace;

		//child是"取代节点"的右孩子,也是需要"调整的节点"
		//"取代节点"肯定不存在左孩子,因为它是一个后继节点
		child = replace->right;
		parent = replace->parent;
		//保存"取代节点"的颜色
		color = replace->color;

		//"被删除节点"是"它的后继节点的父节点"
		if (parent == node)
			parent = replace;
		else
		{
			//child不为空
			if (child)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		node = nullptr;
		return;
	}

	if (node->left)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	//保存"取代节点"的颜色
	color = node->color;
	if (child)
		child->parent = parent;

	//"node节点"不是根节点
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
	node = nullptr;
}

//------------------------------------------------------
/*
	删除结点,若删除成功则返回true,失败则返回false
	T e:要删除的值
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::remove(T e)
{
	TreeNode<T>* node = searchIn(root, e);
	if (node)
	{
		removeAt(root, node);
		return true;
	}
	return false;
}

//------------------------------------------------------
/*
	重载[]操作符,按中序遍历输出
	int r:索引
	@Return T
*/
template <typename T>
T RedBlackTree<T>::operator[] (int r)
{
	if (r < 0 || r >= size())
		return NULL;

	vector<T> v = InOrderTraverse();
	return v[r];
}

//------------------------------------------------------
/*
	获取红黑树结点的颜色
	T e:要获取颜色的结点
	@Return RBTreeColor
*/
template <typename T>
RBTreeColor RedBlackTree<T>::getColor(T e)
{
	TreeNode<T>* node = searchIn(root, e);
	if (node)
		return node->color;
	else
		return BLACK;
}

//------------------------------------------------------
/*
	重载<<操作符,按中序遍历输出红黑树结点的值和颜色
	ostream &os:输出流
	RedBlackTree<T> &m:要输出的红黑树
	@Return ostream
*/
template <typename T>
ostream& operator<<(ostream& os, RedBlackTree<T>& m)
{
	vector<T> v = m.InOrderTraverse();
	if (v.size() == 0)
		return os;

	if (v.size() == 1)
	{
		os << "(" << v.front();
		if (m.getColor(v.front()) == RED)
			os << ",红)";
		else
			os << ",黑)";
		return os;
	}
	else
	{
		for (unsigned int i = 0; i < v.size() - 1; i++)
		{
			os << "(" << v[i];
			if (m.getColor(v[i]) == RED)
				os << ",红) ";
			else
				os << ",黑) ";
		}
		os << "(" << v.back();
		if (m.getColor(v.back()) == RED)
			os << ",红)";
		else
			os << ",黑)";
		return os;
	}
}
template<typename T>
void  RedBlackTree<T>::printRedBlackTree(TreeNode<T>*&root,string indent, bool isLeft)
{
	if (root == nullptr) {
		return;
	}
	std::cout << indent;
	if (isLeft) {
		std::cout << "├─ ";
	}
	else {
		std::cout << "└─ ";
	}

	std::string colorLabel;
	if (root->color == RED) {
		colorLabel = "(R) ";
	}
	else {
		colorLabel = "(B) ";
	}

	std::cout << colorLabel << root->key << std::endl;

	// 递归打印左子树和右子树
	std::string childIndent = indent;
	if (isLeft) {
		childIndent += "│  ";
	}
	else {
		childIndent += "   ";
	}

	printRedBlackTree(root->left, childIndent, true);
	printRedBlackTree(root->right, childIndent, false);
}
#endif // !REDBLACKTREE	
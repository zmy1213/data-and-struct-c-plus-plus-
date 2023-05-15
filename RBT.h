#ifndef REDBLACKTREE
#define REDBLACKTREE
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

//===========�����������ɫ===========
enum RBTreeColor
{
	RED,	//��ɫ
	BLACK	//��ɫ
};

//===========������Ľ��===========
template <typename T>
struct TreeNode
{
	T key;	//����д洢������
	RBTreeColor color;	//������ɫ
	TreeNode<T>* left;	//��������
	TreeNode<T>* right;	//�����Һ���
	TreeNode<T>* parent;	//���ĸ���
	//���Ĺ��캯��
	TreeNode(T x, RBTreeColor _color)
	{
		key = x;
		color = _color;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

//===========�����===========
template <typename T>
class RedBlackTree
{
private:
	TreeNode<T>* root;	//�����
	void printRedBlackTree(TreeNode<T>*& root, std::string indent, bool isLeft);//�������ͼ
public:
	RedBlackTree();	//�޲ι��캯��
	RedBlackTree(T x);	//����һ�������
	RedBlackTree(TreeNode<T>* _root);	//��һ�����еĸ���㸳ֵ�������
	RedBlackTree(RedBlackTree<T>& _root);	//�������캯��
	RedBlackTree(vector<T> v);	//��һ�����������������
	~RedBlackTree();	//��������
	vector<T> PerOrderTraverse();	//�������
	vector<T> InOrderTraverse();	//�������
	vector<T> PostOrderTraverse();	//�������
	vector<T> LevelOrderTraverse();	//�������
	void clear();	//��ն�����
	bool isEmpty();	//�ж϶������Ƿ�Ϊ��
	bool isBalanced();	//�ж��Ƿ�Ϊƽ�������
	int height();	//��ȡ���ĸ߶�
	int size();	//��ȡ������
	T maximum();	//��ȡ���ֵ
	T minimum();	//��ȡ��Сֵ
	TreeNode<T>* search(T e);	//�������
	bool insert(T e);	//����ڵ�
	bool remove(T e);	//ɾ�����
	T operator[] (int r);	//����[]������
	RBTreeColor getColor(T e);	//��ȡ������ɫ
	void PrintRBTree() { this->printRedBlackTree(this->root, "",false); }
};

//===========�����ľ���ʵ��===========
/*
	�޲ι��캯��
*/
template <typename T>
RedBlackTree<T>::RedBlackTree()
{
	root = nullptr;
}

//------------------------------------------------------
/*
	�вι��캯��
	T x:������������ֵ
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(T x)
{
	root = new TreeNode<T>(x, BLACK);
}

//------------------------------------------------------
/*
	����һ�����������µ��ڴ���
	TreeNode<T>* &_root:�����Ƶĸ����
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
	��һ�����еĸ���㸳ֵ�������
	TreeNode<T>* _root:���еĸ����
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
	�������캯��
	RedBlackTree<T> &_root:�������ĺ����
*/
template <typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree<T>& _root)
{
	root = copyBiTree(_root.root);
}

//------------------------------------------------------
/*
	��һ�����������������
	vector<T> v:�������������������
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
	����һ��������
	TreeNode<T>* &root:�������ĸ����
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
	��������
*/
template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
	destroyBiTree(root);
}

//------------------------------------------------------
/*
	�������
	TreeNode<T>* &root:�������ĸ����
	vector<T> &v:�洢�������������
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
	�������,���ѱ���������ص�һ��������
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
	�������
	TreeNode<T>* &root:�������ĸ����
	vector<T> &v:�洢�������������
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
	�������,���ѱ���������ص�һ��������
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
	�������
	TreeNode<T>* &root:�������ĸ����
	vector<T> &v:�洢�������������
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
	�������,���ѱ���������ص�һ��������
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
	�������,���ѱ���������ص�һ��������
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
	��ն�����
	@Return void
*/
template <typename T>
void RedBlackTree<T>::clear()
{
	destroyBiTree(root);
}

//------------------------------------------------------
/*
	�ж϶������Ƿ�Ϊ��
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::isEmpty()
{
	return !root;
}

//------------------------------------------------------
/*
	�ж��Ƿ�Ϊƽ�������
	TreeNode<T>* &root:�������ĸ����
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
	�ж��Ƿ�Ϊƽ�������
	@Return bool
*/
template <typename T>
bool RedBlackTree<T>::isBalanced()
{
	return isBalancedBiTree(root);
}

//------------------------------------------------------
/*
	���ض������ĸ߶�
	TreeNode<T>* &root:�������ĸ����
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
	���ض������ĸ߶�
	@Return int
*/
template <typename T>
int RedBlackTree<T>::height()
{
	return getHeight(root);
}

//------------------------------------------------------
/*
	���ض������н��ĸ���
	TreeNode<T>* &root:�������ĸ����
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
	���ض������н��ĸ���
	@Return int
*/
template <typename T>
int RedBlackTree<T>::size()
{
	return getSize(root);
}

//------------------------------------------------------
/*
	���غ�����д洢���ֵ�Ľ��
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
	���غ�����д洢�����ֵ
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
	���غ�����д洢��Сֵ�Ľ��
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
	���غ�����д洢����Сֵ
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
	�������,���ҵ��ͷ��ظý��,��û�ҵ��ͷ���nullptr
	TreeNode<T>* &root:������ĸ����
	T val:Ҫ������ֵ
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
	�������,���ҵ��ͷ��ظý��,��û�ҵ��ͷ���nullptr
	T e:Ҫ������ֵ
	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* RedBlackTree<T>::search(T e)
{
	return searchIn(root, e);
}

//------------------------------------------------------
/*
	�Ժ�����Ľڵ�(x)��������ת
	TreeNode<T>* &root:Ҫ��ת�ĺ���������
	TreeNode<T>* &x:Ҫ��ת�Ľ��
	@Return void
*/
template <typename T>
void leftRotate(TreeNode<T>*& root, TreeNode<T>*& x)
{
	// ����x���Һ���Ϊy
	TreeNode<T>* y = x->right;

	// �� "y������" ��Ϊ "x���Һ���"
	// ���y�����ӷǿ�,�� "x" ��Ϊ "y�����ӵĸ���"
	x->right = y->left;
	if (y->left)
		y->left->parent = x;

	// �� "x�ĸ���" ��Ϊ "y�ĸ���"
	y->parent = x->parent;

	if (!x->parent)
		root = y;	// ��� "x�ĸ���" �ǿսڵ�,��y��Ϊ���ڵ�
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;	// ��� x �������ڵ������,��y��Ϊ"x�ĸ��ڵ������"
		else
			x->parent->right = y;	// ��� x �������ڵ���Һ���,��y��Ϊ"x�ĸ��ڵ���Һ���"
	}

	// �� "x" ��Ϊ "y������"
	y->left = x;
	// �� "x�ĸ��ڵ�" ��Ϊ "y"
	x->parent = y;
}

//------------------------------------------------------
/*
	�Ժ�����Ľڵ�(y)��������ת
	TreeNode<T>* &root:Ҫ��ת�ĺ���������
	TreeNode<T>* &x:Ҫ��ת�Ľ��
	@Return void
*/
template <typename T>
void rightRotate(TreeNode<T>*& root, TreeNode<T>*& y)
{
	// ����x�ǵ�ǰ�ڵ������
	TreeNode<T>* x = y->left;

	// �� "x���Һ���" ��Ϊ "y������"
	// ��� "x���Һ���" ��Ϊ�յĻ�,�� "y" ��Ϊ "x���Һ��ӵĸ���"
	y->left = x->right;
	if (x->right)
		x->right->parent = y;

	// �� "y�ĸ���" ��Ϊ "x�ĸ���"
	x->parent = y->parent;

	if (!y->parent)
		root = x;	// ��� "y�ĸ���" �ǿսڵ�,��x��Ϊ���ڵ�
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;	// ��� y �������ڵ���Һ��ӣ���x��Ϊ"y�ĸ��ڵ���Һ���"
		else
			y->parent->left = x;	// ��� y �������ڵ�����ӣ���x��Ϊ"y�ĸ��ڵ������"
	}

	// �� "y" ��Ϊ "x���Һ���"
	x->right = y;
	// �� "y�ĸ��ڵ�" ��Ϊ "x"
	y->parent = x;
}

//------------------------------------------------------
/*
	�����������������
	TreeNode<T>* &root:����ĺ���������
	TreeNode<T>* &node:������Ľ��
	@Return void
*/
template <typename T>
void insertFixUp(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* _parent = node->parent;
	TreeNode<T>* _gparent;

	// �����ڵ����,���Ҹ��ڵ����ɫ�Ǻ�ɫ
	while (_parent && _parent->color == RED)
	{
		_gparent = _parent->parent;

		//��"���ڵ�"��"�游�ڵ������"
		if (_parent == _gparent->left)
		{
			TreeNode<T>* uncle = _gparent->right;
			if (uncle && uncle->color == RED)
			{
				//����ڵ��Ǻ�ɫ�����
				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				_parent = node->parent;
				continue;
			}
			if (node == node->parent->right)
			{
				//�����Ǻ�ɫ,�ҵ�ǰ�ڵ����Һ��ӵ����
				leftRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			//�����Ǻ�ɫ,�ҵ�ǰ�ڵ������ӵ����
			_parent->color = BLACK;
			_gparent->color = RED;
			rightRotate(root, _gparent);
		}
		//��"z�ĸ��ڵ�"��"z���游�ڵ���Һ���"
		else
		{
			TreeNode<T>* uncle = _gparent->left;
			if (uncle && uncle->color == RED)
			{
				//����ڵ��Ǻ�ɫ�����
				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				_parent = node->parent;
				continue;
			}
			if (node->parent->left == node)
			{
				//�����Ǻ�ɫ,�ҵ�ǰ�ڵ������ӵ����
				rightRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			//�����Ǻ�ɫ,�ҵ�ǰ�ڵ����Һ��ӵ����
			_parent->color = BLACK;
			_gparent->color = RED;
			leftRotate(root, _gparent);
		}
	}
	//�����ڵ���Ϊ��ɫ
	root->color = BLACK;
}

//------------------------------------------------------
/*
	�������뵽�������
	TreeNode<T>* &root:����ĺ���������
	TreeNode<T>* &node:������Ľ��
	&Return void
*/
template <typename T>
void insertIn(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* y = nullptr;
	TreeNode<T>* x = root;

	//1.�����������һ�Ŷ��������,���ڵ���ӵ������������
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

	//2.���ýڵ����ɫΪ��ɫ
	node->color = RED;

	//3.������������Ϊһ�ź����
	insertFixUp(root, node);
}

//------------------------------------------------------
/*
	������,������ɹ��򷵻�true,ʧ���򷵻�false
	T e:Ҫ�����ֵ
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
	�����ɾ����������
	TreeNode<T>* &root:������ĸ����
	TreeNode<T>* &node:��ɾ���Ľ��
	TreeNode<T>* &parent:�����
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
				//x���ֵ�w�Ǻ�ɫ�����
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//x���ֵ�w�Ǻ�ɫ,��w����������Ҳ���Ǻ�ɫ�����
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color == BLACK)
				{
					//x���ֵ�w�Ǻ�ɫ��,����w�������Ǻ�ɫ,�Һ���Ϊ��ɫ�����
					other->left->color = BLACK;
					other->color = RED;
					rightRotate(root, other);
					other = parent->right;
				}
				//x���ֵ�w�Ǻ�ɫ��,����w���Һ����Ǻ�ɫ��,����������ɫ�����
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
				//x���ֵ�w�Ǻ�ɫ�����
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				//x���ֵ�w�Ǻ�ɫ,��w����������Ҳ���Ǻ�ɫ�����
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					//x���ֵ�w�Ǻ�ɫ��,����w�������Ǻ�ɫ,�Һ���Ϊ��ɫ�����
					other->right->color = BLACK;
					other->color = RED;
					leftRotate(root, other);
					other = parent->left;
				}
				//x���ֵ�w�Ǻ�ɫ��,����w���Һ����Ǻ�ɫ��,����������ɫ�����
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
	ɾ��������еĽ��
	TreeNode<T>* &root:������ĸ����
	TreeNode<T>* &node:��ɾ���Ľ��
	@Return void
*/
template <typename T>
void removeAt(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* child;
	TreeNode<T>* parent;
	RBTreeColor color;

	//��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�����
	if (node->left && node->right)
	{
		//��ɾ�ڵ�ĺ�̽ڵ�,��Ϊ"ȡ���ڵ�"
		//������ȡ��"��ɾ�ڵ�"��λ��,Ȼ���ٽ�"��ɾ�ڵ�"ȥ��
		TreeNode<T>* replace = node;

		//��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left)
			replace = replace->left;

		//"node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			//"node�ڵ�"�Ǹ��ڵ�,���¸��ڵ�
			root = replace;

		//child��"ȡ���ڵ�"���Һ���,Ҳ����Ҫ"�����Ľڵ�"
		//"ȡ���ڵ�"�϶�����������,��Ϊ����һ����̽ڵ�
		child = replace->right;
		parent = replace->parent;
		//����"ȡ���ڵ�"����ɫ
		color = replace->color;

		//"��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
			parent = replace;
		else
		{
			//child��Ϊ��
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
	//����"ȡ���ڵ�"����ɫ
	color = node->color;
	if (child)
		child->parent = parent;

	//"node�ڵ�"���Ǹ��ڵ�
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
	ɾ�����,��ɾ���ɹ��򷵻�true,ʧ���򷵻�false
	T e:Ҫɾ����ֵ
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
	����[]������,������������
	int r:����
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
	��ȡ�����������ɫ
	T e:Ҫ��ȡ��ɫ�Ľ��
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
	����<<������,���������������������ֵ����ɫ
	ostream &os:�����
	RedBlackTree<T> &m:Ҫ����ĺ����
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
			os << ",��)";
		else
			os << ",��)";
		return os;
	}
	else
	{
		for (unsigned int i = 0; i < v.size() - 1; i++)
		{
			os << "(" << v[i];
			if (m.getColor(v[i]) == RED)
				os << ",��) ";
			else
				os << ",��) ";
		}
		os << "(" << v.back();
		if (m.getColor(v.back()) == RED)
			os << ",��)";
		else
			os << ",��)";
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
		std::cout << "���� ";
	}
	else {
		std::cout << "���� ";
	}

	std::string colorLabel;
	if (root->color == RED) {
		colorLabel = "(R) ";
	}
	else {
		colorLabel = "(B) ";
	}

	std::cout << colorLabel << root->key << std::endl;

	// �ݹ��ӡ��������������
	std::string childIndent = indent;
	if (isLeft) {
		childIndent += "��  ";
	}
	else {
		childIndent += "   ";
	}

	printRedBlackTree(root->left, childIndent, true);
	printRedBlackTree(root->right, childIndent, false);
}
#endif // !REDBLACKTREE	
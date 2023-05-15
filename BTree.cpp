#include "BTree.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#define WIN32
#ifdef WIN32
#include <io.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

btree_node* BTree::btree_node_new()
{
	btree_node* node = new btree_node;
	if (NULL == node) {
		return NULL;
	}

	for (int i = 0; i < 2 * M - 1; i++) {
		node->k[i] = 0;
	}

	for (int i = 0; i < 2 * M; i++) {
		node->p[i] = NULL;
	}

	node->num = 0;
	node->is_leaf = true;     //Ĭ��ΪҶ�� 

	return node;
}

btree_node* BTree::btree_create()
{
	btree_node* node = btree_node_new();
	if (NULL == node) {
		return NULL;
	}
	return node;
}

int BTree::btree_split_child(btree_node* parent, int pos, btree_node* child)
{
	btree_node* new_child = btree_node_new();
	if (NULL == new_child) {
		return -1;
	}
	// �½ڵ��is_leaf��child��ͬ��key�ĸ���ΪM-1
	new_child->is_leaf = child->is_leaf;
	new_child->num = M - 1;

	// ��child��벿�ֵ�key�������½ڵ�
	for (int i = 0; i < M - 1; i++) {
		new_child->k[i] = child->k[i + M];
	}

	// ���child����Ҷ�ӣ�����Ҫ��ָ�뿽��ȥ��ָ��Ƚڵ��1
	if (false == new_child->is_leaf) {
		for (int i = 0; i < M; i++) {
			new_child->p[i] = child->p[i + M];
		}
	}

	child->num = M - 1;

	// child���м�ڵ���Ҫ����parent��pos��������parent��key��pointer
	for (int i = parent->num; i > pos; i--) {
		parent->p[i + 1] = parent->p[i];
	}
	parent->p[pos + 1] = new_child;

	for (int i = parent->num - 1; i >= pos; i--) {
		parent->k[i + 1] = parent->k[i];
	}
	parent->k[pos] = child->k[M - 1];

	parent->num += 1;
	return 0;
}

// ִ�иò���ʱ��node->num < 2M-1 
void BTree::btree_insert_nonfull(btree_node* node, int target)
{
	if (1 == node->is_leaf) {
		// �����Ҷ�����ҵ���ֱ��ɾ��
		int pos = node->num;
		while (pos >= 1 && target < node->k[pos - 1]) {
			node->k[pos] = node->k[pos - 1];
			pos--;
		}

		node->k[pos] = target;
		node->num += 1;
		btree_node_num += 1;

	}
	else {
		// ���Ų���·���½�
		int pos = node->num;
		while (pos > 0 && target < node->k[pos - 1]) {
			pos--;
		}

		if (2 * M - 1 == node->p[pos]->num) {
			// ���·���������ڵ������
			btree_split_child(node, pos, node->p[pos]);
			if (target > node->k[pos]) {
				pos++;
			}
		}

		btree_insert_nonfull(node->p[pos], target);
	}
}

//�������
btree_node* BTree::btree_insert(btree_node* root, int target)
{
	if (NULL == root) {
		return NULL;
	}

	// �Ը��ڵ�����⴦������������ģ�Ψһʹ�������ߵ�����
	// ������һ���µ�
	if (2 * M - 1 == root->num) {
		btree_node* node = btree_node_new();
		if (NULL == node) {
			return root;
		}

		node->is_leaf = 0;
		node->p[0] = root;
		btree_split_child(node, 0, root);
		btree_insert_nonfull(node, target);
		return node;
	}
	else {
		btree_insert_nonfull(root, target);
		return root;
	}
}

// ��y��root->k[pos], z�ϲ���y�ڵ㣬���ͷ�z�ڵ㣬y,z����M-1���ڵ�
void BTree::btree_merge_child(btree_node* root, int pos, btree_node* y, btree_node* z)
{
	// ��z�нڵ㿽����y�ĺ�벿��
	y->num = 2 * M - 1;
	for (int i = M; i < 2 * M - 1; i++) {
		y->k[i] = z->k[i - M];
	}
	y->k[M - 1] = root->k[pos];// k[pos]�½�Ϊy���м�ڵ�

	// ���z��Ҷ�ӣ���Ҫ����pointer
	if (false == z->is_leaf) {
		for (int i = M; i < 2 * M; i++) {
			y->p[i] = z->p[i - M];
		}
	}

	// k[pos]�½���y�У�����key��pointer
	for (int j = pos + 1; j < root->num; j++) {
		root->k[j - 1] = root->k[j];
		root->p[j] = root->p[j + 1];
	}

	root->num -= 1;
	free(z);
}

/************  ɾ������   **************
*
��ɾ��B���ڵ�ʱ��Ϊ�˱�����ݣ���������Ҫ�ϲ��Ľڵ�ʱ������ִ�кϲ���B����ɾ���㷨���£���root��Ҷ�ӽڵ㰴��search���ɱ�����
��1��  ���target��Ҷ�ڵ�x�У���ֱ�Ӵ�x��ɾ��target�������2���ͣ�3���ᱣ֤����Ҷ�ӽڵ��ҵ�targetʱ���϶��ܽ�ڵ��ϲ��ɹ����������𸸽ڵ�Ĺؼ��ָ�������t-1��
��2��  ���target�ڷ�֧�ڵ�x�У�
��a��  ���x�����֧�ڵ�y���ٰ���t���ؼ��֣����ҳ�y�����ҵĹؼ���prev�����滻target������y�еݹ�ɾ��prev��
��b��  ���x���ҷ�֧�ڵ�z���ٰ���t���ؼ��֣����ҳ�z������Ĺؼ���next�����滻target������z�еݹ�ɾ��next��
��c��  �������y��z��ֻ��t-1���ؼ��֣���targe��z�ϲ���y�У�ʹ��y��2t-1���ؼ��֣��ٴ�y�еݹ�ɾ��target��
��3��  ����ؼ��ֲ��ڷ�֧�ڵ�x�У����Ȼ��x��ĳ����֧�ڵ�p[i]�У����p[i]�ڵ�ֻ��t-1���ؼ��֡�
��a��  ���p[i-1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���p[i]�У���p[i-1]�����ڵ�������x�С�
��b��  ���p[i+1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���p[i]�У���p[i+1]����С�ؼ���������x����
��c��  ���p[i-1]��p[i+1]��ӵ��t-1���ؼ��֣���p[i]������һ���ֵܺϲ�����x��һ���ؼ��ֽ����ϲ��Ľڵ��У���Ϊ�м�ؼ��֡�
*
*/

// ɾ�����
btree_node* BTree::btree_delete(btree_node* root, int target)
{
	// ���⴦������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
	// ����Ψһ�ܽ������ߵ�����
	if (1 == root->num) {
		btree_node* y = root->p[0];
		btree_node* z = root->p[1];
		if (NULL != y && NULL != z &&
			M - 1 == y->num && M - 1 == z->num) {
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;
		}
		else {
			btree_delete_nonone(root, target);
			return root;
		}
	}
	else {
		btree_delete_nonone(root, target);
		return root;
	}
}

// root�����и�t���ؼ��֣���֤�������
void BTree::btree_delete_nonone(btree_node* root, int target)
{
	if (true == root->is_leaf) {
		// �����Ҷ�ӽڵ㣬ֱ��ɾ��
		int i = 0;
		while (i < root->num && target > root->k[i]) i++;
		if (target == root->k[i]) {
			for (int j = i + 1; j < 2 * M - 1; j++) {
				root->k[j - 1] = root->k[j];
			}
			root->num -= 1;

			btree_node_num -= 1;

		}
		else {
			printf("target not found\n");
		}
	}
	else {
		int i = 0;
		btree_node* y = NULL, * z = NULL;
		while (i < root->num && target > root->k[i]) i++;
		if (i < root->num && target == root->k[i]) {
			// ����ڷ�֧�ڵ��ҵ�target
			y = root->p[i];
			z = root->p[i + 1];
			if (y->num > M - 1) {
				// ������֧�ؼ��ֶ���M-1�����ҵ����֧�����ҽڵ�prev���滻target
				// �������֧�еݹ�ɾ��prev,���2��a)
				int pre = btree_search_predecessor(y);
				root->k[i] = pre;
				btree_delete_nonone(y, pre);
			}
			else if (z->num > M - 1) {
				// ����ҷ�֧�ؼ��ֶ���M-1�����ҵ��ҷ�֧������ڵ�next���滻target
				// �����ҷ�֧�еݹ�ɾ��next,���2(b)
				int next = btree_search_successor(z);
				root->k[i] = next;
				btree_delete_nonone(z, next);
			}
			else {
				// ������֧�ڵ�����ΪM-1����ϲ���y������y�еݹ�ɾ��target,���2(c)
				btree_merge_child(root, i, y, z);
				btree_delete(y, target);
			}
		}
		else {
			// �ڷ�֧û���ҵ����϶��ڷ�֧���ӽڵ���
			y = root->p[i];
			if (i < root->num) {
				z = root->p[i + 1];
			}
			btree_node* p = NULL;
			if (i > 0) {
				p = root->p[i - 1];
			}

			if (y->num == M - 1) {
				if (i > 0 && p->num > M - 1) {
					// ���ڽӽڵ�ؼ��ָ�������M-1
					//���3(a)
					btree_shift_to_right_child(root, i - 1, p, y);
				}
				else if (i < root->num && z->num > M - 1) {
					// ���ڽӽڵ�ؼ��ָ�������M-1
					// ���3(b)
					btree_shift_to_left_child(root, i, y, z);
				}
				else if (i > 0) {
					// ���3��c)
					btree_merge_child(root, i - 1, p, y); // note
					y = p;
				}
				else {
					// ���3(c)
					btree_merge_child(root, i, y, z);
				}
				btree_delete_nonone(y, target);
			}
			else {
				btree_delete_nonone(y, target);
			}
		}

	}
}

//Ѱ��rightmost����rootΪ�������ؼ���
int BTree::btree_search_predecessor(btree_node* root)
{
	btree_node* y = root;
	while (false == y->is_leaf) {
		y = y->p[y->num];
	}
	return y->k[y->num - 1];
}

// Ѱ��leftmost����rootΪ������С�ؼ���
int BTree::btree_search_successor(btree_node* root)
{
	btree_node* z = root;
	while (false == z->is_leaf) {
		z = z->p[0];
	}
	return z->k[0];
}

// z��y��ڵ㣬��root->k[pos]�½���z����y�����ؼ���������root��pos��
void BTree::btree_shift_to_right_child(btree_node* root, int pos,
	btree_node* y, btree_node* z)
{
	z->num += 1;
	for (int i = z->num - 1; i > 0; i--) {
		z->k[i] = z->k[i - 1];
	}
	z->k[0] = root->k[pos];
	root->k[pos] = y->k[y->num - 1];

	if (false == z->is_leaf) {
		for (int i = z->num; i > 0; i--) {
			z->p[i] = z->p[i - 1];
		}
		z->p[0] = y->p[y->num];
	}

	y->num -= 1;
}

// y���ڵ㣬��root->k[pos]�½���y����z����С�ؼ���������root��pos��
void BTree::btree_shift_to_left_child(btree_node* root, int pos,
	btree_node* y, btree_node* z)
{
	y->num += 1;
	y->k[y->num - 1] = root->k[pos];
	root->k[pos] = z->k[0];

	for (int j = 1; j < z->num; j++) {
		z->k[j - 1] = z->k[j];
	}

	if (false == z->is_leaf) {
		y->p[y->num] = z->p[0];
		for (int j = 1; j <= z->num; j++) {
			z->p[j - 1] = z->p[j];
		}
	}

	z->num -= 1;
}

void BTree::btree_inorder_print(btree_node* root)
{
	if (NULL != root) {
		btree_inorder_print(root->p[0]);
		for (int i = 0; i < root->num; i++) {
			printf("%d ", root->k[i]);
			btree_inorder_print(root->p[i + 1]);
		}
	}
}

void BTree::btree_level_display(btree_node* root)
{
	// just for simplicty, can't exceed 200 nodes in the tree
	btree_node* queue[200] = { NULL };
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		btree_node* node = queue[front++];

		printf("[");
		for (int i = 0; i < node->num; i++) {
			printf("%d ", node->k[i]);
		}
		printf("]");

		for (int i = 0; i <= node->num; i++) {
			if (NULL != node->p[i]) {
				queue[rear++] = node->p[i];
			}
		}
	}
	printf("\n");
}

void BTree::Save(btree_node* root)
{
	/*
	storage_struct ss;

	// malloc len space
	ss.len = btree_node_num;
	ss.snode = (storage_node *)malloc(sizeof(storage_node)*ss.len);

	ss.snode[0].bnode = *root;
	for(int i=1;i<ss.len;i++)
	{
		btree_node *node = btree_node_new();
		if(NULL == node) {
			return;
		}
	}

//	fwrite(&ss,sizeof(ss),1,pfile);
*/
}

BTree::BTree(void)
{
	// ���ж��ļ��Ƿ����
	// windows�£���io.h�ļ���linux���� unistd.h�ļ� 
	// int access(const char *pathname, int mode);
	if (-1 == _access("define.Bdb", _A_NORMAL))
	{
		// ������ ,���� 
	//   	pfile = fopen("bstree.b","w");
		roots = btree_create();
	}
	else
	{
		//	   	pfile = fopen("bstree.b","r+");
		roots = btree_create();
		//	   	fread(roots,sizeof(roots),1,pfile);
	}

}


BTree::~BTree(void)
{
	//	fclose(pfile); 
}
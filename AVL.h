#ifndef _BALANCEBITREE_H_
#define _BALANCEBITREE_H_
#include <iostream>
#include <cmath>

using namespace std;

template< class ElementType>
struct Node {
    ElementType data;
    struct Node* lChild;
    struct Node* rChild;
    int balanceFctor;           //平衡因子
};
template< class ElementType>
class BalanceBiTree {
public:
    BalanceBiTree(Node<ElementType>*& T);                       //初始化
    static void menu();                                          //菜单
    void destory(Node<ElementType>*& T);                        //销毁二叉树
    void insert(Node<ElementType>*& T, Node<ElementType>* S);   //将指针S所指节点插入二叉排序中
    int BiTreeDepth(Node <ElementType>* T);                     //求树的高度
    int getNodeFactor(Node<ElementType>* T);                     //求树中节点的平衡因子
    void factorForTree(Node<ElementType>*& T);                   //求树中的每个节点的平衡因子
    void nodeFctorIsTwo(Node<ElementType>*& T, Node<ElementType>*& p);        //获得平衡因子为2或-2的节点
    void nodeFctorIsTwoFather(Node<ElementType>*& T, Node<ElementType>*& f);  //获得平衡因子为2或-2的节点的父节点
    void LLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //LL调整
    void LRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //LR调整
    void RLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //RL调整
    void RRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //RR调整
    void AllAdjust(Node<ElementType>*& T);                       //集成四种调整，并实时更新平衡因子
    void preOrderTraverse(Node<ElementType>* T, int level);       //先序遍历输出
    void inOrderTraverse(Node <ElementType>* T, int level);       //中序遍历输出
    void BiTreeToArray(Node <ElementType>* T, ElementType A[], int i, int& count); //二叉树转数组
    void LevelTraverse(Node <ElementType>* T, ElementType B[], int num);          //对二叉链表表示的二叉树，按从上到下，从左到右打印结点值，即按层次打印
    void createSubBalanceBiTree(Node<ElementType>*& T);          //交互创建二叉平衡树
    void createBalanceBiTreeFromArray(Node<ElementType>*& T, ElementType A[], int n);//从数组中创建平衡二叉树
    void search(Node <ElementType>*& T, Node <ElementType>*& p, ElementType x);          //查找元素x
    Node <ElementType>* getElementFatherPointer(Node <ElementType>*& T, Node <ElementType>*& f, ElementType x); //获取某个元素的父亲指针，不存在返回NULL
    void getPriorElement(Node <ElementType>*& T, ElementType& min, ElementType& max);                 //获取前驱元素
    Node <ElementType>* getElementPriorPointer(Node <ElementType>*& T);  //获取某个元素的前驱指针
    void getNextElement(Node <ElementType>*& T, ElementType& min, ElementType& max);                  //获取后继元素
    Node <ElementType>* getElementNextPointer(Node <ElementType>*& T);   //获取某个元素的后继指针
    void deleteLeafNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f);        //删除叶子节点
    void deleteOneBranchNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f);   //删除仅有左子树或只有右子树的节点
    void deleteTwoBranchNode(Node <ElementType>*& T, Node <ElementType>*& p);   //删除既有左子树又有右子树的节点
    void deleteOperate(Node <ElementType>*& T, ElementType x);         //集成删除的三种情况的操作
private:
    Node<ElementType>* root;   //树根
};
//初始化
template< class ElementType>
BalanceBiTree<ElementType>::BalanceBiTree(Node<ElementType>*& T)
{
    T = NULL;
}
//菜单
template< class ElementType>
void BalanceBiTree<ElementType>::menu()
{
    cout << "*************************************************" << endl;
    cout << "0退出并销毁平衡二叉树" << endl;
    cout << "1二分查找算法实现查找元素" << endl;
    cout << "2插入结点构建二叉排序树（二叉平衡树）" << endl;
    cout << "3二叉排序树中查找指定值的结点" << endl;
    cout << "4二叉排序树中删除特定值的结点" << endl;
    cout << "5数组A[1..26]递增有序，设计算法以构造一棵平衡的二叉排序树" << endl;
    cout << "6树形输出" << endl;
    cout << "*************************************************" << endl;
}
//销毁二叉树
template< class ElementType>
void BalanceBiTree<ElementType>::destory(Node<ElementType>*& T)
{
    if (T)
    {
        destory(T->lChild);
        destory(T->rChild);
        delete T;
    }
}
//将指针S所指节点插入二叉排序中
template< class ElementType>
void BalanceBiTree<ElementType>::insert(Node<ElementType>*& T, Node<ElementType>* S)
{
    if (T == NULL)
        T = S;
    else if (S->data < T->data)
        insert(T->lChild, S);
    else
        insert(T->rChild, S);
}
//求树的高度
template< class ElementType>
int BalanceBiTree<ElementType>::BiTreeDepth(Node <ElementType>* T)
{
    int m, n;
    if (T == NULL)
        return 0;           //空树，高度为0
    else {
        m = BiTreeDepth(T->lChild);   //求左子树高度（递归）
        n = BiTreeDepth(T->rChild);   //求右子树高度（递归）
        if (m > n)
        {
            return m + 1;
        }
        else {
            return n + 1;
        }
    }
}
//求树中节点的平衡因子
template< class ElementType>
int BalanceBiTree<ElementType>::getNodeFactor(Node<ElementType>* T)
{
    int m = 0, n = 0;
    if (T)
    {
        m = BiTreeDepth(T->lChild);
        n = BiTreeDepth(T->rChild);
    }
    return m - n;
}
//求树中的每个节点的平衡因子
template< class ElementType>
void BalanceBiTree<ElementType>::factorForTree(Node<ElementType>*& T)
{
    if (T)
    {
        T->balanceFctor = getNodeFactor(T);
        factorForTree(T->lChild);
        factorForTree(T->rChild);
    }
}
//获得平衡因子为2或-2的节点
template< class ElementType>
void BalanceBiTree<ElementType>::nodeFctorIsTwo(Node<ElementType>*& T, Node<ElementType>*& p)
{
    if (T)
    {
        if (T->balanceFctor == 2 || T->balanceFctor == -2)
        {
            p = T;
        }
        nodeFctorIsTwo(T->lChild, p);
        nodeFctorIsTwo(T->rChild, p);
    }
}
//获得平衡因子为2或-2的节点的父节点
template< class ElementType>
void BalanceBiTree<ElementType>::nodeFctorIsTwoFather(Node<ElementType>*& T, Node<ElementType>*& f)
{
    if (T)
    {
        if (T->lChild != NULL)
        {
            if (T->lChild->balanceFctor == 2 || T->lChild->balanceFctor == -2)
            {
                f = T;
            }
        }
        if (T->rChild != NULL)
        {
            if (T->rChild->balanceFctor == 2 || T->rChild->balanceFctor == -2)
            {
                f = T;
            }
        }
        nodeFctorIsTwoFather(T->lChild, f);
        nodeFctorIsTwoFather(T->rChild, f);
    }
}
//LL调整
template< class ElementType>
void BalanceBiTree<ElementType>::LLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* r;
    if (T == p)           //->balanceFctor==2&&T->lChild->balanceFctor!=2
    {
        cout << "LL调整" << endl;
        T = p->lChild;        //将P的左孩子提升为新的根节点
        r = T->rChild;
        T->rChild = p;        //将p降为其左孩子的右孩子
        p->lChild = r;        //将p原来的左孩子的右孩子连接其p的左孩子

    }
    else {
        if (f->lChild == p)     //f的左孩子是p
        {
            cout << "LL调整" << endl;
            f->lChild = p->lChild;        //将P的左孩子提升为新的根节点
            r = f->lChild->rChild;
            f->lChild->rChild = p;        //将p降为其左孩子的右孩子
            p->lChild = r;        //将p原来的左孩子的右孩子连接其p的左孩子
        }
        if (f->rChild == p)     //f的左孩子是p
        {
            cout << "LL调整" << endl;
            f->rChild = p->lChild;        //将P的左孩子提升为新的根节点
            r = f->rChild->rChild;
            f->rChild->rChild = p;        //将p降为其左孩子的右孩子
            p->lChild = r;        //将p原来的左孩子的右孩子连接其p的左孩子
        }
    }
}
//LR调整
template< class ElementType>
void BalanceBiTree<ElementType>::LRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l, * r;
    if (T == p)           //->balanceFctor==2&&T->lChild->balanceFctor!=2
    {
        cout << "LR调整" << endl;
        T = p->lChild->rChild;    //将P的左孩子的右孩子提升为新的根节点
        r = T->rChild;
        l = T->lChild;
        T->rChild = p;
        T->lChild = p->lChild;
        T->lChild->rChild = l;
        T->rChild->lChild = r;
    }
    else {
        if (f->rChild == p)     //f的左孩子是p
        {
            cout << "LR调整" << endl;
            f->rChild = p->lChild->rChild;    //将P的左孩子的右孩子提升为新的根节点
            r = f->rChild->rChild;
            l = f->rChild->lChild;
            f->rChild->rChild = p;
            f->rChild->lChild = p->lChild;
            f->rChild->lChild->rChild = l;
            f->rChild->rChild->lChild = r;
        }
        if (f->lChild == p)     //f的左孩子是p
        {
            cout << "LR调整" << endl;
            f->lChild = p->lChild->rChild;    //将P的左孩子的右孩子提升为新的根节点
            r = f->lChild->rChild;
            l = f->lChild->lChild;
            f->lChild->rChild = p;
            f->lChild->lChild = p->lChild;
            f->lChild->lChild->rChild = l;
            f->lChild->rChild->lChild = r;
        }
    }
}
//RL调整
template< class ElementType>
void BalanceBiTree<ElementType>::RLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l, * r;
    if (T == p)           //->balanceFctor==-2&&T->rChild->balanceFctor!=-2
    {
        cout << "RL调整" << endl;
        T = p->rChild->lChild;
        r = T->rChild;
        l = T->lChild;
        T->lChild = p;
        T->rChild = p->rChild;
        T->lChild->rChild = l;
        T->rChild->lChild = r;
    }
    else {
        if (f->rChild == p)     //f的左孩子是p
        {
            cout << "RL调整" << endl;
            f->rChild = p->rChild->lChild;
            r = f->rChild->rChild;
            l = f->rChild->lChild;
            f->rChild->lChild = p;
            f->rChild->rChild = p->rChild;
            f->rChild->lChild->rChild = l;
            f->rChild->rChild->lChild = r;
        }
        if (f->lChild == p)     //f的左孩子是p
        {
            cout << "RL调整" << endl;
            f->lChild = p->rChild->lChild;
            r = f->lChild->rChild;
            l = f->lChild->lChild;
            f->lChild->lChild = p;
            f->lChild->rChild = p->rChild;
            f->lChild->lChild->rChild = l;
            f->lChild->rChild->lChild = r;
        }
    }
}
//RR调整
template< class ElementType>
void BalanceBiTree<ElementType>::RRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l;
    if (T == p)                   //->balanceFctor==-2&&T->rChild->balanceFctor!=-2
    {
        cout << "RR调整" << endl;
        T = p->rChild;        //将P的右孩子提升为新的根节点
        l = T->lChild;
        T->lChild = p;        //将p降为其右孩子的左孩子
        p->rChild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
        //注意：p->rChild->balanceFctor==0插入节点时用不上，删除节点时可用
    }
    else {
        if (f->rChild == p)     //f的右孩子是p
        {
            cout << "RR调整" << endl;
            f->rChild = p->rChild;        //将P的右孩子提升为新的根节点
            l = f->rChild->lChild;
            f->rChild->lChild = p;        //将p降为其右孩子的左孩子
            p->rChild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
        }
        if (f->lChild == p)     //f的左孩子是p
        {
            cout << "RR调整" << endl;
            f->lChild = p->rChild;        //将P的左孩子提升为新的根节点
            l = f->lChild->lChild;
            f->lChild->lChild = p;        //将p降为其左孩子的左孩子
            p->rChild = l;        //将p原来的右孩子的左孩子连接其p的右孩子
        }
    }
}
//集成四种调整，并实时更新平衡因子
template< class ElementType>
void BalanceBiTree<ElementType>::AllAdjust(Node<ElementType>*& T)
{
    Node<ElementType>* f = NULL, * p = NULL;
    factorForTree(T);
    nodeFctorIsTwoFather(T, f);
    nodeFctorIsTwo(T, p);
    while (p)
    {
        factorForTree(T);
        if (p->balanceFctor == 2 && (p->lChild->balanceFctor == 1 || p->lChild->balanceFctor == 0))
        {
            LLAdjust(T, p, f);
            factorForTree(T);
        }
        else if (p->balanceFctor == 2 && p->lChild->balanceFctor == -1)
        {
            LRAdjust(T, p, f);
            factorForTree(T);
        }
        else if (p->balanceFctor == -2 && p->rChild->balanceFctor == 1)
        {
            RLAdjust(T, p, f);
            factorForTree(T);
        }
        else if (p->balanceFctor == -2 && (p->rChild->balanceFctor == -1 || p->rChild->balanceFctor == 0))  //||p->rChild->balanceFctor==0
        {
            RRAdjust(T, p, f);
        }
        f = NULL;
        p = NULL;
        nodeFctorIsTwoFather(T, f);
        nodeFctorIsTwo(T, p);
    }
}
//先序遍历输出
template< class ElementType>
void BalanceBiTree<ElementType>::preOrderTraverse(Node<ElementType>* T, int level)
{
    if (T)
    {
        cout << "先序" << "(" << T->data << "," << level << ")" << " ";
        preOrderTraverse(T->lChild, level + 1);
        preOrderTraverse(T->rChild, level + 1);
    }
}
//中序遍历算法
template<class ElementType>
void BalanceBiTree<ElementType>::inOrderTraverse(Node <ElementType>* T, int level)
{
    if (T)
    {
        inOrderTraverse(T->lChild, level + 1);  //递归调用先序遍历左子树
        cout << "中序" << "(" << T->data << "," << level << ")" << " ";           //访问根节点
        inOrderTraverse(T->rChild, level + 1);  //递归调用先序遍历右子树
    }
}
//二叉树转数组
template<class ElementType>
void BalanceBiTree<ElementType>::BiTreeToArray(Node <ElementType>* T, ElementType A[], int i, int& count)
{
    if (T != NULL)
    {
        A[i] = T->data;
        if (i > count)
            count = i;
        BiTreeToArray(T->lChild, A, 2 * i, count);
        BiTreeToArray(T->rChild, A, 2 * i + 1, count);
    }
}
//对二叉链表表示的二叉树，按从上到下，从左到右打印结点值，即按层次打印
template<class ElementType>
void BalanceBiTree<ElementType>::LevelTraverse(Node <ElementType>* T, ElementType B[], int num)
{
    int n, i, j, t, q, s, p, m = 0, k = 0;
    n = (int)((log(num) / log(2)) + 1);
    p = n;
    for (i = 0; i < n; i++)
    {
        k = pow(2, m) + k;
        t = pow(2, m);
        j = pow(2, p - 1) - 1;
        q = pow(2, p) - 1;
        s = q;
        for (j; j > 0; j--)
        {
            cout << " ";
        }
        for (t; t <= k; t++)
        {
            if (B[t] == 0)
            {
                cout << "*";
                for (q; q > 0; q--)
                    cout << " ";
                q = s;
            }
            else {
                cout << B[t];
                for (q; q > 0; q--)
                    cout << " ";
                q = s;
            }
        }
        m++;
        p--;
        j = n - i - 1;
        cout << endl;
    }
}
//交互创建二叉平衡树
template< class ElementType>
void BalanceBiTree<ElementType>::createSubBalanceBiTree(Node<ElementType>*& T)
{
    int level = 1;
    int i = 1, j = 0;
    int A[100] = { 0 };
    int length = 0;
    ElementType x;
    Node<ElementType>* S, * p;
    T = new Node<ElementType>;
    T->balanceFctor = 0;
    T->lChild = NULL;
    T->rChild = NULL;
    p = T;
    cout << "请输入元素(-9999退出)：";
    cin >> x;
    T->data = x;
    while (x != -9999)
    {
        cout << "请输入元素：";
        cin >> x;
        if (x == -9999)
            return;
        S = new Node<ElementType>;
        S->data = x;
        S->balanceFctor = 0;
        S->lChild = NULL;
        S->rChild = NULL;
        insert(p, S);
        AllAdjust(T);
        p = T;
        inOrderTraverse(T, level);
        cout << endl;
        BiTreeToArray(T, A, i, length);
        cout << "其树状图为：" << endl;
        LevelTraverse(T, A, length);
        j = 0;
        for (j; j < 100; j++)
            A[j] = 0;
        level = 1;
        i = 1;
    }
}
//从数组中创建平衡二叉树
template< class ElementType>
void BalanceBiTree<ElementType>::createBalanceBiTreeFromArray(Node<ElementType>*& T, ElementType A[], int n)
{
    Node<ElementType>* S, * p;
    int i = 1;
    T = new Node<ElementType>;
    T->balanceFctor = 0;
    T->lChild = NULL;
    T->rChild = NULL;
    p = T;
    T->data = A[0];
    n = n - 1;
    while (n)
    {
        S = new Node<ElementType>;
        S->data = A[i];
        S->balanceFctor = 0;
        S->lChild = NULL;
        S->rChild = NULL;
        insert(p, S);
        AllAdjust(T);
        p = T;
        i++;
        n--;
    }
}
//查找元素x
template<class ElementType>
void BalanceBiTree<ElementType>::search(Node <ElementType>*& T, Node <ElementType>*& p, ElementType x)
{
    if (T)
    {
        if (T->data == x)
            p = T;
        search(T->lChild, p, x);
        search(T->rChild, p, x);
    }
}
//获取某个元素的父亲指针，不存在返回NULL
template<class ElementType>
Node <ElementType>* BalanceBiTree<ElementType>::getElementFatherPointer(Node <ElementType>*& T, Node <ElementType>*& f, ElementType x)
{
    if (T)
    {
        if (T->lChild != NULL)
        {
            if (T->lChild->data == x)
                f = T;
        }
        if (T->rChild != NULL)
        {
            if (T->rChild->data == x)
                f = T;
        }
        getElementFatherPointer(T->lChild, f, x);
        getElementFatherPointer(T->rChild, f, x);
    }
    return NULL;
}
//获取前驱元素
template<class ElementType>
void BalanceBiTree<ElementType>::getPriorElement(Node <ElementType>*& T, ElementType& min, ElementType& max)
{
    if (T)
    {
        min = T->data;
        if (min > max)
            max = min;
        getPriorElement(T->lChild, min, max);
        getPriorElement(T->rChild, min, max);
    }
}
//获取某个元素的前驱指针
template<class ElementType>
Node <ElementType>* BalanceBiTree<ElementType>::getElementPriorPointer(Node <ElementType>*& T)
{
    Node <ElementType>* p;
    ElementType min = 0, max = -9999;
    getPriorElement(T, min, max);
    search(T, p, max);
    return p;
}
//获取后继元素
template<class ElementType>
void BalanceBiTree<ElementType>::getNextElement(Node <ElementType>*& T, ElementType& min, ElementType& max)
{
    if (T)
    {
        max = T->data;
        if (min > max)
            min = max;
        getNextElement(T->lChild, min, max);
        getNextElement(T->rChild, min, max);
    }
}
//获取某个元素的后继指针
template<class ElementType>
Node <ElementType>* BalanceBiTree<ElementType>::getElementNextPointer(Node <ElementType>*& T)
{
    Node <ElementType>* p;
    ElementType min = 9999, max = 0;
    getNextElement(T, min, max);
    search(T, p, min);
    return p;
}
//删除叶子节点操作
template<class ElementType>
void BalanceBiTree<ElementType>::deleteLeafNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f)
{
    if (p == NULL)
    {
        cout << "此节点不存在，不能删除" << endl;
        return;
    }
    if (T == p)        //根节点即为叶子节点
    {
        delete p;
        T = NULL;
    }
    else {           //删除节点为非根节点的叶子节点
        if (f->lChild == p)
        {
            delete p;
            f->lChild = NULL;
        }
        if (f->rChild == p)
        {
            delete p;
            f->rChild = NULL;
        }
    }
}
//删除仅有左子树或只有右子树的节点
template<class ElementType>
void BalanceBiTree<ElementType>::deleteOneBranchNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f)
{
    if (p == NULL)
    {
        cout << "此节点不存在，不能删除" << endl;
        return;
    }
    if (T == p)
    {
        if (T->lChild == NULL && T->rChild != NULL)
        {
            T = p->rChild;
            delete p;
        }
        if (T->rChild == NULL && T->lChild != NULL)
        {
            T = p->lChild;
            delete p;
        }
    }
    else {
        if (p->lChild != NULL)
        {
            if (f->lChild == p)
                f->lChild = p->lChild;
            else
                f->rChild = p->lChild;
        }
        if (p->rChild != NULL)
        {
            if (f->lChild == p)
                f->lChild = p->rChild;
            else
                f->rChild = p->rChild;
        }
    }
}
//删除既有左子树又有右子树的节点
template<class ElementType>
void BalanceBiTree<ElementType>::deleteTwoBranchNode(Node <ElementType>*& T, Node <ElementType>*& p)
{
    Node <ElementType>* f, * next, * prior;
    if (p == NULL)
    {
        cout << "此节点不存在，不能删除" << endl;
        return;
    }
    if (p->balanceFctor == 1)                             //p的平衡因子为1时，用p的前驱节点代替p
    {
        prior = getElementPriorPointer(p->lChild);             //获得x的前驱指针
        if (prior->lChild != NULL && prior->rChild == NULL)   //情况一前驱节点只有左孩子
        {
            p->data = prior->data;
            prior->data = prior->lChild->data;
            delete prior->lChild;
            prior->lChild = NULL;
        }
        if (prior->lChild == NULL && prior->rChild == NULL)    //情况二前驱节点为叶子节点
        {
            getElementFatherPointer(T, f, prior->data); //得到前驱节点的父节点
            p->data = prior->data;
            delete prior;
            f->rChild = NULL;
        }
    }
    else if (p->balanceFctor == -1)                             //p的平衡因子为-1时，用p的后继节点代替p
    {
        next = getElementNextPointer(p->rChild);                //获得x的后继指针
        cout << next->data;
        int level = 1;
        if (next->rChild != NULL && next->lChild == NULL)      //情况一后继节点只有右孩子
        {
            p->data = next->data;
            next->data = next->rChild->data;
            delete next->rChild;
            next->rChild = NULL;
        }
        else if (next->rChild == NULL && next->lChild == NULL)       //情况二后继节点为叶子节点
        {
            getElementFatherPointer(T, f, next->data);     //得到后继节点的父节点
            p->data = next->data;
            delete next;
            f->lChild = NULL;
        }
    }
    else if (p->balanceFctor == 0)     //p的平衡因子为0时，用p的前驱或后继节点代替p，这里用前驱
    {
        prior = getElementPriorPointer(p->lChild);               //获得x的前驱指针
        if (prior->lChild != NULL && prior->rChild == NULL)     //情况一前驱节点只有左孩子
        {
            p->data = prior->data;
            prior->data = prior->lChild->data;
            delete prior->lChild;
            prior->lChild = NULL;
        }
        if (prior->lChild == NULL && prior->rChild == NULL)      //情况二前驱节点为叶子节点
        {
            getElementFatherPointer(T, f, prior->data);     //得到前驱节点的父节点
            p->data = prior->data;
            delete prior;
            if (p == f)                                      //这块需要特殊记忆，唯独p->balanceFctor==0需要考虑***
                f->lChild = NULL;
            else
                f->rChild = NULL;

        }
    }
}
//集成删除的三种情况的操作
template<class ElementType>
void BalanceBiTree<ElementType>::deleteOperate(Node <ElementType>*& T, ElementType x)
{
    Node <ElementType>* f, * p = NULL;
    search(T, p, x);
    getElementFatherPointer(T, f, x);
    if (p == NULL)
    {
        cout << "不存在此节点，删除失败！" << endl;
        return;
    }
    if (p->lChild == NULL && p->rChild == NULL)  //情况一删除节点为叶子节点
    {
        deleteLeafNode(T, p, f);
        if (T != NULL)
            AllAdjust(T);
    }
    else if ((p->lChild == NULL && p->rChild != NULL) || (p->lChild != NULL && p->rChild == NULL))
    {
        deleteOneBranchNode(T, p, f);
        if (T != NULL)
            AllAdjust(T);
    }
    else                           //if(p->lChild!=NULL&&p->rChild!=NULL)
    {
        deleteTwoBranchNode(T, p);
        if (T != NULL)
            AllAdjust(T);
    }
}
#endif // _BALANCEBITREE_H_
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
    int balanceFctor;           //ƽ������
};
template< class ElementType>
class BalanceBiTree {
public:
    BalanceBiTree(Node<ElementType>*& T);                       //��ʼ��
    static void menu();                                          //�˵�
    void destory(Node<ElementType>*& T);                        //���ٶ�����
    void insert(Node<ElementType>*& T, Node<ElementType>* S);   //��ָ��S��ָ�ڵ�������������
    int BiTreeDepth(Node <ElementType>* T);                     //�����ĸ߶�
    int getNodeFactor(Node<ElementType>* T);                     //�����нڵ��ƽ������
    void factorForTree(Node<ElementType>*& T);                   //�����е�ÿ���ڵ��ƽ������
    void nodeFctorIsTwo(Node<ElementType>*& T, Node<ElementType>*& p);        //���ƽ������Ϊ2��-2�Ľڵ�
    void nodeFctorIsTwoFather(Node<ElementType>*& T, Node<ElementType>*& f);  //���ƽ������Ϊ2��-2�Ľڵ�ĸ��ڵ�
    void LLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //LL����
    void LRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //LR����
    void RLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //RL����
    void RRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f);                        //RR����
    void AllAdjust(Node<ElementType>*& T);                       //�������ֵ�������ʵʱ����ƽ������
    void preOrderTraverse(Node<ElementType>* T, int level);       //����������
    void inOrderTraverse(Node <ElementType>* T, int level);       //����������
    void BiTreeToArray(Node <ElementType>* T, ElementType A[], int i, int& count); //������ת����
    void LevelTraverse(Node <ElementType>* T, ElementType B[], int num);          //�Զ��������ʾ�Ķ������������ϵ��£������Ҵ�ӡ���ֵ��������δ�ӡ
    void createSubBalanceBiTree(Node<ElementType>*& T);          //������������ƽ����
    void createBalanceBiTreeFromArray(Node<ElementType>*& T, ElementType A[], int n);//�������д���ƽ�������
    void search(Node <ElementType>*& T, Node <ElementType>*& p, ElementType x);          //����Ԫ��x
    Node <ElementType>* getElementFatherPointer(Node <ElementType>*& T, Node <ElementType>*& f, ElementType x); //��ȡĳ��Ԫ�صĸ���ָ�룬�����ڷ���NULL
    void getPriorElement(Node <ElementType>*& T, ElementType& min, ElementType& max);                 //��ȡǰ��Ԫ��
    Node <ElementType>* getElementPriorPointer(Node <ElementType>*& T);  //��ȡĳ��Ԫ�ص�ǰ��ָ��
    void getNextElement(Node <ElementType>*& T, ElementType& min, ElementType& max);                  //��ȡ���Ԫ��
    Node <ElementType>* getElementNextPointer(Node <ElementType>*& T);   //��ȡĳ��Ԫ�صĺ��ָ��
    void deleteLeafNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f);        //ɾ��Ҷ�ӽڵ�
    void deleteOneBranchNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f);   //ɾ��������������ֻ���������Ľڵ�
    void deleteTwoBranchNode(Node <ElementType>*& T, Node <ElementType>*& p);   //ɾ�����������������������Ľڵ�
    void deleteOperate(Node <ElementType>*& T, ElementType x);         //����ɾ������������Ĳ���
private:
    Node<ElementType>* root;   //����
};
//��ʼ��
template< class ElementType>
BalanceBiTree<ElementType>::BalanceBiTree(Node<ElementType>*& T)
{
    T = NULL;
}
//�˵�
template< class ElementType>
void BalanceBiTree<ElementType>::menu()
{
    cout << "*************************************************" << endl;
    cout << "0�˳�������ƽ�������" << endl;
    cout << "1���ֲ����㷨ʵ�ֲ���Ԫ��" << endl;
    cout << "2�����㹹������������������ƽ������" << endl;
    cout << "3�����������в���ָ��ֵ�Ľ��" << endl;
    cout << "4������������ɾ���ض�ֵ�Ľ��" << endl;
    cout << "5����A[1..26]������������㷨�Թ���һ��ƽ��Ķ���������" << endl;
    cout << "6�������" << endl;
    cout << "*************************************************" << endl;
}
//���ٶ�����
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
//��ָ��S��ָ�ڵ�������������
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
//�����ĸ߶�
template< class ElementType>
int BalanceBiTree<ElementType>::BiTreeDepth(Node <ElementType>* T)
{
    int m, n;
    if (T == NULL)
        return 0;           //�������߶�Ϊ0
    else {
        m = BiTreeDepth(T->lChild);   //���������߶ȣ��ݹ飩
        n = BiTreeDepth(T->rChild);   //���������߶ȣ��ݹ飩
        if (m > n)
        {
            return m + 1;
        }
        else {
            return n + 1;
        }
    }
}
//�����нڵ��ƽ������
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
//�����е�ÿ���ڵ��ƽ������
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
//���ƽ������Ϊ2��-2�Ľڵ�
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
//���ƽ������Ϊ2��-2�Ľڵ�ĸ��ڵ�
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
//LL����
template< class ElementType>
void BalanceBiTree<ElementType>::LLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* r;
    if (T == p)           //->balanceFctor==2&&T->lChild->balanceFctor!=2
    {
        cout << "LL����" << endl;
        T = p->lChild;        //��P����������Ϊ�µĸ��ڵ�
        r = T->rChild;
        T->rChild = p;        //��p��Ϊ�����ӵ��Һ���
        p->lChild = r;        //��pԭ�������ӵ��Һ���������p������

    }
    else {
        if (f->lChild == p)     //f��������p
        {
            cout << "LL����" << endl;
            f->lChild = p->lChild;        //��P����������Ϊ�µĸ��ڵ�
            r = f->lChild->rChild;
            f->lChild->rChild = p;        //��p��Ϊ�����ӵ��Һ���
            p->lChild = r;        //��pԭ�������ӵ��Һ���������p������
        }
        if (f->rChild == p)     //f��������p
        {
            cout << "LL����" << endl;
            f->rChild = p->lChild;        //��P����������Ϊ�µĸ��ڵ�
            r = f->rChild->rChild;
            f->rChild->rChild = p;        //��p��Ϊ�����ӵ��Һ���
            p->lChild = r;        //��pԭ�������ӵ��Һ���������p������
        }
    }
}
//LR����
template< class ElementType>
void BalanceBiTree<ElementType>::LRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l, * r;
    if (T == p)           //->balanceFctor==2&&T->lChild->balanceFctor!=2
    {
        cout << "LR����" << endl;
        T = p->lChild->rChild;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
        r = T->rChild;
        l = T->lChild;
        T->rChild = p;
        T->lChild = p->lChild;
        T->lChild->rChild = l;
        T->rChild->lChild = r;
    }
    else {
        if (f->rChild == p)     //f��������p
        {
            cout << "LR����" << endl;
            f->rChild = p->lChild->rChild;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
            r = f->rChild->rChild;
            l = f->rChild->lChild;
            f->rChild->rChild = p;
            f->rChild->lChild = p->lChild;
            f->rChild->lChild->rChild = l;
            f->rChild->rChild->lChild = r;
        }
        if (f->lChild == p)     //f��������p
        {
            cout << "LR����" << endl;
            f->lChild = p->lChild->rChild;    //��P�����ӵ��Һ�������Ϊ�µĸ��ڵ�
            r = f->lChild->rChild;
            l = f->lChild->lChild;
            f->lChild->rChild = p;
            f->lChild->lChild = p->lChild;
            f->lChild->lChild->rChild = l;
            f->lChild->rChild->lChild = r;
        }
    }
}
//RL����
template< class ElementType>
void BalanceBiTree<ElementType>::RLAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l, * r;
    if (T == p)           //->balanceFctor==-2&&T->rChild->balanceFctor!=-2
    {
        cout << "RL����" << endl;
        T = p->rChild->lChild;
        r = T->rChild;
        l = T->lChild;
        T->lChild = p;
        T->rChild = p->rChild;
        T->lChild->rChild = l;
        T->rChild->lChild = r;
    }
    else {
        if (f->rChild == p)     //f��������p
        {
            cout << "RL����" << endl;
            f->rChild = p->rChild->lChild;
            r = f->rChild->rChild;
            l = f->rChild->lChild;
            f->rChild->lChild = p;
            f->rChild->rChild = p->rChild;
            f->rChild->lChild->rChild = l;
            f->rChild->rChild->lChild = r;
        }
        if (f->lChild == p)     //f��������p
        {
            cout << "RL����" << endl;
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
//RR����
template< class ElementType>
void BalanceBiTree<ElementType>::RRAdjust(Node<ElementType>*& T, Node<ElementType>*& p, Node<ElementType>*& f)
{
    Node<ElementType>* l;
    if (T == p)                   //->balanceFctor==-2&&T->rChild->balanceFctor!=-2
    {
        cout << "RR����" << endl;
        T = p->rChild;        //��P���Һ�������Ϊ�µĸ��ڵ�
        l = T->lChild;
        T->lChild = p;        //��p��Ϊ���Һ��ӵ�����
        p->rChild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
        //ע�⣺p->rChild->balanceFctor==0����ڵ�ʱ�ò��ϣ�ɾ���ڵ�ʱ����
    }
    else {
        if (f->rChild == p)     //f���Һ�����p
        {
            cout << "RR����" << endl;
            f->rChild = p->rChild;        //��P���Һ�������Ϊ�µĸ��ڵ�
            l = f->rChild->lChild;
            f->rChild->lChild = p;        //��p��Ϊ���Һ��ӵ�����
            p->rChild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
        }
        if (f->lChild == p)     //f��������p
        {
            cout << "RR����" << endl;
            f->lChild = p->rChild;        //��P����������Ϊ�µĸ��ڵ�
            l = f->lChild->lChild;
            f->lChild->lChild = p;        //��p��Ϊ�����ӵ�����
            p->rChild = l;        //��pԭ�����Һ��ӵ�����������p���Һ���
        }
    }
}
//�������ֵ�������ʵʱ����ƽ������
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
//����������
template< class ElementType>
void BalanceBiTree<ElementType>::preOrderTraverse(Node<ElementType>* T, int level)
{
    if (T)
    {
        cout << "����" << "(" << T->data << "," << level << ")" << " ";
        preOrderTraverse(T->lChild, level + 1);
        preOrderTraverse(T->rChild, level + 1);
    }
}
//��������㷨
template<class ElementType>
void BalanceBiTree<ElementType>::inOrderTraverse(Node <ElementType>* T, int level)
{
    if (T)
    {
        inOrderTraverse(T->lChild, level + 1);  //�ݹ�����������������
        cout << "����" << "(" << T->data << "," << level << ")" << " ";           //���ʸ��ڵ�
        inOrderTraverse(T->rChild, level + 1);  //�ݹ�����������������
    }
}
//������ת����
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
//�Զ��������ʾ�Ķ������������ϵ��£������Ҵ�ӡ���ֵ��������δ�ӡ
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
//������������ƽ����
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
    cout << "������Ԫ��(-9999�˳�)��";
    cin >> x;
    T->data = x;
    while (x != -9999)
    {
        cout << "������Ԫ�أ�";
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
        cout << "����״ͼΪ��" << endl;
        LevelTraverse(T, A, length);
        j = 0;
        for (j; j < 100; j++)
            A[j] = 0;
        level = 1;
        i = 1;
    }
}
//�������д���ƽ�������
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
//����Ԫ��x
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
//��ȡĳ��Ԫ�صĸ���ָ�룬�����ڷ���NULL
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
//��ȡǰ��Ԫ��
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
//��ȡĳ��Ԫ�ص�ǰ��ָ��
template<class ElementType>
Node <ElementType>* BalanceBiTree<ElementType>::getElementPriorPointer(Node <ElementType>*& T)
{
    Node <ElementType>* p;
    ElementType min = 0, max = -9999;
    getPriorElement(T, min, max);
    search(T, p, max);
    return p;
}
//��ȡ���Ԫ��
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
//��ȡĳ��Ԫ�صĺ��ָ��
template<class ElementType>
Node <ElementType>* BalanceBiTree<ElementType>::getElementNextPointer(Node <ElementType>*& T)
{
    Node <ElementType>* p;
    ElementType min = 9999, max = 0;
    getNextElement(T, min, max);
    search(T, p, min);
    return p;
}
//ɾ��Ҷ�ӽڵ����
template<class ElementType>
void BalanceBiTree<ElementType>::deleteLeafNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f)
{
    if (p == NULL)
    {
        cout << "�˽ڵ㲻���ڣ�����ɾ��" << endl;
        return;
    }
    if (T == p)        //���ڵ㼴ΪҶ�ӽڵ�
    {
        delete p;
        T = NULL;
    }
    else {           //ɾ���ڵ�Ϊ�Ǹ��ڵ��Ҷ�ӽڵ�
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
//ɾ��������������ֻ���������Ľڵ�
template<class ElementType>
void BalanceBiTree<ElementType>::deleteOneBranchNode(Node <ElementType>*& T, Node <ElementType>*& p, Node <ElementType>*& f)
{
    if (p == NULL)
    {
        cout << "�˽ڵ㲻���ڣ�����ɾ��" << endl;
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
//ɾ�����������������������Ľڵ�
template<class ElementType>
void BalanceBiTree<ElementType>::deleteTwoBranchNode(Node <ElementType>*& T, Node <ElementType>*& p)
{
    Node <ElementType>* f, * next, * prior;
    if (p == NULL)
    {
        cout << "�˽ڵ㲻���ڣ�����ɾ��" << endl;
        return;
    }
    if (p->balanceFctor == 1)                             //p��ƽ������Ϊ1ʱ����p��ǰ���ڵ����p
    {
        prior = getElementPriorPointer(p->lChild);             //���x��ǰ��ָ��
        if (prior->lChild != NULL && prior->rChild == NULL)   //���һǰ���ڵ�ֻ������
        {
            p->data = prior->data;
            prior->data = prior->lChild->data;
            delete prior->lChild;
            prior->lChild = NULL;
        }
        if (prior->lChild == NULL && prior->rChild == NULL)    //�����ǰ���ڵ�ΪҶ�ӽڵ�
        {
            getElementFatherPointer(T, f, prior->data); //�õ�ǰ���ڵ�ĸ��ڵ�
            p->data = prior->data;
            delete prior;
            f->rChild = NULL;
        }
    }
    else if (p->balanceFctor == -1)                             //p��ƽ������Ϊ-1ʱ����p�ĺ�̽ڵ����p
    {
        next = getElementNextPointer(p->rChild);                //���x�ĺ��ָ��
        cout << next->data;
        int level = 1;
        if (next->rChild != NULL && next->lChild == NULL)      //���һ��̽ڵ�ֻ���Һ���
        {
            p->data = next->data;
            next->data = next->rChild->data;
            delete next->rChild;
            next->rChild = NULL;
        }
        else if (next->rChild == NULL && next->lChild == NULL)       //�������̽ڵ�ΪҶ�ӽڵ�
        {
            getElementFatherPointer(T, f, next->data);     //�õ���̽ڵ�ĸ��ڵ�
            p->data = next->data;
            delete next;
            f->lChild = NULL;
        }
    }
    else if (p->balanceFctor == 0)     //p��ƽ������Ϊ0ʱ����p��ǰ�����̽ڵ����p��������ǰ��
    {
        prior = getElementPriorPointer(p->lChild);               //���x��ǰ��ָ��
        if (prior->lChild != NULL && prior->rChild == NULL)     //���һǰ���ڵ�ֻ������
        {
            p->data = prior->data;
            prior->data = prior->lChild->data;
            delete prior->lChild;
            prior->lChild = NULL;
        }
        if (prior->lChild == NULL && prior->rChild == NULL)      //�����ǰ���ڵ�ΪҶ�ӽڵ�
        {
            getElementFatherPointer(T, f, prior->data);     //�õ�ǰ���ڵ�ĸ��ڵ�
            p->data = prior->data;
            delete prior;
            if (p == f)                                      //�����Ҫ������䣬Ψ��p->balanceFctor==0��Ҫ����***
                f->lChild = NULL;
            else
                f->rChild = NULL;

        }
    }
}
//����ɾ������������Ĳ���
template<class ElementType>
void BalanceBiTree<ElementType>::deleteOperate(Node <ElementType>*& T, ElementType x)
{
    Node <ElementType>* f, * p = NULL;
    search(T, p, x);
    getElementFatherPointer(T, f, x);
    if (p == NULL)
    {
        cout << "�����ڴ˽ڵ㣬ɾ��ʧ�ܣ�" << endl;
        return;
    }
    if (p->lChild == NULL && p->rChild == NULL)  //���һɾ���ڵ�ΪҶ�ӽڵ�
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
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

int num_rand(int a[],int size,int randsize);

typedef struct AVLTreeNode {
    Type key;
    int height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
} *AVLTreeN;

// ��ȡAVL���ĸ߶�
int HeightAVLTree(AVLTreeN atree);

// �������AVL��
void InorderAVLTree(AVLTreeN atree);

// (�ݹ�ʵ��)����AVL����ֵΪkey�Ľڵ�
AVLTreeN SearchAVLTree(AVLTreeN atree, Type key);

// ������С�ڵ�, Ҳ����AVL������ڵ�
AVLTreeN MinAVLTree(AVLTreeN atree);

// �������ڵ�, Ҳ����AVL�����ҽڵ�
AVLTreeN MaxAVLTree(AVLTreeN atree);

// ����ڵ� �����µĸ��ڵ�, ��Ϊ����Ľڵ��п����滻���ڵ�
AVLTreeN InsertAVLTree(AVLTreeN atree, Type key);

// ɾ���ڵ� �����µĸ��ڵ�, ��Ϊɾ���Ľڵ���ܾ��Ǹ��ڵ�
AVLTreeN DeleteAVLTree(AVLTreeN atree, Type key);

// ����AVL��
void DestroyAVLTree(AVLTreeN atree);

void PrintAVLTree(AVLTreeN root);

#endif


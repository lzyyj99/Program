#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED        0    // ��ɫ�ڵ�
#define BLACK    1    // ��ɫ�ڵ�

int num_rand(int a[],int size,int randsize);

typedef int Type;

// ������Ľڵ�
typedef struct RBTreeNode{
    unsigned char color;        // ��ɫ(RED �� BLACK)
    Type   key;                    // �ؼ���(��ֵ)
    struct RBTreeNode *left;    // ����
    struct RBTreeNode *right;    // �Һ���
    struct RBTreeNode *parent;    // �����
}Node, *RBTree;

// ������ĸ�
typedef struct rb_root{
    Node *node;
}RBRoot;

// ���������������"������ĸ�"��
RBRoot* CreateRBTree();

// ���ٺ����
void DestoryRBTree(RBRoot *root);

// �������뵽������С�����ɹ�������0��ʧ�ܷ���-1��
int InsertRBTree(RBRoot *root, Type key);

// ɾ�����(keyΪ�ڵ��ֵ)
int DeleteRBTree(RBRoot *root, Type key);

// �������"�����"
void InorderRBTree(RBRoot *root);

// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
int SearchRBTree(RBRoot *root, Type key);

// ��ӡ�����
void PrintRBTree(RBRoot *root);

void Print1RBTree(RBRoot *root);
#endif

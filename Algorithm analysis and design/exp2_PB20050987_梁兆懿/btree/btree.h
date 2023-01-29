#ifndef _BTREE_H_
#define _BTREE_H_


typedef struct bintree
{
	int data;
	struct bintree* lchild;
	struct bintree* rchild;
}btree;

int num_rand(int a[],int size,int randsize);

//��ʼ������������Ľ��
btree* InitnodeBTree(int p_data);

//�������
void M_orderBTree(btree* root);

//������
btree* InsertBTree(btree* root, btree* node);

//ɾ��
btree* DelBTree(btree* root, int p_data);

//Ѱ�ҽ��
int FindBTree(btree* root,int fnum); 
int Find0BTree(btree* root,int fnum);
//��ӡ�� 
void PrintBTree(btree* root);
#endif

#ifndef _BTREE_H_
#define _BTREE_H_


typedef struct bintree
{
	int data;
	struct bintree* lchild;
	struct bintree* rchild;
}btree;

int num_rand(int a[],int size,int randsize);

//初始化二叉查找树的结点
btree* InitnodeBTree(int p_data);

//中序遍历
void M_orderBTree(btree* root);

//插入结点
btree* InsertBTree(btree* root, btree* node);

//删除
btree* DelBTree(btree* root, int p_data);

//寻找结点
int FindBTree(btree* root,int fnum); 
int Find0BTree(btree* root,int fnum);
//打印树 
void PrintBTree(btree* root);
#endif

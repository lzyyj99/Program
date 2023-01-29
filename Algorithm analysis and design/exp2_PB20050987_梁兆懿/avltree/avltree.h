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

// 获取AVL树的高度
int HeightAVLTree(AVLTreeN atree);

// 中序遍历AVL树
void InorderAVLTree(AVLTreeN atree);

// (递归实现)查找AVL树键值为key的节点
AVLTreeN SearchAVLTree(AVLTreeN atree, Type key);

// 查找最小节点, 也就是AVL树最左节点
AVLTreeN MinAVLTree(AVLTreeN atree);

// 查找最大节点, 也就是AVL树最右节点
AVLTreeN MaxAVLTree(AVLTreeN atree);

// 插入节点 返回新的根节点, 因为插入的节点有可能替换根节点
AVLTreeN InsertAVLTree(AVLTreeN atree, Type key);

// 删除节点 返回新的根节点, 因为删除的节点可能就是根节点
AVLTreeN DeleteAVLTree(AVLTreeN atree, Type key);

// 销毁AVL树
void DestroyAVLTree(AVLTreeN atree);

void PrintAVLTree(AVLTreeN root);

#endif


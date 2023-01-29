#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点

int num_rand(int a[],int size,int randsize);

typedef int Type;

// 红黑树的节点
typedef struct RBTreeNode{
    unsigned char color;        // 颜色(RED 或 BLACK)
    Type   key;                    // 关键字(键值)
    struct RBTreeNode *left;    // 左孩子
    struct RBTreeNode *right;    // 右孩子
    struct RBTreeNode *parent;    // 父结点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root{
    Node *node;
}RBRoot;

// 创建红黑树，返回"红黑树的根"！
RBRoot* CreateRBTree();

// 销毁红黑树
void DestoryRBTree(RBRoot *root);

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
int InsertRBTree(RBRoot *root, Type key);

// 删除结点(key为节点的值)
int DeleteRBTree(RBRoot *root, Type key);

// 中序遍历"红黑树"
void InorderRBTree(RBRoot *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
int SearchRBTree(RBRoot *root, Type key);

// 打印红黑树
void PrintRBTree(RBRoot *root);

void Print1RBTree(RBRoot *root);
#endif

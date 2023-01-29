#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>


#define HEIGHT(p)   ((p==NULL) ? 0 : (((AVLTreeN)(p))->height))
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

int num_rand(int a[],int size,int randsize)
{
    int i;
    int b[randsize+1];
    for(i=0;i<=randsize;i++){
    	b[i]=0;
	}
    for(i=0;i<size;i++)
    {	
		while(1){
        a[i]=rand()%randsize+1;
        if(b[a[i]]!=1){
        	b[a[i]]=1;
        	break;
		}
    }
}
}
// 获取AVL树的高度
int HeightAVLTree(AVLTreeN atree)
{
    return HEIGHT(atree);
}

// 中序遍历AVL树
void InorderAVLTree(AVLTreeN atree)
{
    if (atree) {
        InorderAVLTree(atree->left);
        printf("%d ", atree->key);
        InorderAVLTree(atree->right);
    }
}

// (递归实现)查找AVL树键值为key的节点
AVLTreeN SearchAVLTree(AVLTreeN atree, Type key)
{
    if (atree==NULL || key==atree->key) {
        return atree;
    }

    if (atree->key > key)
        return SearchAVLTree(atree->left, key);
    else
        return SearchAVLTree(atree->right, key);
}

// 查找最小节点, 也就是AVL树最左节点
AVLTreeN MinAVLTree(AVLTreeN atree)
{
    if (atree == NULL)
        return atree;

    while (atree->left != NULL)
        atree = atree->left;

    return atree;
}

// 查找最大节点, 也就是AVL树最右节点
AVLTreeN MaxAVLTree(AVLTreeN atree)
{
    if (atree == NULL)
        return atree;

    while (atree->right != NULL)
        atree = atree->right;

    return atree;
}

// LL: 左左对应的情况 左单旋转, 返回旋转后的根节点
AVLTreeN LL_Rotation(AVLTreeN atree)
{
    struct AVLTreeNode *k1;

    k1 = atree->left;
    atree->left = k1->right;
    k1->right = atree;

    atree->height = MAX(HEIGHT(atree->left), HEIGHT(atree->right)) + 1;
    k1->height = MAX(HEIGHT(k1->left), atree->height) + 1;

    return k1;
}

// RR: 右右对应的情况 右单旋转, 返回旋转后的节点
AVLTreeN RR_Rotation(AVLTreeN atree)
{
    struct AVLTreeNode *k1;

    k1 = atree->right;
    atree->right = k1->left;
    k1->left = atree;

    atree->height = MAX(HEIGHT(atree->left), HEIGHT(atree->right)) + 1;
    k1->height = MAX(HEIGHT(k1->left), atree->height) + 1;

    return k1;
}

// LR: 左右对应的情况 左双旋转, 返回旋转后的节点
AVLTreeN LR_Rotation(AVLTreeN atree)
{
    atree->left = RR_Rotation(atree->left);
    return LL_Rotation(atree);
}

// RL: 右左对应的情况 右双旋转, 返回旋转后的节点
AVLTreeN RL_Rotation(AVLTreeN atree)
{
    atree->right = LL_Rotation(atree->right);
    return RR_Rotation(atree);
}

// 创建一个AVL树的节点
AVLTreeN Create_nodeAVLTree(Type key, struct AVLTreeNode *left, struct AVLTreeNode *right)
{
    struct AVLTreeNode *p = NULL;

    p = (AVLTreeN)malloc(sizeof(struct AVLTreeNode));
    if (p == NULL)
        return NULL;

    p->height = 0;
    p->key = key;
    p->left = left;
    p->right = right;

    return p;
}


// 插入节点 返回新的根节点, 因为插入的节点有可能替换根节点
AVLTreeN InsertAVLTree(AVLTreeN atree, Type key)
{
    if (atree == NULL) {
        atree = Create_nodeAVLTree(key, NULL, NULL);
        if (atree == NULL) {
            printf("avltree_create_node failed. \r\n");
            return NULL;
        }
    } else if (key < atree->key) {
        atree->left = InsertAVLTree(atree->left, key);
        if ((HEIGHT(atree->left) - HEIGHT(atree->right)) == 2) {
            if (key < atree->left->key) {
                atree = LL_Rotation(atree);
            } else {
                atree = LR_Rotation(atree);
            }
        }
    } else if (key > atree->key) {
        atree->right = InsertAVLTree(atree->right, key);
        if ((HEIGHT(atree->right) - HEIGHT(atree->left)) == 2) {
            if (key > atree->right->key) {
                atree = RR_Rotation(atree);
            } else {
                atree = RL_Rotation(atree);
            }
        }
    } else {
        printf("the key has existed. \r\n");
    }

    atree->height = MAX(HEIGHT(atree->left), HEIGHT(atree->right)) + 1;    // 更新一下atree的高度数值

    return atree;
}

AVLTreeN Delete0AVLTree(AVLTreeN atree, struct AVLTreeNode *node)
{
    struct AVLTreeNode *t = NULL;
    if (atree==NULL || node==NULL)
        return NULL;

    if (node->key < atree->key) {
        atree->left = Delete0AVLTree(atree->left, node);
        if ((HEIGHT(atree->right) - HEIGHT(atree->left)) == 2) {
            t = atree->right;
            if (t->right > t->left) {
                atree = RR_Rotation(atree);
            } else {
                atree = RL_Rotation(atree);
            }
        }
    } else if (node->key > atree->key) {
        atree->right = Delete0AVLTree(atree->right, node);
        if ((HEIGHT(atree->left) - HEIGHT(atree->right)) == 2) {
            t = atree->left;
            if (t->left > t->right) {
                atree = LL_Rotation(atree);
            } else {
                atree = LR_Rotation(atree);
            }
        }
    } else {
        if (atree->left==NULL) {
            t = atree;
            atree = atree->right;
            free(t);
        } else if (atree->right==NULL) {
            t = atree;
            atree = atree->left;
            free(t);
        } else {
            if (HEIGHT(atree->left) > HEIGHT(atree->right)) {
                t = MaxAVLTree(atree->left);
                atree->key = t->key;
                atree->left = Delete0AVLTree(atree->left, t);   // __avltree_delete 返回的肯定是AVL树
            } else {
                t = MinAVLTree(atree->right);
                atree->key = t->key;
                atree->right = Delete0AVLTree(atree->right, t); // // __avltree_delete 返回的肯定是AVL树
            }
        }
    }

    return atree;
}

// 删除节点 返回新的根节点, 因为删除的节点可能就是根节点
AVLTreeN DeleteAVLTree(AVLTreeN atree, Type key)
{
    struct AVLTreeNode *node = NULL;
    node = SearchAVLTree(atree, key);

    if (node) {
        atree = Delete0AVLTree(atree, node);
    }

    return atree;      
}

// 销毁AVL树
void DestroyAVLTree(AVLTreeN atree)
{
    if (atree == NULL)
        return;

    if (atree->left)
        DestroyAVLTree(atree->left);

    if (atree->right)
        DestroyAVLTree(atree->right);

    free(atree);
}
void PrintAVLTree(AVLTreeN root)
{
	static int level = -1; //记录是第几层次
	int i;

	if (NULL == root)
		return;

	level++;
	PrintAVLTree(root->right);
	level--;

	level++;
	for (i = 0; i < level; i++)
		printf("  ");
	printf("%2d\n", root->key);
	PrintAVLTree(root->left);
	level--;
}

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
// ��ȡAVL���ĸ߶�
int HeightAVLTree(AVLTreeN atree)
{
    return HEIGHT(atree);
}

// �������AVL��
void InorderAVLTree(AVLTreeN atree)
{
    if (atree) {
        InorderAVLTree(atree->left);
        printf("%d ", atree->key);
        InorderAVLTree(atree->right);
    }
}

// (�ݹ�ʵ��)����AVL����ֵΪkey�Ľڵ�
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

// ������С�ڵ�, Ҳ����AVL������ڵ�
AVLTreeN MinAVLTree(AVLTreeN atree)
{
    if (atree == NULL)
        return atree;

    while (atree->left != NULL)
        atree = atree->left;

    return atree;
}

// �������ڵ�, Ҳ����AVL�����ҽڵ�
AVLTreeN MaxAVLTree(AVLTreeN atree)
{
    if (atree == NULL)
        return atree;

    while (atree->right != NULL)
        atree = atree->right;

    return atree;
}

// LL: �����Ӧ����� ����ת, ������ת��ĸ��ڵ�
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

// RR: ���Ҷ�Ӧ����� �ҵ���ת, ������ת��Ľڵ�
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

// LR: ���Ҷ�Ӧ����� ��˫��ת, ������ת��Ľڵ�
AVLTreeN LR_Rotation(AVLTreeN atree)
{
    atree->left = RR_Rotation(atree->left);
    return LL_Rotation(atree);
}

// RL: �����Ӧ����� ��˫��ת, ������ת��Ľڵ�
AVLTreeN RL_Rotation(AVLTreeN atree)
{
    atree->right = LL_Rotation(atree->right);
    return RR_Rotation(atree);
}

// ����һ��AVL���Ľڵ�
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


// ����ڵ� �����µĸ��ڵ�, ��Ϊ����Ľڵ��п����滻���ڵ�
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

    atree->height = MAX(HEIGHT(atree->left), HEIGHT(atree->right)) + 1;    // ����һ��atree�ĸ߶���ֵ

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
                atree->left = Delete0AVLTree(atree->left, t);   // __avltree_delete ���صĿ϶���AVL��
            } else {
                t = MinAVLTree(atree->right);
                atree->key = t->key;
                atree->right = Delete0AVLTree(atree->right, t); // // __avltree_delete ���صĿ϶���AVL��
            }
        }
    }

    return atree;
}

// ɾ���ڵ� �����µĸ��ڵ�, ��Ϊɾ���Ľڵ���ܾ��Ǹ��ڵ�
AVLTreeN DeleteAVLTree(AVLTreeN atree, Type key)
{
    struct AVLTreeNode *node = NULL;
    node = SearchAVLTree(atree, key);

    if (node) {
        atree = Delete0AVLTree(atree, node);
    }

    return atree;      
}

// ����AVL��
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
	static int level = -1; //��¼�ǵڼ����
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

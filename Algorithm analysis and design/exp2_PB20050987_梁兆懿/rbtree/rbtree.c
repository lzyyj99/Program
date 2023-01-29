#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

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

RBRoot* CreateRBTree()
{
    RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
    root->node = NULL;

    return root;
}

void Inorder0RBTree(RBTree tree)
{
    if(tree != NULL)
    {
        Inorder0RBTree(tree->left);
        printf("%d ", tree->key);
        Inorder0RBTree(tree->right);
    }
}

void InorderRBTree(RBRoot *root)
{
    if (root)
        Inorder0RBTree(root->node);
}

Node* Search0RBTree(RBTree x, Type key)
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return Search0RBTree(x->left, key);
    else
        return Search0RBTree(x->right, key);
}

int SearchRBTree(RBRoot *root, Type key)
{
    if (root)
        return Search0RBTree(root->node, key)? 0 : -1;
}


void rbtree_left_rotate(RBRoot *root, Node *x)
{

    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root->node = y;     
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;   
        else
            x->parent->right = y;    
    }
    y->left = x;
    x->parent = y;
}

void rbtree_right_rotate(RBRoot *root, Node *y)
{
    Node *x = y->left;

    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        root->node = x;        
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;  
        else
            y->parent->left = x;   

    x->right = y;

    y->parent = x;
}
} 

void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;

    while ((parent = node->parent) && parent->color==RED)
    {
        gparent = parent->parent;

        if (parent == gparent->left)
        {

            {
                Node *uncle = gparent->right;
                if (uncle && uncle->color==RED)
                {
                    do { uncle->color = BLACK; } while (0);
                    do { parent->color = BLACK; } while (0);
                    do { gparent->color = RED; } while (0);
                    node = gparent;
                    continue;
                }
            }

            if (parent->right == node)
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            do { parent->color = BLACK; } while (0);
            do { gparent->color = RED; } while (0);
            rbtree_right_rotate(root, gparent);
        }
        else
        {
            {
                Node *uncle = gparent->left;
                if (uncle && uncle->color==RED)
                {
                    do { uncle->color = BLACK; } while (0);
                    do { parent->color = BLACK; } while (0);
                    do { gparent->color = RED; } while (0);
                    node = gparent;
                    continue;
                }
            }

            if (parent->left == node)
            {
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            do { parent->color = BLACK; } while (0);
            do { gparent->color = RED; } while (0);
            rbtree_left_rotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    do { root->node->color = BLACK; } while (0);
}

void Insert0RBTree(RBRoot *root, Node *node)
{
    Node *y = NULL;
    Node *x = root->node;

    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;

    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;                
        else
            y->right = node;        
    }
    else
    {
        root->node = node;      
    }
    node->color = RED;
    rbtree_insert_fixup(root, node);
}


Node* CreateRBTreeNode(Type key, Node *parent, Node *left, Node* right)
{
    Node* p;

    if ((p = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK; // 默认为黑色

    return p;
}


int InsertRBTree(RBRoot *root, Type key)
{
    Node *node;   

    if (Search0RBTree(root->node, key)!= NULL)
        return -1;

    if ((node=CreateRBTreeNode(key, NULL, NULL, NULL)) == NULL)
        return -1;

    Insert0RBTree(root, node);

    return 0;
}


void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *other;

    while ((!node || node->color==BLACK) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color==RED)
            {
                do { other->color = BLACK; } while (0);
                do {parent->color = RED; } while (0);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
                do {other->color = RED; } while (0);
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color==BLACK)
                {
                    do { other->left->color = BLACK; } while (0);
                    do { other->color = RED; } while (0);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                do { other->color = parent->color; } while (0);
                do { parent->color = BLACK; } while (0);
                do { other->right->color = BLACK; } while (0);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color==RED)
            {
                do { other->color = BLACK; } while (0);
                do {parent->color = RED; } while (0);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
                do {other->color = RED; } while (0);
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color==BLACK)
                {
                    do { other->right->color = BLACK; } while (0);
                    do { other->color = RED; } while (0);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                do { other->color = parent->color; } while (0);
                do { parent->color = BLACK; } while (0);
                do { other->left->color = BLACK; } while (0);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        do { node->color = BLACK; } while (0);
}


void Delete0RBTree(RBRoot *root, Node *node)
{
    Node *child, *parent;
    int color;

    if ( (node->left!=NULL) && (node->right!=NULL) )
    {
        Node *replace = node;

        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        if (node->parent)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            root->node = replace;

        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            if (child)
                do { child->parent = parent; } while (0);
            parent->left = child;

            replace->right = node->right;
            do { node->right->parent = replace; } while (0);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
        free(node);

        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;

    if (child)
        child->parent = parent;

    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        rbtree_delete_fixup(root, child, parent);
    free(node);
}


int DeleteRBTree(RBRoot *root, Type key)
{
    Node *z, *node;

    if ((z = Search0RBTree(root->node, key) )!= NULL){
        Delete0RBTree(root, z);
        return 1;
    }
  		else
  		return 0;
}


void Destory0RBTree(RBTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        Destory0RBTree(tree->left);
    if (tree->right != NULL)
        Destory0RBTree(tree->right);

    free(tree);
}

void DestoryRBTree(RBRoot *root)
{
    if (root != NULL)
        Destory0RBTree(root->node);

    free(root);
}


void Print0RBTree(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    
            printf("%2d(B) is root\n", tree->key);
        else           
            printf("%2d(%s) is %2d %6s child\n", tree->key, tree->color==RED?"R":"B", key, direction==1?"right" : "left");

        Print0RBTree(tree->left, tree->key, -1);
        Print0RBTree(tree->right,tree->key,  1);
    }
}

void PrintRBTree1(RBTree tree)
{
	static int level = -1; //记录是第几层次
	int i;

	if (NULL == tree)
		return;

	level++;
	PrintRBTree1(tree->right);
	level--;

	level++;
	for (i = 0; i < level; i++)
		printf("     ");
	printf("%2d(%s)\n", tree->key, tree->color==RED?"R":"B");
	PrintRBTree1(tree->left);
	level--;
}
void Print1RBTree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
        PrintRBTree1(root->node);
}

void PrintRBTree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
        Print0RBTree(root->node, root->node->key, 0);
}

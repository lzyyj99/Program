#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"btree.h" 


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

//³õÊ¼»¯¶þ²æ²éÕÒÊ÷µÄ½áµã
btree* InitnodeBTree(int p_data)
{
	btree* node = (btree*)malloc(sizeof(btree));
	if (node == NULL)
	{
		return node;
	}
	node->data = p_data;
	node->lchild = NULL; 
	node->rchild = NULL;
	return node;
}

void M_orderBTree(btree* root)
{
	if (root != NULL)
	{
		if (root->lchild != NULL)
		{
			M_orderBTree(root->lchild);
		}
		printf("%d\t", root->data);
		if (root->rchild != NULL)
		{
			M_orderBTree(root->rchild);
		}
	}
}

btree* InsertBTree(btree* root, btree* node)
{
	if (root == NULL)
	{
		return node;
	}
	if (node == NULL)
	{
		return root;
	}
	if (node->data > root->data )
	{
		root->rchild = InsertBTree(root->rchild, node);
	}
	else if (node->data < root->data)
	{
		root->lchild = InsertBTree(root->lchild, node);
	}
    else printf("The node already exist!\n");
	return root;
}

////É¾³ý
//btree* DelBTree(btree* root, int p_data)
//{
//	if (root == NULL)
//	{
//		return NULL;
//	}
//	if (p_data < root->data)
//	{
//		root->lchild = DelBTree(root->lchild, p_data);
//	}
//	else if (p_data > root->data )
//	{
//		root->rchild = DelBTree(root->rchild, p_data);
//	}
//		else{
//		btree* temp;
//		if (root->lchild != NULL)
//		{
//			for (temp = root->lchild; temp->rchild != NULL; temp = temp->rchild);
//			root->data = temp->data;//Ìæ»»ÒªÉ¾³ýµÄ½áµã
//			DelBTree(temp, temp->data);//É¾³ýÌæ»»½áµã
//		}
//		else if (root->rchild != NULL)
//		{   
//			for (temp = root->rchild; temp->lchild != NULL; temp = temp->lchild);
//			root->data = temp->data;//Ìæ»»ÒªÉ¾³ýµÄ½áµã
//			DelBTree(temp, temp->data);//É¾³ýÌæ»»½áµã
//		}
//		else
//		{
//			free(root);
//			return NULL;
//		}
//    }
//	return root;
//}
btree* FindMin(btree* BST)
{
	while (BST)
	{
		if (!BST->lchild)
		{
			return BST;
		}
		else
		{
			BST = BST->lchild;
		}
	}
	return NULL;
}
btree* DelBTree(btree* Btree, int X)
{
	btree* Tmp;
	if (!Btree)
	{
		printf("Not Found\n");
	}
	else if (X < Btree->data)
	{
		Btree->lchild = DelBTree(Btree->lchild, X);   // é€’å½’åˆ é™¤å·¦å­æ ‘
	}
	else if (X > Btree->data)
	{
		Btree->rchild = DelBTree(Btree->rchild, X); 
	}
	else
	{
		if (Btree->lchild && Btree->rchild)
		{
			Tmp = FindMin(Btree->rchild);  
			Btree->data = Tmp->data;
			Btree->rchild = DelBTree(Btree->rchild, Btree->data);  // é€’å½’åˆ é™¤å³å­æ ‘æœ€å¤§å€¼
		}
		else
		{
			Tmp = Btree;
			if (!Btree->lchild)
			{
				Btree = Btree->rchild; 
			}
			else if (!Btree->rchild)
			{
				Btree = Btree->lchild;   
			}           
		}
	}
	return Btree;
}

//Ñ°ÕÒ½áµã
int Find0BTree(btree* root,int fnum)
{
	if (root == NULL)
	{
		return 0; 
	}
	if (fnum < root->data)
	{
		if(Find0BTree(root->lchild, fnum)==1)
		return 1;
		else return 0;
	}
	else if (fnum > root->data)
	{
		if(Find0BTree(root->rchild, fnum)==1){
			return 1;
		}
		else return 0;
	}
	else {
		return 1;
	}
}

int FindBTree(btree* root,int fnum)
{
	if (root == NULL)
	{
		printf("NULL\n");
		return 0; 
	}
	if (fnum < root->data)
	{
		if(FindBTree(root->lchild, fnum)==1)
		return 1;
		else return 0;
	}
	else if (fnum > root->data)
	{
		if(FindBTree(root->rchild, fnum)==1){
			return 1;
		}
		else return 0;
	}
	else {
		printf("The key already exists!\n");
		return 1;
	}
	return 1;
}
void PrintBTree(btree* root)
{
	static int level = -1; //¼ÇÂ¼ÊÇµÚ¼¸²ã´Î
	int i;

	if (NULL == root)
		return;

	level++;
	PrintBTree(root->rchild);
	level--;

	level++;
	for (i = 0; i < level; i++)
		printf("  ");
	printf("%2d\n", root->data);
	PrintBTree(root->lchild);
	level--;
}


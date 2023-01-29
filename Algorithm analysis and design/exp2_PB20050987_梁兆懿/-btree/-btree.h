#ifndef _BTREE_H
#define _BTREE_H
#define MAXM 5  
#define m 4
#define Max m-1
#define Min (m-1)/2        
             
typedef int KeyType;              

typedef struct node{               
    int keynum;                 
    KeyType key[MAXM];            
    struct node *parent;           
    struct node *ptr[MAXM];         
}BTNode,*BTree;

typedef struct{                     
    BTNode *pt;                    
    int i;                         
    int tag;                        
}NODE0;

typedef struct LNode{              
    BTree data;                    
    struct LNode *next;            
}LNode, *LinkList;

int InitBTree(BTree &root);      
                              
int SearchBTNode(BTNode *p,KeyType k);  
                     
NODE0 SearchBTree(BTree t,KeyType k);                        
      
void InsertBTree(BTree &t,int i,KeyType k,BTNode *p);        
                                                                                                                                                                                         
int FindBTNode(BTNode *p,KeyType k,int &i);                 
                 
void BTreeDelete(BTree &t,KeyType k); 
                         
void DestroyBTree(BTree &t);                                  
     
int PrintBTree(BTree t);                                                                                      
#endif 


#ifndef BPTree_h
#define BPTree_h
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define M 4
 
typedef struct BPNode *BPTree,*Position;
struct BPNode{
    int KeyNum;
    int Key[M + 1];
    BPTree Children[M + 1];
    BPTree Next;
};
 

BPTree InitializeBPTree();

BPTree InsertBPTree(BPTree T,int Key);

BPTree RemoveBPTree(BPTree T,int Key);

void TravelBPTree(BPTree T);

void TravelDataBPTree(BPTree T);

BPTree DeleteBPTree(BPTree T);

int SearchBPTree(BPTree T,int key);

int num_rand(int a[],int size,int randsize);
#endif 

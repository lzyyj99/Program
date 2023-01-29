#include<stdio.h>¡¢
#include<stdlib.h> 
#include"btree.c"
#include"btree.h"
#include <time.h>

int main()

{   int a[100] ;
	num_rand(a,100,1000);
	int i; 
	for(i=0;i<100;i++){
		printf("%d  ",a[i] );
	}
	printf("\n\n");
   	btree* root = (btree*)malloc(sizeof(btree));
	root = NULL;
    for(i=0;i<100;i++){
  		   	btree* node = InitnodeBTree(a[i]);
			root = InsertBTree(root, node);
		}
	printf("M_orderBTree£º\n\t");
	M_orderBTree(root);
	printf("\n\n");

	for(i=0;i<=95;i++)
		DelBTree(root, a[i]);
	printf("M_orderBTree£º\n\t");
	M_orderBTree(root);
	printf("\n\n");
	
	FindBTree(root,30);
	FindBTree(root,83);
	printf("\n\n");

    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
	btree* root1 = (btree*)malloc(sizeof(btree));
	root1 = NULL;
	for(i=0;i<20;i++){
  		   	btree* node = InitnodeBTree(b[i]);
			root1 = InsertBTree(root1, node);
		}
		printf("\n\n");
	printf("M_orderBTree£º\n\t");
	M_orderBTree(root1);
    printf("\n____________________________________________________________\n");
	
    PrintBTree(root1); 
    printf("\n____________________________________________________________\n");
    for(i=5;i<10;i++)
    	DelBTree(root1,b[i]) ;
    printf("after delete:\n");
    PrintBTree(root1); 
    printf("\n____________________________________________________________\n");
    
	int c[20000] ;
	num_rand(c,20000,100000); 

	printf("\n\n");
	btree* root2 = (btree*)malloc(sizeof(btree));
	root = NULL;

    for(i=0;i<1000;i++){
  		   	btree* node = InitnodeBTree(c[i]);
			root2 = InsertBTree(root2, node);
		}
    clock_t begin = 0, end = 0;
    begin = clock();
    for(i=1000;i<20000;i++){
  		   	btree* node = InitnodeBTree(c[i]);
			root2 = InsertBTree(root2, node);
		}
    end = clock();
    printf("\nInsert time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    	M_orderBTree(root2);
    begin = clock();
    for(i=1000;i<20000;i++)
    	DelBTree(root2,c[i]) ;
    end = clock();
    printf("\nDelete time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    for(i=1000;i<20000;i++){
  		   	btree* node = InitnodeBTree(c[i]);
			root2 = InsertBTree(root2, node);
		}
    
    begin = clock();
    for(i=1000;i<20000;i++)
    		Find0BTree(root2,c[i]);
    end = clock();
    printf("\nSearch time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
	return 0;
} 

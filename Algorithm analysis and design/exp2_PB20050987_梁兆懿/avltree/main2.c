#include <stdio.h>
#include "avltree.h"
#include "avltree.c" 
#include <time.h>


int main()

{   int a[100] ;
	num_rand(a,100,1000);
	int i; 
	for(i=0;i<100;i++){
		printf("%d  ",a[i] );
	}
	printf("\n\n");
    AVLTreeN root = NULL;

    for (i =0; i<100; i++) {
        root = InsertAVLTree(root, a[i]);
    }

	printf("M_orderBTree£º\n");
	InorderAVLTree(root);
	printf("\n\n");

	for(i=50;i<95;i++)
		root=DeleteAVLTree(root, a[i]);
	printf("M_orderBTree£º\n");
	InorderAVLTree(root);
	printf("\n\n");
	
	if(SearchAVLTree(root, 42)!=NULL){
		printf("\nThe key %d is already exist!",10);
	}else
	printf("\nsearch fail!");
	if(SearchAVLTree(root, 540)!=NULL){
		printf("\nThe key is already exist!");
	}else
	printf("\nsearch:%d fail!",540);
	printf("\n\n");

    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
    AVLTreeN root1 = NULL;

    for (i = 0; i < 20; i++) {
        root1 = InsertAVLTree(root1, b[i]);
    }
	printf("\n\n");
	printf("M_orderBTree£º\n\t");
	InorderAVLTree(root1);
    printf("\n____________________________________________________________\n");
	
    PrintAVLTree(root1); 
    printf("\n____________________________________________________________\n");
    for(i=5;i<10;i++)
    	DeleteAVLTree(root1,b[i]) ;
    printf("after delete:\n");
    PrintAVLTree(root1); 
    printf("\n____________________________________________________________\n");
	
	int c[20000] ;
	num_rand(c,20000,100000); 

	printf("\n\n");
    AVLTreeN root2 = NULL;

    for (i =0; i<1000; i++) {
        root2 = InsertAVLTree(root2, c[i]);
    }
    clock_t begin = 0, end = 0;
    begin = clock();
    for(i=1000;i<20000;i++)
		root2 = InsertAVLTree(root2, c[i]);
    end = clock();
    printf("\nInsert time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	DeleteAVLTree(root2, c[i]);
    end = clock();
    printf("\nDelete time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    for(i=1000;i<20000;i++)
		root2 = InsertAVLTree(root2, c[i]);
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	SearchAVLTree(root2, c[i]);
    end = clock();
    printf("\nSearch time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
	return 0;
} 

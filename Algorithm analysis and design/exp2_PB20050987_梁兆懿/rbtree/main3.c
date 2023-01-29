#include <stdio.h>
#include "rbtree.h"
#include "rbtree.c" 
#include <time.h>

int main()
{   int a[100] ;
	num_rand(a,100,1000);
	int i; 
	for(i=0;i<100;i++){
		printf("%d  ",a[i] );
	}
	printf("\n\n");
	RBRoot *root=NULL;
    root = CreateRBTree();

    for (i =0; i<100; i++) {
        InsertRBTree(root, a[i]);
    }

	printf("M_orderBTree£º\n\t");
	InorderRBTree(root);
	printf("\n\n");

	for(i=0;i<95;i++)
		DeleteRBTree(root, a[i]);
	printf("M_orderRBTree£º\n\t");
	InorderRBTree(root);
	printf("\n\n");
	
	if(SearchRBTree(root, 116)!=-1){
		printf("\nThe key %d is already exist!",116);
	}else
	printf("\nsearch 116 fail!");
	if(SearchRBTree(root, 540)!=-1){
		printf("\nThe key is already exist!");
	}else
	printf("\nsearch:%d fail!",540);
	printf("\n\n");

    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
	
	RBRoot *root1=NULL;
    root1 = CreateRBTree();
    for (i = 0; i < 20; i++) {
        InsertRBTree(root1, b[i]);
    }
	printf("\n\n");
	printf("M_orderBTree£º\n\t");
	InorderRBTree(root1);
    printf("\n____________________________________________________________\n");
	
    Print1RBTree(root1); 
    printf("\n____________________________________________________________\n");
    for(i=5;i<10;i++)
    	DeleteRBTree(root1,b[i]) ;
    printf("after delete:\n");
    Print1RBTree(root1); 
    printf("\n____________________________________________________________\n");
    
	int c[20000] ;
	num_rand(c,20000,100000); 

	printf("\n\n");
	RBRoot *root2=NULL;
    root2 = CreateRBTree();
    for (i = 0; i < 1000; i++) {
        InsertRBTree(root2, c[i]);
    }

    clock_t begin = 0, end = 0;
    begin = clock();
    for(i=1000;i<20000;i++)
        InsertRBTree(root2, c[i]);
    end = clock();
    printf("\nInsert time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    begin = clock();
    for(i=1000;i<20000;i++)
		DeleteRBTree(root2, c[i]);
    end = clock();
    printf("\nDelete time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    for(i=1000;i<20000;i++)
        InsertRBTree(root2, c[i]);
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	SearchRBTree(root2, c[i]);
    end = clock();
    printf("\nSearch time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
	return 0;
} 

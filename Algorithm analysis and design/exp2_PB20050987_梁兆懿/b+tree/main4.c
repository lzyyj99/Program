#include <stdio.h>
#include "bptree.h"
#include "bptree.c"
#include <time.h>

int main()

{   int a[100] ;
	num_rand(a,100,1000);
	int i; 
	for(i=0;i<100;i++){
		printf("%d  ",a[i] );
	}
	printf("\n\n");
    BPTree T;
    T = InitBPTree();

    for (i =0; i<100; i++) {
        T = InsertBPTree(T, a[i]);
    }

	printf("TravelBPTree£º\n");
    TravelBPTree(T);
	printf("\n\n");

	for(i=0;i<95;i++)
        T = RemoveBPTree(T, a[i]);
	printf("TravelBPTree£º\n");
    TravelBPTree(T);
	printf("\n\n");
	
    if(SearchBPTree(T, 116)!=1)
		printf("search fail!\n");
		else
		printf("The key is already in the tree!\n");
	    if(SearchBPTree(T, 980)!=1)
		printf("search fail!\n");
    DeleteBPTree(T);

    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
    BPTree T1;
    T1 = InitBPTree();

    for (i = 0; i < 20; i++) {
        T1 = InsertBPTree(T1, b[i]);
    }
	printf("\n\n");
	printf("TravelBPTree£º\n\t");
    TravelBPTree(T1); 
    printf("\n____________________________________________________________\n");
	
    TravelBPTree(T1); 
    printf("\n____________________________________________________________\n");
    for(i=5;i<15;i++)
    	T1 = RemoveBPTree(T1, b[i]) ;
    printf("after delete:\n");
    TravelBPTree(T1);
    printf("\n____________________________________________________________\n");
    
    int c[20000] ;
	num_rand(c,20000,100000); 

	printf("\n\n");
    BPTree T2;
    T2 = InitBPTree();

    for (i =0; i<1000; i++) {
        T2 = InsertBPTree(T2, c[i]);
    }
    clock_t begin = 0, end = 0;
    begin = clock();
    for(i=1000;i<20000;i++)
    	InsertBPTree(T2, c[i]);
    end = clock();
    printf("\nInsert time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	T2 = RemoveBPTree(T2, c[i]);
    end = clock();
    printf("\nDelete time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    for(i=1000;i<20000;i++)
    	InsertBPTree(T2, c[i]);;
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	SearchBPTree(T2, c[i]);
    end = clock();
    printf("\nSearch time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
	return 0;
} 

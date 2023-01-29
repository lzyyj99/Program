#include <bits/stdc++.h>
#define RAND_MAX 10000
#define SIZE 100000
#define MAXR 4 

int Create_Rand_Num(int temp[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        temp[i]=rand()%RAND_MAX;
    }
}


    
int Insert_Sort(int a[])
{  
    int j = 0;
    int temp = 0;
    for(int i=1;i<SIZE;i++)
    {
        if(a[i]<a[i-1])
        {
            j = i-1;
            temp = a[i];
            while(j>-1&&temp<a[j])
            {
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = temp;
        }
    }
}

int _MergeSort(int a[], int left, int right,int* tmp)
{
	if (left >= right)
	{
		return 0;
	}

	int mid = (left + right) >> 1;
	_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);

	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	int index = left;

	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
            tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	
	for (int i = left; i <=right ; i++)
	{
		a[i] = tmp[i];
	}
}
//归并排序 
void Merge_Sort(int a[])
{ 
	int* tmp = (int*)malloc(sizeof(int)*SIZE);

	_MergeSort(a, 0, SIZE-1, tmp);

	free(tmp);
}
//快排 
int Quick_Sort(int a[],int L,int H)
{
    int i, j, temp, k;
    i = L;
    j = H;
    k = a[L];
    if(i>=j)
    {
        return 0;
    }
     while (i < j)
        {
            while(i < j && a[j] >= k)     
            {
                j--;
            }
 
            if(i < j)
            {
                a[i++] = a[j];
            }
 
            while(i < j && a[i] < k)     
            {
                i++;
            }
 
            if(i < j)
            {
                a[j--] = a[i];
            }
        }
        a[i] = k;
    Quick_Sort(a, L, i-1);
    Quick_Sort(a, i+1, H);
}
//堆排序 
int HeapAdjust(int a[],int s,int m)
{
    int rc,j;
    rc=a[s];
    for(j=2*s;j<=m;j=j*2)
    {
        if(j<m&&a[j]<a[j+1]) j++;
        if(rc>a[j]) break;
        a[s]=a[j];s=j;
    }
    a[s]=rc;
}
int Heap_Sort(int a[],int n)
{
    int temp,i,j;
    for(i=n/2;i>0;i--)
    {
        HeapAdjust(a,i,n);
    }
    for(i=n;i>0;i--)
    {
        temp=a[1];
        a[1]=a[i];
        a[i]=temp;
        HeapAdjust(a,1,i-1);
    }
}


int GetDigit(int M, int i) 
{
	while(i > 1)
	{
		M /= 10;
		i--;
	}
	return M % 10;
}

// 基数排序
int Radix_Sort(int a[])
{
    int temp[SIZE] = {0};
    int i, j, k;
    int count[10] = {0};
    int radix = 1;
    for(i = 1; i <= MAXR; i++)
   {
      memset(count, 0, sizeof(count));
      for(j = 0; j < SIZE;j++)
      {
        k = (a[j]/radix)%10;
        count[k]++;
      }
      for(j = 1; j < 10; j++)
      {
        count[j] = count[j-1] + count[j];
      }
      for(j = SIZE -1; j >= 0; j--)
      {
        k = (a[j]/radix)%10;
        temp[count[k]-1] = a[j];
        count[k]--;
      }
      for(j = 0; j < SIZE; j++)
      {
        a[j] = temp[j];
      }
      memset(count, 0, sizeof(count));
      radix *= 10;
    }
}

 
//桶排序   
int BucketSort(int* arr , int len)
{   int maxVal = arr[0];
        for(int i = 1; i < len; i++) 
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    int tmpArrLen =maxVal + 1;
    int tmpArr[tmpArrLen];  //获得空桶大小
    int i, j;
    
    for( i = 0; i < tmpArrLen; i++) 
        tmpArr[i] = 0;
    
    for(i = 0; i < len; i++)  
        tmpArr[ arr[i] ]++;
    
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) 
        {
            arr[j ] = i;  //从不是空的桶子里把项目再放回原来的序列中。
            j++;
            tmpArr[i]--;
        }
    }
}
//降序桶排序 
int BucketSort0(int* arr , int len)
{   int maxVal = arr[0];
        for(int i = 1; i < len; i++) 
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    int tmpArrLen =maxVal + 1;
    int tmpArr[tmpArrLen]; 
    int i, j;
    
    for( i = 0; i < tmpArrLen; i++) 
        tmpArr[i] = 0;
    
    for(i = 0; i < len; i++)  
        tmpArr[ arr[i] ]++;
    
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) 
        {
            arr[SIZE-j-1] = i;  
            j++;
            tmpArr[i]--;
        }
    }
}

int main()
{
    int temp[SIZE];
    int a[SIZE];
    Create_Rand_Num(temp,SIZE);
//    for(int i=0;i<100;i++ ){
//    int temp0[1000];
//	Create_Rand_Num(temp0,1000);
//	BucketSort(temp0, 1000);
//	for(int j=0;j<1000;j++){
//		temp[i*1000+j]=temp0[j];
//	}
//}//部分升序 
    
//    BucketSort0(temp, SIZE); //降序操作  
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",temp[i]);
//    }
    
    memcpy(a,temp,sizeof temp) ;
    clock_t begin = 0, end = 0;
    begin = clock();
    Insert_Sort(a);
    end = clock();
    printf("\nInsert_Sort time: %5.4f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",a[i]);
//    }

    memcpy(a,temp,sizeof temp) ;//temp[]是初始数组，a[]是用于排序的数组 
    begin = clock();
    Merge_Sort(a);
    end = clock();
    printf("\nMerge_Sort time: %5.4f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",a[i]);
//    }
 
    memcpy(a,temp,sizeof temp) ;
    begin = clock();
    Quick_Sort(a,0,SIZE-1);
    end = clock();
    printf("\nQuick_Sort time: %5.4f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",a[i]);
//    }
 
    int c[SIZE+1];
    for(int i = 1;i <=SIZE; i++)
    {
       c[i]=temp[i-1];
    }
    begin = clock();
    Heap_Sort(c,SIZE);
    end = clock();
    printf("\nHeap_Sort time: %5.4f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 1;i <=SIZE; i++)
//    {
//        printf("%d  ",c[i]);
//    }
    int b[SIZE];
    memcpy(b,temp,sizeof temp) ;
    begin = clock();
    Radix_Sort(b);
    end = clock();
    printf("\nRadix_Sort time: %5.4f\n",(float)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",b[i]);
//    }
    memcpy(a,temp,sizeof temp) ;
    begin = clock();
    BucketSort(a, SIZE);
    end = clock();
    printf("\nBucket_Sort time: %5.4f\n",(double)(end-begin)/CLOCKS_PER_SEC);
//    for(int i = 0;i <SIZE; i++)
//    {
//        printf("%d  ",a[i]);
//    }
    return 0;
}

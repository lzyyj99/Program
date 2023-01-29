#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream> 
#include <queue>  
#include <ctime>
using namespace std;

#define SIZE 20  //背包容量 
#define C 40     //最大重量 
#define MAX_WEIGHT 5  //物品最大重量 
#define MAX_VAULE 7	  //物品最大价值 

int dp[SIZE+1][C+1];        //动态规划存储数组 
int w[SIZE];				//物品的体积
int v[SIZE];				//物品的价值
int item[SIZE+1];			//最优解情况
double cw=0;				//当前物品总重
double cv=0;				//当前物品总价值
int bestp=0;				//当前最大价值
int bestx[SIZE+1];			//暂时存放最优解
int total=1;				 //解空间中的节点数累计，全局变量 
struct nodetype    		    //队列中的结点类型
{
    int no;       	   
    int i;       	  
    int w;       	  
    int v;       	    
    int x[SIZE+1];        
    double ub;     	   
};

void Initialize(){
	int i;
	cw=0;			
	cv=0;				
	bestp=0;			
	total=1;
	for(i=0;i<SIZE;i++)
	bestx[SIZE+1];
	for(i=0;i<SIZE;i++)
	item[i]=0;
}

int Create_Rand_Num(int temp[],int size,int randx)
{
    int i;
    for(i=0;i<size;i++)
    {
        temp[i]=rand()%randx;
        while(temp[i]==0){
        	temp[i]=rand()%randx;
		}
    }
}

void Printf(){//打印函数 
	int i;
	printf("物品重量：\n");
 	for(i=0;i<SIZE;i++){
 		printf("%d\t",w[i]);
	 }
	printf("\n物品价值：\n");
	for(i=0;i<SIZE;i++){
 		printf("%d\t",v[i]);
	 }
	printf("\n");
}

int max(int a,int b)//求最大值 
{
   if(a>=b)
       return a;
   else return b;
}

void swap(int t[],int i,int j){//交换函数 
	int temp;
	temp = t[i];
	t[i] = t[j];
	t[j] = temp;
}

void swap0(float t[],int i,int j){//交换函数
	float temp;
	temp = t[i];
	t[i] = t[j];
	t[j] = temp;
}

void strcpy0(int *a,int *b, int n){
	int i;
	b[0]=0;
	for(i=0; i<n;i++)
	b[i+1] =a[i];
	return;
}

void strcpy1(int *a,float *b, int n){
	int i;
	for(i=0; i<n;i++)
	b[i] =float(a[i]);
	return;
}

void sort0(float t[],int w[],int v[],int n){
	int max1;
	for(int i=1;i<n+1;i++){
		max1=i;
		for(int j=i+1;j<n+1;j++){
			if(t[j]>t[max1]||(w[j]<w[max1]&&t[j]==t[max1])){
				max1=j;
			}
		}
		swap0(t,i,max1);
		swap(w,i,max1);
		swap(v,i,max1);
	}
}

void sort1(float t[],float w[],float v[],int n){
	int max1;
	for(int i=0;i<n;i++){
		max1=i;
		for(int j=i+1;j<n;j++){
			if(t[j]>t[max1]||(w[j]<w[max1]&&t[j]==t[max1])){
				max1=j;
			}
		}
		swap0(t,i,max1);
		swap0(w,i,max1);
		swap0(v,i,max1);
	}
}

int Divide0(int i,int j){//分治法 
    if(j <= 0) return 0;
	if(i == -1) return 0;
	if(j<w[i])
        return Divide0(i - 1, j);
    else
    return max(Divide0(i - 1, j), Divide0(i - 1, j - w[i]) + v[i]);
}

void Divide(){//分治法 
	printf("\n------------------------------------\n");
	int s;
	Initialize();
	clock_t begin, end;
    begin = clock();
    s = Divide0(SIZE-1,C);
    printf("\n分治法：\n最大物品价值为:%d\n" , s);
    end = clock();
    printf("time: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
}

int DPprint(int n){
            int i,j=C;
            for(i=n;i>=1;i--)
            {
            if(dp[i][j]>dp[i-1][j])
                {
					item[i]=1;
					j=j-w[i-1];
                }
            else
                item[i]=0;
            }
            printf("选中的物品是:\n");
            for(i=1;i<=n;i++)
                printf("%d ",item[i]);
            printf("\n");      
}
 
int DP(int n,int item[])
{
    int i,j;
    for(i=0;i<=n;i++)
        dp[i][0]=0;
    for(j=0;j<=C;j++)
        dp[0][j]=0;
    for(i=1;i<=n;i++)
	{
        for(j=1;j<=C;j++)
		{
            if(j<w[i-1])
			{
				dp[i][j]=dp[i-1][j];
			}
			
            else
			{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i-1]]+v[i-1]);
			}
		}
	}
	DPprint(n);
	return dp[n][C];
}

void Dynamicpro(){
	printf("\n------------------------------------\n");
	int s;
	Initialize();
	clock_t begin, end;
    begin = clock();
	printf("动态规划法：\n");
 	s=DP(SIZE,item);
    printf("最大物品价值为:\n");
    printf("%d\n",s);
    end = clock();
    printf("time: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
}

void greedy() {
	float tem[SIZE],temw[SIZE],temv[SIZE];
	int i,j;
	float c=C,maxvalue=0;
	strcpy1(w,temw,SIZE);
	strcpy1(v,temv,SIZE);
	for(i=0;i<SIZE;i++){
		tem[i] = temv[i]/temw[i];
	}
	sort1(tem,temw,temv,SIZE);
	for(j=0;j<SIZE;j++){
		if(w[j]>=c)continue;
		item[j]=1;
		c=c-temw[j];
		maxvalue=maxvalue+temv[j];
	} 

    printf("\n贪心算法：");
    for(i=0;i<SIZE;i++){
    	printf("\n%.0f %.0f %.3f %d",temw[i],temv[i],tem[i],item[i]);
	}
	printf("\n物品最大价值：%.3f",maxvalue);
	return ; 
}

 
void Greedy(){
	printf("\n------------------------------------\n");
	Initialize();
	clock_t begin, end;
    begin = clock();
	greedy();
	end = clock();
    printf("\ntime: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
}

double bound(float temw[],float temv[],int i)
{   
    double leftw= C-cw;
    double b = cv;
    while(i<SIZE && temw[i]<=leftw)
    {
        leftw-=temw[i];
        b+=temv[i];
        i++;
    }
    if(i<SIZE)
        b+=temv[i]/temw[i]*leftw;
    return b;
}

void backtrack(float temw[],float temv[],int i)
{   
    //bound(temw,temv,i);
    if(i>=SIZE) 
    {
        bestp = cv;
        return;
    }
    if(cw+temw[i]<=C)
    {
        cw+=temw[i];
        cv+=temv[i];
        item[i]=1;
        backtrack(temw,temv,i+1);
        cw-=temw[i];
        cv-=temv[i];
    }
    if(bound(temw,temv,i+1)>bestp)
        backtrack(temw,temv,i+1);
}

void Backtrack(){ 
	printf("\n------------------------------------\n");
	Initialize();
	clock_t begin, end;
    begin = clock();
	float tem[SIZE],temw[SIZE],temv[SIZE];
	int j;
	float c=C;
	strcpy1(w,temw,SIZE);
	strcpy1(v,temv,SIZE);
	for(j=0;j<SIZE;j++){
		tem[j] = temv[j]/temw[j];
	}
	sort1(tem,temw,temv,SIZE);
	cv=0;
	cw=0;
	bestp=0;
	backtrack(temw,temv,0);
	printf("\n\n回溯法：\n最大物品价值为：%d\n",bestp);
    printf("选中的物品是：");
    for(int i=0;i<SIZE;i++)
    {
        printf("\n%.0f %.0f %d",temw[i],temv[i],item[i]);
	}
	end = clock();
    printf("\ntime: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
} 

void bound1(nodetype &e,int temw[],int temv[])     
{	
    double c=C;
    int i=e.i+1;       
    int sumw=e.w;
    double sumv=e.v;
    while((sumw+temw[i]<=c)&&i<=SIZE) 
    {
        sumw+=temw[i];
        sumv+=temv[i];
        i++;
    }
    if(i<=SIZE)           
    e.ub=sumv+(c-sumw)*temv[i]/temw[i];
    else e.ub=sumv; 
} 

void enqueue(nodetype e,queue<nodetype> &qu,int temw[],int temv[])
{
    if(e.i==SIZE)               
    {
        if(e.v>bestp)       
        {
            bestp=e.v;
            for(int j=1;j<=SIZE;j++)
            item[j]=e.x[j];
        }
    }
    else qu.push(e);        
} 

void bfs(int temw[],int temv[])
{
    int j;
    nodetype e,e1,e2;
    queue<nodetype> qu;
    
    e.i=0;
    e.w=0;
    e.v=0;
    e.no=total++;
    
    for(j=1;j<=SIZE;j++)
    e.x[j]=0;
    bound1(e,temw,temv);
    qu.push(e);
    
    while(!qu.empty())
    {
        e=qu.front();qu.pop();  
        if(e.w+temw[e.i+1]<=C)      
        {
            e1.no=total++;     
            e1.i=e.i+1;
            e1.w=e.w+temw[e1.i];
            e1.v=e.v+temv[e1.i];
            for(j=1;j<=SIZE;j++)
            e1.x[j]=e.x[j];
            e1.x[e1.i]=1;
            bound1(e1,temw,temv);      
            enqueue(e1,qu,temw,temv);  
        }
        e2.no=total++;
        e2.i=e.i+1;
        e2.w=e.w;
        e2.v=e.v; 
        for(j=1;j<=SIZE;j++)
            e2.x[j]=e.x[j];
        e2.x[e2.i]=0;
        bound1(e2,temw,temv);
        if(e2.ub>bestp)       
        enqueue(e2,qu,temw,temv);    
    }
} 

void output(int temw[],int temv[])
{
    printf("\n\n分支限界法\n物品最大价值是:%d\n选取的物品是：",bestp);
    for(int i=1;i<=SIZE;i++)
        printf("\n%d %.d  %d",temw[i],temv[i],item[i]);

}

void Boundfs(){
	printf("\n------------------------------------\n");
	Initialize();
	clock_t begin, end;
    begin = clock();
	int temw[SIZE+1],temv[SIZE+1],j;
	float tem[SIZE+1];
	bestp=0;
	memset(bestx,0,sizeof(bestx));
	strcpy0(w,temw,SIZE);
	strcpy0(v,temv,SIZE);
	for(j=1;j<SIZE+1;j++){
		tem[j] = temv[j]/temw[j];
	}
	sort0(tem,temw,temv,SIZE);
	bfs(temw,temv);
	output(temw,temv);
	end = clock();
    printf("\ntime: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
}

int MonteCarlo0(){
	bestp = 0;
	long int i=0;
	int key,j,nowvaule=0;
	//double prob = double(MAX_VAULE/MAX_WEIGHT*1/5);
	int item0[SIZE]; 
	float tem[SIZE];
	//printf ("%lf",prob);
	for(j=0;j<SIZE;j++){
		tem[j] =float(v[j]/w[j]);
	}
	for(int i=0;i<=10000;i++){
		int nowvaule = 0;
		int leftc = C;
		memset(item0,0,sizeof(item0));
		while(1){
			key = rand()%SIZE;
			if( item0[key]!=1 ){
			//	if( tem[key]>float(rand()%10/10*prob)) {
				if( w[key] <= leftc){
					nowvaule = nowvaule + v[key];
					leftc = leftc - w[key];
					item0[key] = 1;
				}
				else if(leftc <=2) break;
			}
		}
		//}
		if(nowvaule>bestp){
			bestp = nowvaule;
			for(i=0;i<SIZE;i++)
				item[i] = item0[i];
		}
	//	printf("%d ",nowvaule);
	}
	printf("\n\n蒙特卡洛算法：\n物品最大价值：%d\n",bestp);
	printf("选中的物品是:\n");
    for(i=0;i<SIZE;i++)
        printf("%d ",item[i]);
    printf("\n"); 
	return 0;
}

void MonteCarlo(){
	printf("\n------------------------------------\n");
	Initialize();
	clock_t begin, end;
    begin = clock();
	MonteCarlo0();
	end = clock();
    printf("time: %.3fs\n" , double(end - begin) / CLOCKS_PER_SEC) ;
}

int main()
{
 	Create_Rand_Num(w,SIZE,MAX_WEIGHT);
 	Create_Rand_Num(v,SIZE,MAX_VAULE);
    Printf();
	Dynamicpro();
	Divide();
    Greedy();
	Backtrack();
    Boundfs();
    MonteCarlo(); 
    return 0;
}

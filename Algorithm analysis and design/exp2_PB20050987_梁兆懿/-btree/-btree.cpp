#include<bits/stdc++.h>
#include <iostream>
#include"-btree.h"
#include <time.h>

int InitBTree(BTree &root){
    root=NULL;
    return 1;
}

int SearchBTNode(BTNode *p,KeyType k){ 
    int i=0;
    for(i=0;i<p->keynum&&p->key[i+1]<=k;i++);
    return i;
}


NODE0 SearchBTree(BTree t,KeyType k){

    BTNode *p=t,*q=NULL;                            //初始化结点p和结点q,p指向待查结点,q指向p的双亲
    int found_tag=0;                                //设定查找成功与否标志 
    int i=0;                 
    NODE0 r;                                       //设定返回的查找结果 

    while(p!=NULL&&found_tag==0){
        i=SearchBTNode(p,k);                        //在结点p中查找关键字k,使得p->key[i]<=k<p->key[i+1]
        if(i>0&&p->key[i]==k)                       //找到待查关键字
            found_tag=1;                            //查找成功 
        else{                                       //查找失败 
            q=p;                            
            p=p->ptr[i];
        }
    }

    if(found_tag==1){                               //查找成功
        r.pt=p;
        r.i=i;
        r.tag=1;
    }
    else{                                           //查找失败
        r.pt=q;
        r.i=i;
        r.tag=0;
    }

    return r;                                       //返回关键字k的位置(或插入位置)
}


void InsertBTNode(BTNode *&p,int i,KeyType k,BTNode *q){
    int j;
    for(j=p->keynum;j>i;j--){                     
        p->key[j+1]=p->key[j];
        p->ptr[j+1]=p->ptr[j];
    }
    p->key[i+1]=k;
    p->ptr[i+1]=q;
    if(q!=NULL) 
        q->parent=p;
    p->keynum++;
}


void SplitBTNode(BTNode *&p,BTNode *&q){
    int i;
    int s=(m+1)/2;
    q=(BTNode *)malloc(sizeof(BTNode));        

    q->ptr[0]=p->ptr[s];                            
    for(i=s+1;i<=m;i++){
        q->key[i-s]=p->key[i];
        q->ptr[i-s]=p->ptr[i];
    }
    q->keynum=p->keynum-s;                
    q->parent=p->parent;
    for(i=0;i<=p->keynum-s;i++)                   
        if(q->ptr[i]!=NULL) 
            q->ptr[i]->parent=q;
    p->keynum=s-1;                               
}


void NewRoot(BTNode *&t,KeyType k,BTNode *p,BTNode *q){
    t=(BTNode *)malloc(sizeof(BTNode));      
    t->keynum=1;
    t->ptr[0]=p;
    t->ptr[1]=q;
    t->key[1]=k;
    if(p!=NULL)                             
        p->parent=t;
    if(q!=NULL) 
        q->parent=t;
    t->parent=NULL;
}


void InsertBTree(BTree &t,int i,KeyType k,BTNode *p){
    BTNode *q;
    int finish_tag,newroot_tag,s;                  
    KeyType x;
    if(p==NULL)                                    
        NewRoot(t,k,NULL,NULL);                     //生成仅含关键字k的根结点t
    else{
        x=k;
        q=NULL;
        finish_tag=0;       
        newroot_tag=0;
        while(finish_tag==0&&newroot_tag==0){
            InsertBTNode(p,i,x,q);                  //将关键字x和结点q分别插入到p->key[i+1]和p->ptr[i+1]
            if (p->keynum<=Max) 
                finish_tag=1;                       //插入完成
            else{         
                s=(m+1)/2;
                SplitBTNode(p,q);                   //分裂结点 
                x=p->key[s];
                if(p->parent){                      //查找x的插入位置
                    p=p->parent;
                    i=SearchBTNode(p, x);
                }
                else                                //没找到x，需要新结点 
                    newroot_tag=1;
            }
        }
        if(newroot_tag==1)                          //根结点已分裂为结点p和q 
            NewRoot(t,x,p,q);                       //生成新根结点t,p和q为子树指针
    }
}


void Remove(BTNode *p,int i){
//从p结点删除key[i]和它的孩子指针ptr[i]
    int j;
    for(j=i+1;j<=p->keynum;j++){                    //前移删除key[i]和ptr[i]
        p->key[j-1]=p->key[j];
        p->ptr[j-1]=p->ptr[j];
    }
    p->keynum--;
}


void Substitution(BTNode *p,int i){
//查找被删关键字p->key[i](在非叶子结点中)的替代叶子结点(右子树中值最小的关键字) 
    BTNode *q;
    for(q=p->ptr[i];q->ptr[0]!=NULL;q=q->ptr[0]);
    p->key[i]=q->key[1];                            //复制关键字值
}


void MoveRight(BTNode *p,int i){
/*将双亲结点p中的最后一个关键字移入右结点q中
将左结点aq中的最后一个关键字移入双亲结点p中*/ 
    int j;
    BTNode *q=p->ptr[i];
    BTNode *aq=p->ptr[i-1];

    for(j=q->keynum;j>0;j--){                       //将右兄弟q中所有关键字向后移动一位
        q->key[j+1]=q->key[j];
        q->ptr[j+1]=q->ptr[j];
    }

    q->ptr[1]=q->ptr[0];                            //从双亲结点p移动关键字到右兄弟q中
    q->key[1]=p->key[i];
    q->keynum++;

    p->key[i]=aq->key[aq->keynum];                  //将左兄弟aq中最后一个关键字移动到双亲结点p中
    p->ptr[i]->ptr[0]=aq->ptr[aq->keynum];
    aq->keynum--;
}


void MoveLeft(BTNode *p,int i){
/*将双亲结点p中的第一个关键字移入左结点aq中，
将右结点q中的第一个关键字移入双亲结点p中*/ 
    int j;
    BTNode *aq=p->ptr[i-1];
    BTNode *q=p->ptr[i];

    aq->keynum++;                                   //把双亲结点p中的关键字移动到左兄弟aq中
    aq->key[aq->keynum]=p->key[i]; 
    aq->ptr[aq->keynum]=p->ptr[i]->ptr[0];

    p->key[i]=q->key[1];                            //把右兄弟q中的关键字移动到双亲节点p中
    q->ptr[0]=q->ptr[1];
    q->keynum--;

    for(j=1;j<=aq->keynum;j++){                     //将右兄弟q中所有关键字向前移动一位
        aq->key[j]=aq->key[j+1];
        aq->ptr[j]=aq->ptr[j+1];
    }
}


void Combine(BTNode *p,int i){
/*将双亲结点p、右结点q合并入左结点aq，
并调整双亲结点p中的剩余关键字的位置*/ 
    int j;
    BTNode *q=p->ptr[i];                            
    BTNode *aq=p->ptr[i-1];

    aq->keynum++;                                  //将双亲结点的关键字p->key[i]插入到左结点aq     
    aq->key[aq->keynum]=p->key[i];
    aq->ptr[aq->keynum]=q->ptr[0];

    for(j=1;j<=q->keynum;j++){                      //将右结点q中的所有关键字插入到左结点aq 
        aq->keynum++;
        aq->key[aq->keynum]=q->key[j];
        aq->ptr[aq->keynum]=q->ptr[j];
    }

    for(j=i;j<p->keynum;j++){                       //将双亲结点p中的p->key[i]后的所有关键字向前移动一位 
        p->key[j]=p->key[j+1];
        p->ptr[j]=p->ptr[j+1];
    }
    p->keynum--;                                    //修改双亲结点p的keynum值 
    free(q);                                        //释放空右结点q的空间
}


void AdjustBTree(BTNode *p,int i){
//删除结点p中的第i个关键字后,调整B树
    if(i==0)                                        //删除的是最左边关键字
        if(p->ptr[1]->keynum>Min)                   //右结点可以借
            MoveLeft(p,1);
        else                                        //右兄弟不够借 
            Combine(p,1);
    else if(i==p->keynum)                           //删除的是最右边关键字
        if(p->ptr[i-1]->keynum>Min)                 //左结点可以借 
            MoveRight(p,i);
        else                                        //左结点不够借 
            Combine(p,i);
    else if(p->ptr[i-1]->keynum>Min)                //删除关键字在中部且左结点够借 
        MoveRight(p,i);
    else if(p->ptr[i+1]->keynum>Min)                //删除关键字在中部且右结点够借 
        MoveLeft(p,i+1);
    else                                            //删除关键字在中部且左右结点都不够借
        Combine(p,i);
}


int FindBTNode(BTNode *p,KeyType k,int &i){
//反映是否在结点p中是否查找到关键字k 
    if(k<p->key[1]){                                //结点p中查找关键字k失败 
        i=0;
        return 0;
    }
    else{                                           //在p结点中查找
        i=p->keynum;
        while(k<p->key[i]&&i>1)
            i--;
        if(k==p->key[i])                            //结点p中查找关键字k成功 
            return 1;
    }
}


int BTNodeDelete(BTNode *p,KeyType k){
//在结点p中查找并删除关键字k
    int i;
    int found_tag;                                  //查找标志 
    if(p==NULL)                                     
        return 0;
    else{
        found_tag=FindBTNode(p,k,i);                //返回查找结果 
        if(found_tag==1){                           //查找成功 
            if(p->ptr[i-1]!=NULL){                  //删除的是非叶子结点
                Substitution(p,i);                  //寻找相邻关键字(右子树中最小的关键字) 
                BTNodeDelete(p->ptr[i],p->key[i]);  //执行删除操作 
            }
            else
                Remove(p,i);                        //从结点p中位置i处删除关键字
        }
        else
            found_tag=BTNodeDelete(p->ptr[i],k);    //沿孩子结点递归查找并删除关键字k
        if(p->ptr[i]!=NULL)
            if(p->ptr[i]->keynum<Min)               //删除后关键字个数小于MIN
                AdjustBTree(p,i);                   //调整B树 
        return found_tag;
    }
}


void BTreeDelete(BTree &t,KeyType k){ 
    BTNode *p;
    int a=BTNodeDelete(t,k);                        
    if(a==0)                                       
        printf("   关键字%d不在B树中\n",k);
    else if(t->keynum==0){                       
        p=t;
        t=t->ptr[0];
        free(p);
    }
}


void DestroyBTree(BTree &t){
    int i;  
    BTNode* p=t;  
    if(p!=NULL){                                    //B树不为空  
        for(i=0;i<=p->keynum;i++){                  //递归释放每一个结点 
            DestroyBTree(*&p->ptr[i]);  
        }  
        free(p);  
    }  
    t=NULL;  
}  

int InitQueue(LinkList &L){
    L=(LNode*)malloc(sizeof(LNode));                //分配结点空间 
    if(L==NULL)                                     //分配失败              
        return 0;
     L->next=NULL;
     return 1;
}


LNode* CreateNode(BTNode *p){
    LNode *q;
    q=(LNode*)malloc(sizeof(LNode));                //分配结点空间
    if(q!=NULL){                                    //分配成功 
        q->data=p;
        q->next=NULL;
    }
   return q;
}


int Enqueue(LNode *p,BTNode *q){ 
    if(p==NULL)                                     
        return 0;                               
    while(p->next!=NULL)                            //调至队列最后 
        p=p->next;
    p->next=CreateNode(q);                          //生成结点让q进入队列 
    return 1;
}


int Dequeue(LNode *p,BTNode *&q){
    LNode *aq;
    if(p==NULL||p->next==NULL)                      //删除位置不合理 
        return 0; 
    aq=p->next;                                     //修改被删结点aq的指针域
    p->next=aq->next;                               
    q=aq->data;
    free(aq);                                       //释放结点aq
    return 1;
}


int IfEmpty(LinkList L){
    if(L==NULL)                                     //队列不存在 
        return 0;
    if(L->next==NULL)                               //队列为空 
        return 1;
    return 0;                                   //队列非空 
}

void DestroyQueue(LinkList L){
   LinkList p;
    if(L!=NULL){
        p=L;
        L=L->next;
        free(p);                                    //逐一释放 
        DestroyQueue(L);
    }
}

int Traverse(BTree t,LinkList L,int newline,int sum){
//用队列遍历输出B树 
    int i;
    BTree p;
    if(t!=NULL){
        printf("  [ ");
        Enqueue(L,t->ptr[0]);                       //入队         
        for(i=1;i<=t->keynum;i++){
            printf(" %d ",t->key[i]);
            Enqueue(L,t->ptr[i]);                   //子结点入队 
        }
        sum+=t->keynum+1;
        printf("]");
        if(newline==0){                             //需要另起一行 
            printf("\n");
            newline=sum-1;
            sum=0;
        }
        else
            newline--;
     }

     if(IfEmpty(L)==0){                         //l不为空 
         Dequeue(L,p);                              //出队，以p返回 
         Traverse(p,L,newline,sum);                 //遍历出队结点 
     }
     return 1;
 }


int PrintBTree(BTree t){
//输出B树 
   LinkList L;
    if(t==NULL){
        printf("  B树为空树");
        return 1;
    }
    InitQueue(L);                                   //初始化队列 
    Traverse(t,L,0,0);                              //利用队列输出 
    DestroyQueue(L);                                //销毁队列 
    return 1;
}


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

int main(){ 
    BTNode *t=NULL;
    NODE0 s;                                       
    int j,n=100;
    int k;
    int a[100] ;
	num_rand(a,100,1000);
	int i; 
	for(i=0;i<100;i++){
		printf("%d  ",a[i] );
	}   
	printf("\n\n");
    for(j=0;j<n;j++){                               //逐一插入元素 
        s=SearchBTree(t,a[j]);
        if(s.tag==0)
            InsertBTree(t,s.i,a[j],s.pt);
    }
    PrintBTree(t);
    printf("\n");
    printf("delete:\n");                          //删除操作 
    for(i=70;i<90;i++)                                                       
        BTreeDelete(t,a[i]);
    printf("  删除后的B树: \n");
    PrintBTree(t);
    printf("\n\n");
    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
    BTNode *t1=NULL;
    n=20;
    for(j=0;j<n;j++){                               //逐一插入元素 
        s=SearchBTree(t1,b[j]);
        if(s.tag==0)
        InsertBTree(t1,s.i,b[j],s.pt);
    }
    PrintBTree(t1);
    printf("\n");
	printf("delete:\n");                          //删除操作 
    for(i=10;i<15;i++)                                                       
        BTreeDelete(t1,b[i]);
    printf("  删除后的B树: \n");
    PrintBTree(t1);
    
    if(SearchBTree(t1,b[10]).tag!=0)
		printf("This key: already exist!\n");
		else
		printf("Search fail!\n");
	if(SearchBTree(t1,b[9]).tag!=0)
		printf("This key:%d already exist!\n",b[9]);
		else
		printf("Search fail!\n");
    printf("\n\n"); 
    
    int c[20000] ;
	num_rand(c,20000,100000); 
	n=1000;
	printf("\n\n");
    BTNode *t2=NULL;
    for(j=0;j<n;j++){                               //逐一插入元素 
        s=SearchBTree(t2,c[j]);
        if(s.tag==0)
            InsertBTree(t2,s.i,c[j],s.pt);
    }
    n=20000;
    clock_t begin = 0, end = 0;
    begin = clock();
	for(j=1000;j<n;j++){                               //逐一插入元素 
        s=SearchBTree(t2,c[j]);
        if(s.tag==0)
            InsertBTree(t2,s.i,c[j],s.pt);
    };
    end = clock();
    printf("\nInsert time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    begin = clock();
    for(i=1000;i<20000;i++)
        BTreeDelete(t2,c[i]);
    end = clock();
    printf("\nDelete time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    
    for(j=1000;j<n;j++){                               //逐一插入元素 
        s=SearchBTree(t2,c[j]);
        if(s.tag==0)
            InsertBTree(t2,s.i,c[j],s.pt);
    };
    
    begin = clock();
    for(i=1000;i<20000;i++)
    	SearchBTree(t2,c[j]);
    end = clock();
    printf("\nSearch time: %5.3f\n",(float)(end-begin)/CLOCKS_PER_SEC);
    return 0;
}



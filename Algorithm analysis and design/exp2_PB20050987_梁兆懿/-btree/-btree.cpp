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

    BTNode *p=t,*q=NULL;                            //��ʼ�����p�ͽ��q,pָ�������,qָ��p��˫��
    int found_tag=0;                                //�趨���ҳɹ�����־ 
    int i=0;                 
    NODE0 r;                                       //�趨���صĲ��ҽ�� 

    while(p!=NULL&&found_tag==0){
        i=SearchBTNode(p,k);                        //�ڽ��p�в��ҹؼ���k,ʹ��p->key[i]<=k<p->key[i+1]
        if(i>0&&p->key[i]==k)                       //�ҵ�����ؼ���
            found_tag=1;                            //���ҳɹ� 
        else{                                       //����ʧ�� 
            q=p;                            
            p=p->ptr[i];
        }
    }

    if(found_tag==1){                               //���ҳɹ�
        r.pt=p;
        r.i=i;
        r.tag=1;
    }
    else{                                           //����ʧ��
        r.pt=q;
        r.i=i;
        r.tag=0;
    }

    return r;                                       //���عؼ���k��λ��(�����λ��)
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
        NewRoot(t,k,NULL,NULL);                     //���ɽ����ؼ���k�ĸ����t
    else{
        x=k;
        q=NULL;
        finish_tag=0;       
        newroot_tag=0;
        while(finish_tag==0&&newroot_tag==0){
            InsertBTNode(p,i,x,q);                  //���ؼ���x�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]
            if (p->keynum<=Max) 
                finish_tag=1;                       //�������
            else{         
                s=(m+1)/2;
                SplitBTNode(p,q);                   //���ѽ�� 
                x=p->key[s];
                if(p->parent){                      //����x�Ĳ���λ��
                    p=p->parent;
                    i=SearchBTNode(p, x);
                }
                else                                //û�ҵ�x����Ҫ�½�� 
                    newroot_tag=1;
            }
        }
        if(newroot_tag==1)                          //������ѷ���Ϊ���p��q 
            NewRoot(t,x,p,q);                       //�����¸����t,p��qΪ����ָ��
    }
}


void Remove(BTNode *p,int i){
//��p���ɾ��key[i]�����ĺ���ָ��ptr[i]
    int j;
    for(j=i+1;j<=p->keynum;j++){                    //ǰ��ɾ��key[i]��ptr[i]
        p->key[j-1]=p->key[j];
        p->ptr[j-1]=p->ptr[j];
    }
    p->keynum--;
}


void Substitution(BTNode *p,int i){
//���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ��(��������ֵ��С�Ĺؼ���) 
    BTNode *q;
    for(q=p->ptr[i];q->ptr[0]!=NULL;q=q->ptr[0]);
    p->key[i]=q->key[1];                            //���ƹؼ���ֵ
}


void MoveRight(BTNode *p,int i){
/*��˫�׽��p�е����һ���ؼ��������ҽ��q��
������aq�е����һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *q=p->ptr[i];
    BTNode *aq=p->ptr[i-1];

    for(j=q->keynum;j>0;j--){                       //�����ֵ�q�����йؼ�������ƶ�һλ
        q->key[j+1]=q->key[j];
        q->ptr[j+1]=q->ptr[j];
    }

    q->ptr[1]=q->ptr[0];                            //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
    q->key[1]=p->key[i];
    q->keynum++;

    p->key[i]=aq->key[aq->keynum];                  //�����ֵ�aq�����һ���ؼ����ƶ���˫�׽��p��
    p->ptr[i]->ptr[0]=aq->ptr[aq->keynum];
    aq->keynum--;
}


void MoveLeft(BTNode *p,int i){
/*��˫�׽��p�еĵ�һ���ؼ�����������aq�У�
���ҽ��q�еĵ�һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *aq=p->ptr[i-1];
    BTNode *q=p->ptr[i];

    aq->keynum++;                                   //��˫�׽��p�еĹؼ����ƶ������ֵ�aq��
    aq->key[aq->keynum]=p->key[i]; 
    aq->ptr[aq->keynum]=p->ptr[i]->ptr[0];

    p->key[i]=q->key[1];                            //�����ֵ�q�еĹؼ����ƶ���˫�׽ڵ�p��
    q->ptr[0]=q->ptr[1];
    q->keynum--;

    for(j=1;j<=aq->keynum;j++){                     //�����ֵ�q�����йؼ�����ǰ�ƶ�һλ
        aq->key[j]=aq->key[j+1];
        aq->ptr[j]=aq->ptr[j+1];
    }
}


void Combine(BTNode *p,int i){
/*��˫�׽��p���ҽ��q�ϲ�������aq��
������˫�׽��p�е�ʣ��ؼ��ֵ�λ��*/ 
    int j;
    BTNode *q=p->ptr[i];                            
    BTNode *aq=p->ptr[i-1];

    aq->keynum++;                                  //��˫�׽��Ĺؼ���p->key[i]���뵽����aq     
    aq->key[aq->keynum]=p->key[i];
    aq->ptr[aq->keynum]=q->ptr[0];

    for(j=1;j<=q->keynum;j++){                      //���ҽ��q�е����йؼ��ֲ��뵽����aq 
        aq->keynum++;
        aq->key[aq->keynum]=q->key[j];
        aq->ptr[aq->keynum]=q->ptr[j];
    }

    for(j=i;j<p->keynum;j++){                       //��˫�׽��p�е�p->key[i]������йؼ�����ǰ�ƶ�һλ 
        p->key[j]=p->key[j+1];
        p->ptr[j]=p->ptr[j+1];
    }
    p->keynum--;                                    //�޸�˫�׽��p��keynumֵ 
    free(q);                                        //�ͷſ��ҽ��q�Ŀռ�
}


void AdjustBTree(BTNode *p,int i){
//ɾ�����p�еĵ�i���ؼ��ֺ�,����B��
    if(i==0)                                        //ɾ����������߹ؼ���
        if(p->ptr[1]->keynum>Min)                   //�ҽ����Խ�
            MoveLeft(p,1);
        else                                        //���ֵܲ����� 
            Combine(p,1);
    else if(i==p->keynum)                           //ɾ���������ұ߹ؼ���
        if(p->ptr[i-1]->keynum>Min)                 //������Խ� 
            MoveRight(p,i);
        else                                        //���㲻���� 
            Combine(p,i);
    else if(p->ptr[i-1]->keynum>Min)                //ɾ���ؼ������в������㹻�� 
        MoveRight(p,i);
    else if(p->ptr[i+1]->keynum>Min)                //ɾ���ؼ������в����ҽ�㹻�� 
        MoveLeft(p,i+1);
    else                                            //ɾ���ؼ������в������ҽ�㶼������
        Combine(p,i);
}


int FindBTNode(BTNode *p,KeyType k,int &i){
//��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
    if(k<p->key[1]){                                //���p�в��ҹؼ���kʧ�� 
        i=0;
        return 0;
    }
    else{                                           //��p����в���
        i=p->keynum;
        while(k<p->key[i]&&i>1)
            i--;
        if(k==p->key[i])                            //���p�в��ҹؼ���k�ɹ� 
            return 1;
    }
}


int BTNodeDelete(BTNode *p,KeyType k){
//�ڽ��p�в��Ҳ�ɾ���ؼ���k
    int i;
    int found_tag;                                  //���ұ�־ 
    if(p==NULL)                                     
        return 0;
    else{
        found_tag=FindBTNode(p,k,i);                //���ز��ҽ�� 
        if(found_tag==1){                           //���ҳɹ� 
            if(p->ptr[i-1]!=NULL){                  //ɾ�����Ƿ�Ҷ�ӽ��
                Substitution(p,i);                  //Ѱ�����ڹؼ���(����������С�Ĺؼ���) 
                BTNodeDelete(p->ptr[i],p->key[i]);  //ִ��ɾ������ 
            }
            else
                Remove(p,i);                        //�ӽ��p��λ��i��ɾ���ؼ���
        }
        else
            found_tag=BTNodeDelete(p->ptr[i],k);    //�غ��ӽ��ݹ���Ҳ�ɾ���ؼ���k
        if(p->ptr[i]!=NULL)
            if(p->ptr[i]->keynum<Min)               //ɾ����ؼ��ָ���С��MIN
                AdjustBTree(p,i);                   //����B�� 
        return found_tag;
    }
}


void BTreeDelete(BTree &t,KeyType k){ 
    BTNode *p;
    int a=BTNodeDelete(t,k);                        
    if(a==0)                                       
        printf("   �ؼ���%d����B����\n",k);
    else if(t->keynum==0){                       
        p=t;
        t=t->ptr[0];
        free(p);
    }
}


void DestroyBTree(BTree &t){
    int i;  
    BTNode* p=t;  
    if(p!=NULL){                                    //B����Ϊ��  
        for(i=0;i<=p->keynum;i++){                  //�ݹ��ͷ�ÿһ����� 
            DestroyBTree(*&p->ptr[i]);  
        }  
        free(p);  
    }  
    t=NULL;  
}  

int InitQueue(LinkList &L){
    L=(LNode*)malloc(sizeof(LNode));                //������ռ� 
    if(L==NULL)                                     //����ʧ��              
        return 0;
     L->next=NULL;
     return 1;
}


LNode* CreateNode(BTNode *p){
    LNode *q;
    q=(LNode*)malloc(sizeof(LNode));                //������ռ�
    if(q!=NULL){                                    //����ɹ� 
        q->data=p;
        q->next=NULL;
    }
   return q;
}


int Enqueue(LNode *p,BTNode *q){ 
    if(p==NULL)                                     
        return 0;                               
    while(p->next!=NULL)                            //����������� 
        p=p->next;
    p->next=CreateNode(q);                          //���ɽ����q������� 
    return 1;
}


int Dequeue(LNode *p,BTNode *&q){
    LNode *aq;
    if(p==NULL||p->next==NULL)                      //ɾ��λ�ò����� 
        return 0; 
    aq=p->next;                                     //�޸ı�ɾ���aq��ָ����
    p->next=aq->next;                               
    q=aq->data;
    free(aq);                                       //�ͷŽ��aq
    return 1;
}


int IfEmpty(LinkList L){
    if(L==NULL)                                     //���в����� 
        return 0;
    if(L->next==NULL)                               //����Ϊ�� 
        return 1;
    return 0;                                   //���зǿ� 
}

void DestroyQueue(LinkList L){
   LinkList p;
    if(L!=NULL){
        p=L;
        L=L->next;
        free(p);                                    //��һ�ͷ� 
        DestroyQueue(L);
    }
}

int Traverse(BTree t,LinkList L,int newline,int sum){
//�ö��б������B�� 
    int i;
    BTree p;
    if(t!=NULL){
        printf("  [ ");
        Enqueue(L,t->ptr[0]);                       //���         
        for(i=1;i<=t->keynum;i++){
            printf(" %d ",t->key[i]);
            Enqueue(L,t->ptr[i]);                   //�ӽ����� 
        }
        sum+=t->keynum+1;
        printf("]");
        if(newline==0){                             //��Ҫ����һ�� 
            printf("\n");
            newline=sum-1;
            sum=0;
        }
        else
            newline--;
     }

     if(IfEmpty(L)==0){                         //l��Ϊ�� 
         Dequeue(L,p);                              //���ӣ���p���� 
         Traverse(p,L,newline,sum);                 //�������ӽ�� 
     }
     return 1;
 }


int PrintBTree(BTree t){
//���B�� 
   LinkList L;
    if(t==NULL){
        printf("  B��Ϊ����");
        return 1;
    }
    InitQueue(L);                                   //��ʼ������ 
    Traverse(t,L,0,0);                              //���ö������ 
    DestroyQueue(L);                                //���ٶ��� 
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
    for(j=0;j<n;j++){                               //��һ����Ԫ�� 
        s=SearchBTree(t,a[j]);
        if(s.tag==0)
            InsertBTree(t,s.i,a[j],s.pt);
    }
    PrintBTree(t);
    printf("\n");
    printf("delete:\n");                          //ɾ������ 
    for(i=70;i<90;i++)                                                       
        BTreeDelete(t,a[i]);
    printf("  ɾ�����B��: \n");
    PrintBTree(t);
    printf("\n\n");
    int b[20] ;
	num_rand(b,20,100);
	printf("\nrand list:\n");
	for(i=0;i<20;i++)
		printf("  %d  ",b[i] );
    BTNode *t1=NULL;
    n=20;
    for(j=0;j<n;j++){                               //��һ����Ԫ�� 
        s=SearchBTree(t1,b[j]);
        if(s.tag==0)
        InsertBTree(t1,s.i,b[j],s.pt);
    }
    PrintBTree(t1);
    printf("\n");
	printf("delete:\n");                          //ɾ������ 
    for(i=10;i<15;i++)                                                       
        BTreeDelete(t1,b[i]);
    printf("  ɾ�����B��: \n");
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
    for(j=0;j<n;j++){                               //��һ����Ԫ�� 
        s=SearchBTree(t2,c[j]);
        if(s.tag==0)
            InsertBTree(t2,s.i,c[j],s.pt);
    }
    n=20000;
    clock_t begin = 0, end = 0;
    begin = clock();
	for(j=1000;j<n;j++){                               //��һ����Ԫ�� 
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
    
    for(j=1000;j<n;j++){                               //��һ����Ԫ�� 
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



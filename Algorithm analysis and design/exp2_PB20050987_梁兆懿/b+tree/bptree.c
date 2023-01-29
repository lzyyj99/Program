#include "bptree.h"

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
/* ���ɽڵ㲢��ʼ�� */
BPTree NewNodeBPTree(){
    BPTree NewNode;
    int i;
    NewNode = malloc(sizeof(struct BPNode));
    if (NewNode == NULL)
           return NULL;

    i = 0;
    while (i < M + 1){
        NewNode->Key[i] = INT_MIN;
        NewNode->Children[i] = NULL;
        i++;
    }
    NewNode->Next = NULL;
    NewNode->KeyNum = 0;
    
    return NewNode;
}
 
/* ��ʼ�� */
BPTree InitBPTree(){
    
    BPTree T;    
    if (M < (3)){
        printf("M��С����3��");
         return NULL;
    }
    T = NewNodeBPTree();
    
    return T;
}
 
BPTree FindLBPTree(BPTree P){
    BPTree Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[0] != NULL) {
        Tmp = Tmp->Children[0];
    }
    return Tmp;
}
 
BPTree FindRBPTree(BPTree P){
    BPTree Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[Tmp->KeyNum - 1] != NULL) {
        Tmp = Tmp->Children[Tmp->KeyNum - 1];
    }
    return Tmp;
}
 
/* Ѱ��һ���ֵܽڵ㣬��洢�Ĺؼ���δ�������򷵻�NULL */
BPTree FindSBPTree(BPTree Parent,int i){
    BPTree Sibling;
    int Limit;
    
    Limit = M;
    
    Sibling = NULL;
    if (i == 0){
        if (Parent->Children[1]->KeyNum < Limit)
            Sibling = Parent->Children[1];
    }
    else if (Parent->Children[i - 1]->KeyNum < Limit)
        Sibling = Parent->Children[i - 1];
    else if (i + 1 < Parent->KeyNum && Parent->Children[i + 1]->KeyNum < Limit){
        Sibling = Parent->Children[i + 1];
    }
    
    return Sibling;
}
 
/* �����ֵܽڵ㣬��ؼ���������M/2 ;û�з���NULL*/
BPTree FindSNum_M_2BPTree(BPTree Parent,int i,int *j){
    int Limit;
    BPTree Sibling;
    Sibling = NULL;
    
    Limit = (M % 2 ? (M + 1)/2 : M/2);
    
    if (i == 0){
        if (Parent->Children[1]->KeyNum > Limit){
            Sibling = Parent->Children[1];
            *j = 1;
        }
    }
    else{
        if (Parent->Children[i - 1]->KeyNum > Limit){
            Sibling = Parent->Children[i - 1];
            *j = i - 1;
        }
        else if (i + 1 < Parent->KeyNum && Parent->Children[i + 1]->KeyNum > Limit){
            Sibling = Parent->Children[i + 1];
            *j = i + 1;
        }
        
    }
    
    return Sibling;
}
 
/* ��Ҫ��X����Key��ʱ��i��X��Parent��λ�ã�j��KeyҪ�����λ��
   ��Ҫ��Parent����X�ڵ��ʱ��i��Ҫ�����λ�ã�Key��j��ֵû����
 */
BPTree InsertEBPTree(int isKey, BPTree Parent,BPTree X,int Key,int i,int j){
    
    int k;
    if (isKey){
        /* ����key */
        k = X->KeyNum - 1;
        while (k >= j){
            X->Key[k + 1] = X->Key[k];k--;
        }
        
        X->Key[j] = Key;
        
        if (Parent != NULL)
            Parent->Key[i] = X->Key[0];
        
        X->KeyNum++;
        
    }else{
        /* ����ڵ� */
        
        /* ����Ҷ�ڵ�������� */
        if (X->Children[0] == NULL){
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }
        
        k = Parent->KeyNum - 1;
        while (k >= i){
            Parent->Children[k + 1] = Parent->Children[k];
            Parent->Key[k + 1] = Parent->Key[k];
            k--;
        }
        Parent->Key[i] = X->Key[0];
        Parent->Children[i] = X;
        
        Parent->KeyNum++;
        
    }
    return X;
}
 
 
BPTree RemoveEBPTree(int Key0, BPTree Parent,BPTree X,int i,int j){
    int k,Limit;
    
    if (Key0){
        Limit = X->KeyNum;
        /* ɾ��key */
        k = j + 1;
        while (k < Limit){
            X->Key[k - 1] = X->Key[k];k++;
        }
        
        X->Key[X->KeyNum - 1] = INT_MIN;
        
        Parent->Key[i] = X->Key[0];
        
        X->KeyNum--;
    }else{
        /* ɾ���ڵ� */
        
        /* �޸���Ҷ�ڵ������ */
        if (X->Children[0] == NULL && i > 0){
            Parent->Children[i - 1]->Next = Parent->Children[i + 1];
        }
        Limit = Parent->KeyNum;
        k = i + 1;
        while (k < Limit){
            Parent->Children[k - 1] = Parent->Children[k];
            Parent->Key[k - 1] = Parent->Key[k];
            k++;
        }
        
        Parent->Children[Parent->KeyNum - 1] = NULL;
        Parent->Key[Parent->KeyNum - 1] = INT_MIN;
        
        Parent->KeyNum--;
        
    }
    return X;
}
 
/* Src��Dst���������ڵĽڵ㣬i��Src��Parent�е�λ�ã�
 ��Src��Ԫ���ƶ���Dst�� ,n���ƶ�Ԫ�صĸ���*/
BPTree MoveEBPTree(BPTree Src,BPTree Dst,BPTree Parent,int i,int n){
    int TmpKey;
    BPTree Child;
    int j,SrcInFront;
    
    SrcInFront = 0;
    
    if (Src->Key[0] < Dst->Key[0])
        SrcInFront = 1;
    
    j = 0;
    /* �ڵ�Src��Dstǰ�� */
    if (SrcInFront){
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[Src->KeyNum - 1];
                RemoveEBPTree(0, Src, Child, Src->KeyNum - 1, INT_MIN);
                InsertEBPTree(0, Dst, Child, INT_MIN, 0, INT_MIN);
                j++;
            }
        }else{
            while (j < n) {
                TmpKey = Src->Key[Src->KeyNum -1];
                RemoveEBPTree(1, Parent, Src, i, Src->KeyNum - 1);
                InsertEBPTree(1, Parent, Dst, TmpKey, i + 1, 0);
                j++;
            }
            
        }
        
        Parent->Key[i + 1] = Dst->Key[0];
        /* ����Ҷ�ڵ��������� */
        if (Src->KeyNum > 0)
            FindRBPTree(Src)->Next = FindLBPTree(Dst);
        
    }else{
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[0];
                RemoveEBPTree(0, Src, Child, 0, INT_MIN);
                InsertEBPTree(0, Dst, Child, INT_MIN, Dst->KeyNum, INT_MIN);
                j++;
            }
            
        }else{
            while (j < n) {
                TmpKey = Src->Key[0];
                RemoveEBPTree(1, Parent, Src, i, 0);
                InsertEBPTree(1, Parent, Dst, TmpKey, i - 1, Dst->KeyNum);
                j++;
            }
            
        }
        
        Parent->Key[i] = Src->Key[0];
        if (Src->KeyNum > 0)
            FindRBPTree(Dst)->Next = FindLBPTree(Src);   
    }
    return Parent;
}
 
BPTree SplitBPTree(BPTree Parent,BPTree X,int i){
    int j,k,Limit;
    BPTree NewNode;
    
    NewNode = NewNodeBPTree();
    
    k = 0;
    j = X->KeyNum / 2;
    Limit = X->KeyNum;
    while (j < Limit){
        if (X->Children[0] != NULL){
            NewNode->Children[k] = X->Children[j];
            X->Children[j] = NULL;
        }
        NewNode->Key[k] = X->Key[j];
        X->Key[j] = INT_MIN;
        NewNode->KeyNum++;X->KeyNum--;
        j++;k++;
    }
    
    if (Parent != NULL)
        InsertEBPTree(0, Parent, NewNode, INT_MIN, i + 1, INT_MIN);
    else{
        /* �����X�Ǹ�����ô�����µĸ������� */
        Parent = NewNodeBPTree();
        InsertEBPTree(0, Parent, X, INT_MIN, 0, INT_MIN);
        InsertEBPTree(0, Parent, NewNode, INT_MIN, 1, INT_MIN);
        
        return Parent;
    }
    
    return X;
}
 
/* �ϲ��ڵ�,X����M/2�ؼ��֣�S�д��ڻ����M/2���ؼ���*/
BPTree MergeNodeBPTree(BPTree Parent, BPTree X,BPTree S,int i){
    int Limit;
    
    /* S�Ĺؼ�����Ŀ����M/2 */
    if (S->KeyNum > (M % 2 ? (M + 1)/2 : M/2)){
        /* ��S���ƶ�һ��Ԫ�ص�X�� */
        MoveEBPTree(S, X, Parent, i,1);
    }else{
        /* ��Xȫ��Ԫ���ƶ���S�У�����Xɾ�� */
        Limit = X->KeyNum;
        MoveEBPTree(X,S, Parent, i,Limit);
        RemoveEBPTree(0, Parent, X, i, INT_MIN);
        
        free(X);
        X = NULL;
    }
    
    return Parent;
}
 
BPTree InsertBPTree0(BPTree T,int Key,int i,BPTree Parent){
    int j,Limit;
    BPTree Sibling;
    
    /* ���ҷ�֧ */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        /* �ظ�ֵ������ */
        if (Key == T->Key[j])
            return T;
        j++;
    }
    if (j != 0 && T->Children[0] != NULL) j--;
    
    /* ��Ҷ */
    if (T->Children[0] == NULL)
        T = InsertEBPTree(1, Parent, T, Key, i, j);
    /* �ڲ��ڵ� */
    else
        T->Children[j] = InsertBPTree0(T->Children[j], Key, j, T);
    Limit = M;
    
    if (T->KeyNum > Limit){
        if (Parent == NULL){
            T = SplitBPTree(Parent, T, i);
        }
        else{
            Sibling = FindSBPTree(Parent, i);
            if (Sibling != NULL){
                MoveEBPTree(T, Sibling, Parent, i, 1);
            }else{
                T = SplitBPTree(Parent, T, i);
            }
        }
        
    }
    
    if (Parent != NULL)
        Parent->Key[i] = T->Key[0];
    
    
    return T;
}
 
/* ���� */
BPTree InsertBPTree(BPTree T,int Key){
    return InsertBPTree0(T, Key, 0, NULL);
}
 
BPTree RecursiveRemoveBPTree(BPTree T,int Key,int i,BPTree Parent){
    
    int j,NeedAdjust;
    BPTree Sibling,Tmp;
    
    Sibling = NULL;
    
    /* ���ҷ�֧ */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        if (Key == T->Key[j])
            break;
        j++;
    }
    
    if (T->Children[0] == NULL){
        /* û�ҵ� */
        if (Key != T->Key[j] || j == T->KeyNum)
            return T;
    }else
        if (j == T->KeyNum || Key < T->Key[j]) j--;
    
    
    
    /* ��Ҷ */
    if (T->Children[0] == NULL){
        T = RemoveEBPTree(1, Parent, T, i, j);
    }else{
        T->Children[j] = RecursiveRemoveBPTree(T->Children[j], Key, j, T);
    }
    
    NeedAdjust = 0;
    /* ���ĸ�������һƬ��Ҷ���������������2��M֮�� */
    if (Parent == NULL && T->Children[0] != NULL && T->KeyNum < 2)
        NeedAdjust = 1;
    /* �����⣬���з���Ҷ�ڵ�Ķ�������[M/2]��M֮�䡣(����[]��ʾ����ȡ��) */
    else if (Parent != NULL && T->Children[0] != NULL && T->KeyNum < (M % 2 ? (M + 1)/2 : M/2))
        NeedAdjust = 1;
    /* ���Ǹ�����Ҷ�йؼ��ֵĸ���Ҳ��[M/2]��M֮�� */
    else if (Parent != NULL && T->Children[0] == NULL && T->KeyNum < (M % 2 ? (M + 1)/2 : M/2))
        NeedAdjust = 1;
    
    /* �����ڵ� */
    if (NeedAdjust){
        /* �� */
        if (Parent == NULL){
            if(T->Children[0] != NULL && T->KeyNum < 2){
                Tmp = T;
                T = T->Children[0];
                free(Tmp);
                return T;
            }
            
        }else{
            /* �����ֵܽڵ㣬��ؼ�����Ŀ����M/2 */
            Sibling = FindSNum_M_2BPTree(Parent, i,&j);
            if (Sibling != NULL){
                MoveEBPTree(Sibling, T, Parent, j, 1);
            }else{
                if (i == 0)
                    Sibling = Parent->Children[1];
                else
                    Sibling = Parent->Children[i - 1];
                
                Parent = MergeNodeBPTree(Parent, T, Sibling, i);
                T = Parent->Children[i];
            }
        }      
    }
    return T;
}
 
/* ɾ�� */
BPTree RemoveBPTree(BPTree T,int Key){
    return RecursiveRemoveBPTree(T, Key, 0, NULL);
}
 
/* ���� */
BPTree DeleteBPTree(BPTree T){
    int i,j;
    if (T != NULL){
        i = 0;
        while (i < T->KeyNum + 1){
            DeleteBPTree(T->Children[i]);i++;
        }
        j = 0;
        free(T);
        T = NULL;
    }
    
    return T;
}
 
void TravelBPTree0(BPTree T,int Level){
    int i;
    if (T != NULL){
        printf("  ");
        printf(" L%d :",Level);
        printf("[ ");
        i = 0;
        while (i < T->KeyNum)/*  T->Key[i] != INT_MIN*/
            printf("%d ",T->Key[i++]);
        printf("]");
        printf("\n");
        Level++;
        i = 0;
        while (i <= T->KeyNum) {
            TravelBPTree0(T->Children[i], Level);
            i++;
        }
        
        
    }
}
 
/* ���� */
void TravelBPTree(BPTree T){
    TravelBPTree0(T, 0);
    printf("\n");
}
 
/* ������Ҷ�ڵ������ */
void TravelData(BPTree T){
    BPTree Tmp;
    int i;
    if (T == NULL)
        return ;
    printf("All Data:");
    Tmp = T;
    while (Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    /* ��һƬ��Ҷ */
    while (Tmp != NULL){
        i = 0;
        while (i < Tmp->KeyNum)
            printf(" %d",Tmp->Key[i++]);
        Tmp = Tmp->Next;
    }
}

int SearchBPTree(BPTree T,int key){
    int i;
    if (T != NULL){
        if (T->Children[0] == NULL)
            i = 0;
        else
            i = 1;

        while (i < T->KeyNum)
        if(key==T->Key[i++]){
            return 1;
			}

        i = 0;
        while (i <= T->KeyNum) {
            if(SearchBPTree(T->Children[i], key)==1)
			return 1;
            i++;
        }    
    }
}

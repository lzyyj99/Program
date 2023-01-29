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
/* 生成节点并初始化 */
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
 
/* 初始化 */
BPTree InitBPTree(){
    
    BPTree T;    
    if (M < (3)){
        printf("M最小等于3！");
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
 
/* 寻找一个兄弟节点，其存储的关键字未满，否则返回NULL */
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
 
/* 查找兄弟节点，其关键字数大于M/2 ;没有返回NULL*/
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
 
/* 当要对X插入Key的时候，i是X在Parent的位置，j是Key要插入的位置
   当要对Parent插入X节点的时候，i是要插入的位置，Key和j的值没有用
 */
BPTree InsertEBPTree(int isKey, BPTree Parent,BPTree X,int Key,int i,int j){
    
    int k;
    if (isKey){
        /* 插入key */
        k = X->KeyNum - 1;
        while (k >= j){
            X->Key[k + 1] = X->Key[k];k--;
        }
        
        X->Key[j] = Key;
        
        if (Parent != NULL)
            Parent->Key[i] = X->Key[0];
        
        X->KeyNum++;
        
    }else{
        /* 插入节点 */
        
        /* 对树叶节点进行连接 */
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
        /* 删除key */
        k = j + 1;
        while (k < Limit){
            X->Key[k - 1] = X->Key[k];k++;
        }
        
        X->Key[X->KeyNum - 1] = INT_MIN;
        
        Parent->Key[i] = X->Key[0];
        
        X->KeyNum--;
    }else{
        /* 删除节点 */
        
        /* 修改树叶节点的链接 */
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
 
/* Src和Dst是两个相邻的节点，i是Src在Parent中的位置；
 将Src的元素移动到Dst中 ,n是移动元素的个数*/
BPTree MoveEBPTree(BPTree Src,BPTree Dst,BPTree Parent,int i,int n){
    int TmpKey;
    BPTree Child;
    int j,SrcInFront;
    
    SrcInFront = 0;
    
    if (Src->Key[0] < Dst->Key[0])
        SrcInFront = 1;
    
    j = 0;
    /* 节点Src在Dst前面 */
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
        /* 将树叶节点重新连接 */
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
        /* 如果是X是根，那么创建新的根并返回 */
        Parent = NewNodeBPTree();
        InsertEBPTree(0, Parent, X, INT_MIN, 0, INT_MIN);
        InsertEBPTree(0, Parent, NewNode, INT_MIN, 1, INT_MIN);
        
        return Parent;
    }
    
    return X;
}
 
/* 合并节点,X少于M/2关键字，S有大于或等于M/2个关键字*/
BPTree MergeNodeBPTree(BPTree Parent, BPTree X,BPTree S,int i){
    int Limit;
    
    /* S的关键字数目大于M/2 */
    if (S->KeyNum > (M % 2 ? (M + 1)/2 : M/2)){
        /* 从S中移动一个元素到X中 */
        MoveEBPTree(S, X, Parent, i,1);
    }else{
        /* 将X全部元素移动到S中，并把X删除 */
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
    
    /* 查找分支 */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        /* 重复值不插入 */
        if (Key == T->Key[j])
            return T;
        j++;
    }
    if (j != 0 && T->Children[0] != NULL) j--;
    
    /* 树叶 */
    if (T->Children[0] == NULL)
        T = InsertEBPTree(1, Parent, T, Key, i, j);
    /* 内部节点 */
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
 
/* 插入 */
BPTree InsertBPTree(BPTree T,int Key){
    return InsertBPTree0(T, Key, 0, NULL);
}
 
BPTree RecursiveRemoveBPTree(BPTree T,int Key,int i,BPTree Parent){
    
    int j,NeedAdjust;
    BPTree Sibling,Tmp;
    
    Sibling = NULL;
    
    /* 查找分支 */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        if (Key == T->Key[j])
            break;
        j++;
    }
    
    if (T->Children[0] == NULL){
        /* 没找到 */
        if (Key != T->Key[j] || j == T->KeyNum)
            return T;
    }else
        if (j == T->KeyNum || Key < T->Key[j]) j--;
    
    
    
    /* 树叶 */
    if (T->Children[0] == NULL){
        T = RemoveEBPTree(1, Parent, T, i, j);
    }else{
        T->Children[j] = RecursiveRemoveBPTree(T->Children[j], Key, j, T);
    }
    
    NeedAdjust = 0;
    /* 树的根或者是一片树叶，或者其儿子数在2到M之间 */
    if (Parent == NULL && T->Children[0] != NULL && T->KeyNum < 2)
        NeedAdjust = 1;
    /* 除根外，所有非树叶节点的儿子数在[M/2]到M之间。(符号[]表示向上取整) */
    else if (Parent != NULL && T->Children[0] != NULL && T->KeyNum < (M % 2 ? (M + 1)/2 : M/2))
        NeedAdjust = 1;
    /* （非根）树叶中关键字的个数也在[M/2]和M之间 */
    else if (Parent != NULL && T->Children[0] == NULL && T->KeyNum < (M % 2 ? (M + 1)/2 : M/2))
        NeedAdjust = 1;
    
    /* 调整节点 */
    if (NeedAdjust){
        /* 根 */
        if (Parent == NULL){
            if(T->Children[0] != NULL && T->KeyNum < 2){
                Tmp = T;
                T = T->Children[0];
                free(Tmp);
                return T;
            }
            
        }else{
            /* 查找兄弟节点，其关键字数目大于M/2 */
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
 
/* 删除 */
BPTree RemoveBPTree(BPTree T,int Key){
    return RecursiveRemoveBPTree(T, Key, 0, NULL);
}
 
/* 销毁 */
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
 
/* 遍历 */
void TravelBPTree(BPTree T){
    TravelBPTree0(T, 0);
    printf("\n");
}
 
/* 遍历树叶节点的数据 */
void TravelData(BPTree T){
    BPTree Tmp;
    int i;
    if (T == NULL)
        return ;
    printf("All Data:");
    Tmp = T;
    while (Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    /* 第一片树叶 */
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

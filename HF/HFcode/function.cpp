#include"HFcode.h"

//选择最小权值
void Select(HUFF* HT, int n, int& n1, int& n2)//返回未处理的两个权值最小的元素
{
	int i = 1;
	while (HT[i].parent != 0)
		i++;
	n1 = i;
	i++;
	while (HT[i].parent != 0)
		i++;
	n2 = i;
	/*设定n1<n2*/
	if (HT[n2].weight < HT[n1].weight)
	{
		int tem;
		tem = HT[n2].weight;
		HT[n2].weight = HT[n1].weight;
		HT[n1].weight = tem;
	}//end if
	int j = 0;
	i++;
	while (i <= n && HT[i].weight != 0)
	{
		if (HT[i].parent == 0)
		{
			if (HT[i].weight < HT[n1].weight)
			{
				n2 = n1;
				n1 = i;
			}
			else if (HT[i].weight < HT[n2].weight)
			{
				n2 = i;
			}
		}//end if
		i++;
	}//end while

}

//创建霍夫曼树
void CreatHUff(HUFF*& HT, int* W, int n)/*HT为存放HUFFTREE的节点，W是权值的数组，n为总共出现的字母类型*/
{
	int m = 2 * n - 1,n1, n2;;/*计算HUFFtree的节点数目*/
	HT = new HUFF[m + 1];
	for (int i = 1; i <= m; i++)
	{
		HT[i].weight = i <= n ? W[i] : 0;
		HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
	}//end for
	
	for (int i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, n1, n2);
		HT[i].lchild = n1;
		HT[i].rchild = n2;
		HT[i].weight = HT[n1].weight + HT[n2].weight;
		HT[n1].parent = HT[n2].parent = i;
	}//end for
}

//初始化栈，以下三个函数为栈操作
void Init(S& stack)
{

	stack.elem = new char[400];
	stack.stacksize = 400;
	stack.top = -1;
}

//入栈
void PUSH(S& stack, char a)
{
	stack.elem[++stack.top] = a;
}

//出栈
bool POP(S& stack, char& a)
{
	if (stack.top == -1) return 1;/*定义非零为假，0为真*/
	a = stack.elem[stack.top--];
	return 0;

}

//单个编码,编码函数，找到字母对应的二进制流
void CODING(HUFF* HT, int root, char**& HC, S& stack)
{
	if (root != 0)
	{
		if (HT[root].lchild == 0)
		{
			PUSH(stack, '\0');
			HC[root] = new char[200];
			strcpy_s(HC[root],100, stack.elem);
			char b;
			POP(stack, b);
		}
		char b;
		PUSH(stack, '0');
		CODING(HT, HT[root].lchild, HC, stack);
		POP(stack, b);
		PUSH(stack, '1');
		CODING(HT, HT[root].rchild, HC, stack);
		POP(stack, b);

	}
}

//编码
void HUFFCOD(HUFF* HT, char**& HC, int n)//将字母对应的二进制流存入HC数组，P209
{
	S stack;
	Init(stack);
	HC = new char*[n + 1];
	CODING(HT, 2 * n - 1, HC, stack);

}

//初始化扫描栈
void InitS(SCAN& stack)
{
	stack.R = new ELEM[200];
	/*for (int i = 0; i <= 50; i++)
	{
		stack.R[i].L = '0';
		stack.R[i].num = 0;
	}*/
	stack.top = 0;
}

//扫描入栈
void PUSHS(SCAN& stack, char a)
{
	stack.R[++stack.top].L = a;
	stack.R[stack.top].num = 1;
}

//判断扫描的字符有无在栈中，若无则创建进入栈中
void judge(SCAN& stack, char a)
{
	int i = 1;
	int st = 0;             /*0表示没找到，1表示找到了*/
	while ((stack.top + 1) > i)
	{
		if (a == stack.R[i].L)
		{
			stack.R[i].num++;
			st = 1;
		}
		i++;
	}
	if (st == 0)
	{
		PUSHS(stack, a);
	}
}


//判断字符在储存的位置
int RANK(char* a, char b, int top)
{
	int i = 1;
	while (i <= top)
	{
		if (b == a[i]) return i;
		i++;
	}
	return -1;
}
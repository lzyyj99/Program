#include"HFcode.h"

//ѡ����СȨֵ
void Select(HUFF* HT, int n, int& n1, int& n2)//����δ���������Ȩֵ��С��Ԫ��
{
	int i = 1;
	while (HT[i].parent != 0)
		i++;
	n1 = i;
	i++;
	while (HT[i].parent != 0)
		i++;
	n2 = i;
	/*�趨n1<n2*/
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

//������������
void CreatHUff(HUFF*& HT, int* W, int n)/*HTΪ���HUFFTREE�Ľڵ㣬W��Ȩֵ�����飬nΪ�ܹ����ֵ���ĸ����*/
{
	int m = 2 * n - 1,n1, n2;;/*����HUFFtree�Ľڵ���Ŀ*/
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

//��ʼ��ջ��������������Ϊջ����
void Init(S& stack)
{

	stack.elem = new char[400];
	stack.stacksize = 400;
	stack.top = -1;
}

//��ջ
void PUSH(S& stack, char a)
{
	stack.elem[++stack.top] = a;
}

//��ջ
bool POP(S& stack, char& a)
{
	if (stack.top == -1) return 1;/*�������Ϊ�٣�0Ϊ��*/
	a = stack.elem[stack.top--];
	return 0;

}

//��������,���뺯�����ҵ���ĸ��Ӧ�Ķ�������
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

//����
void HUFFCOD(HUFF* HT, char**& HC, int n)//����ĸ��Ӧ�Ķ�����������HC���飬P209
{
	S stack;
	Init(stack);
	HC = new char*[n + 1];
	CODING(HT, 2 * n - 1, HC, stack);

}

//��ʼ��ɨ��ջ
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

//ɨ����ջ
void PUSHS(SCAN& stack, char a)
{
	stack.R[++stack.top].L = a;
	stack.R[stack.top].num = 1;
}

//�ж�ɨ����ַ�������ջ�У������򴴽�����ջ��
void judge(SCAN& stack, char a)
{
	int i = 1;
	int st = 0;             /*0��ʾû�ҵ���1��ʾ�ҵ���*/
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


//�ж��ַ��ڴ����λ��
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
#pragma once
#include<cstdio>
#include<iostream>


using namespace std;


typedef struct
{
	int weight;
	int parent, lchild, rchild;
}HUFF,*HUFFN;
typedef struct
{
	char* elem;
	int stacksize;
	int top;
} S;
typedef struct
{
	char L;
	int num;   //权重
}ELEM;
typedef struct
{
	ELEM* R;   //用以储存扫描进入的字符
	int top;
}SCAN;


//选择最小权值
void Select(HUFF* HT, int n, int& n1, int& n2);
//创建霍夫曼树
void CreatHUff(HUFF*& HT, int* W, int n);
//初始化栈
void Init(S& stack);
//入栈
void PUSH(S& stack, char a);
//出栈
bool POP(S& stack, char& a);
//单个编码
void CODING(HUFF* HT, int root, char**& HC, S& stack);
//编码
void HUFFCOD(HUFF* HT, char**& HC, int n);
//初始化扫描栈
void InitS(SCAN& stack);
//扫描入栈
void PUSHS(SCAN& stack, char a);
//判断扫描的字符有无在栈中，若无则创建进入栈中
void judge(SCAN& stack, char a);
//判断字符在储存的位置
int RANK(char* a, char b, int top);

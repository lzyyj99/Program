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
	int num;   //Ȩ��
}ELEM;
typedef struct
{
	ELEM* R;   //���Դ���ɨ�������ַ�
	int top;
}SCAN;


//ѡ����СȨֵ
void Select(HUFF* HT, int n, int& n1, int& n2);
//������������
void CreatHUff(HUFF*& HT, int* W, int n);
//��ʼ��ջ
void Init(S& stack);
//��ջ
void PUSH(S& stack, char a);
//��ջ
bool POP(S& stack, char& a);
//��������
void CODING(HUFF* HT, int root, char**& HC, S& stack);
//����
void HUFFCOD(HUFF* HT, char**& HC, int n);
//��ʼ��ɨ��ջ
void InitS(SCAN& stack);
//ɨ����ջ
void PUSHS(SCAN& stack, char a);
//�ж�ɨ����ַ�������ջ�У������򴴽�����ջ��
void judge(SCAN& stack, char a);
//�ж��ַ��ڴ����λ��
int RANK(char* a, char b, int top);

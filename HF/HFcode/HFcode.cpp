#include"HFcode.h"


int main()
{
	float rate;
	float num1 = 0;   //电文的总字数
	float num2 = 0;
	char L[300];   //字母信息
	int W[300];    //权重
	int j = 0;
	int n = 0;   //总共出现的字母类型
	SCAN ST;    //记录扫描的变量
	InitS(ST);
	FILE* f1,*f2,*f3,*f4;
	fopen_s(&f1,"Huffmandata\\ToBeTran.txt", "rt+");
	fopen_s(&f2,"Huffmandata\\Temp.txt", "wb+");
	fopen_s(&f3,"Huffmandata\\TextFile.txt", "wt+");
	fopen_s(&f4, "Huffmandata\\CodeFile.txt", "wb+");
	if (f1 == NULL || f2 == NULL || f3 == NULL||f4==NULL)
	{
		cout << "打开文件失败" << endl;
		return 0;
	}
	//录入信息并创建树,直接从待编码的文件中录入，无需输入
	char letter;
	HUFF* HT;
	char** HC = NULL;
	while ((letter = fgetc(f1)) != EOF)//扫描文件中所有字母，用栈储存录入结果，已录入的不再入栈，此处用到judge，PUSHS等函数
	{
		num1++;
		judge(ST, letter);
	}
	int i = 1;
	while (i <= ST.top)
	{
		L[i] = ST.R[i].L;
		W[i] = ST.R[i].num;
		i++;
		n++;
	}
	CreatHUff(HT, W, n);
	HUFFCOD(HT, HC, n);
	rewind(f1);
	//编码
	char temp[500];
	while ((letter = fgetc(f1)) != EOF)
	{
		int number = RANK(L, letter, ST.top);
		strcpy_s(temp,100, HC[number]);

		fputs(temp, f2);
	}
	rewind(f2);
	 //二进制转换
	int *result = new int;
	*result = 0;
	int u = 0;
	while ((letter = fgetc(f2)) != EOF)
	{
		u++;
		if (u == 31)
		{
			fwrite(result, sizeof(int), 1, f4);
			u = 1;
			*result = 0;
		}
		if (letter == '0') *result = *result * 2;
		if (letter == '1') *result = *result * 2 + 1;
	}
	fwrite(result, sizeof(int), 1, f4);
	rewind(f2);
	//解码
	S w;                      //用w储存扫描进入的huffman码，然后再用来解码
	Init(w);
	int k = 0;                //用K来暂时储存解码得到的字符位置
	while ((letter = fgetc(f2)) != EOF)
	{
		PUSH(w, letter);
		PUSH(w, '\0');
		for (int i = 1; i <= n; i++)
		{
			int min = strcmp(HC[i], w.elem);
			if (min == 0)
			{
				k = i;
				break;
			}
		}
		if (k != 0)
		{
			while (!POP(w, letter));
			fputc(L[k], f3);
			k = 0;
			 
		}
		else POP(w, letter);
	}
	cout << "编码、解码成功，请在huffmandata中查看结果" << endl;
	rewind(f2);
	while ((letter = fgetc(f2)) != EOF) {
		num2++;
	}
	num2 = num2 / 8;
	rate = num2 / num1;
	cout << "压缩比为：" << rate;
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

	return 0;
}

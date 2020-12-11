#include<iostream>
#include"SHA256.h"
#include<stdlib.h>
using namespace std;

typedef unsigned int		UInt32;
typedef unsigned __int64	UInt64;
typedef unsigned char		UChar;

#define Max 1000 //最大字符数

SHA256 sha256 = SHA256();//构造函数

Message_Digest M_D;//构造Message_Digest

UInt32 W[Max / 4];//整型
UInt32 M[16];//储存分组信息

//压缩
void compress() {
	M_D = sha256.Deal(M);//把M输入Deal函数中
	cout << "哈希值 ： ";
	for (int i = 0; i < 8; i++) {
		cout << hex << M_D.H[i] << " ";
	}
	cout << endl << endl;
}

//附加填充bit、长度
void Append(UChar Y[Max])
{
	UInt32 T1 = 0, T2 = 0, T3 = 0, T4 = 0;
	UChar temp[Max] = {0};
	UInt64 x = strlen((char*)Y);		//数据长度
	UInt32 d = abs(long int(55-x)) % 64;//填充长度
	UInt32 n = ((x + 8) / 64) + 1;		//分组数量
	UInt32 m = x % 64;					//最后组数据长度
	int l = 8;
	cout << "数据长度x ： " << (int)x << endl;
	cout << "填充长度d ： " << d << endl;
	cout << "分组数量n ： " << n << endl;
	cout << "最后长度m ： " << m << endl;
	//不填充，放输入字符串
	for (int i = 0; i < x; i++) {
		temp[i] = Y[i];
	}
	//填充一次1000 0000
	temp[x] = 0x80;
	//填充d次0000 0000
	for (int i = x + 1; i < x + d + 1; i++) {
		temp[i] = 0x00;
	}
	//填充长度的63-0位
	for (int i = 1; i <= l; i++) {
		temp[(n * 64) - i] = (UChar)(8 * x >> (i - 1) * 8);
	}
	//无符号字符转换为无符号整型
	for (int i = 0; i < Max / 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 0) {
				T1 = temp[4 * i + j];
			}
			if (j == 1) {
				T2 = temp[4 * i + j];
			}
			if (j == 2) {
				T3 = temp[4 * i + j];
			}
			if (j == 3) {
				T4 = temp[4 * i + j];
			}
		}
		W[i] = (T1 << 24) + (T2 << 16) + (T3 << 8) + T4;
	}
	cout << "16进制数据 ：";
	for (int i = 0; i < n * 16; i++) {
		cout << hex << " " << W[i];
	}
	cout << endl;
	//分组处理
	for (int i = 0; i < n; i++) {
		cout << "分组处理 ： " << "第" << i + 1 << "组" << endl;
		for (int j = 0; j < 16; j++) {
			M[j] = W[(i * 16) + j];
		}
		compress();//sha-256压缩
	}
}

int main() {
	UChar Y[Max];
	cout << "请输入你要加密的字符串（最大1000个） ： " << endl;
	cin >> Y;//输入字符串
	cout << "Hash of '" << Y << "'" << endl;
	Append(Y);//添加填充
	system("pause");
}
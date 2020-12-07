#include<iostream>
#include"SHA256.h"
#include<stdlib.h>
using namespace std;

typedef unsigned int		UInt32;
typedef unsigned __int64	UInt64;
typedef unsigned char		UChar;

#define Max 1000 //����ַ���

SHA256 sha256 = SHA256();//���캯��

Message_Digest M_D;//����Message_Digest

UInt32 W[Max / 4];//����
UInt32 M[16];//���������Ϣ

//ѹ��
void compress() {
	M_D = sha256.Deal(M);//��M����Deal������
	cout << "��ϣֵ �� ";
	for (int i = 0; i < 8; i++) {
		cout << hex << M_D.H[i] << " ";
	}
	cout << endl << endl;
}

//�������bit������
void Append(UChar Y[Max])
{
	UInt32 T1 = 0, T2 = 0, T3 = 0, T4 = 0;
	UChar temp[Max] = {0};
	UInt64 x = strlen((char*)Y);		//���ݳ���
	UInt32 d = abs(long int(55-x)) % 64;//��䳤��
	UInt32 n = ((x + 8) / 64) + 1;		//��������
	UInt32 m = x % 64;					//��������ݳ���
	int l = 8;
	cout << "���ݳ���x �� " << (int)x << endl;
	cout << "��䳤��d �� " << d << endl;
	cout << "��������n �� " << n << endl;
	cout << "��󳤶�m �� " << m << endl;
	//����䣬�������ַ���
	for (int i = 0; i < x; i++) {
		temp[i] = Y[i];
	}
	//���һ��1000 0000
	temp[x] = 0x80;
	//���d��0000 0000
	for (int i = x + 1; i < x + d + 1; i++) {
		temp[i] = 0x00;
	}
	//��䳤�ȵ�63-0λ
	for (int i = 1; i <= l; i++) {
		temp[(n * 64) - i] = (UChar)(8 * x >> (i - 1) * 8);
	}
	//�޷����ַ�ת��Ϊ�޷�������
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
	cout << "16�������� ��";
	for (int i = 0; i < n * 16; i++) {
		cout << hex << " " << W[i];
	}
	cout << endl;
	//���鴦��
	for (int i = 0; i < n; i++) {
		cout << "���鴦�� �� " << "��" << i + 1 << "��" << endl;
		for (int j = 0; j < 16; j++) {
			M[j] = W[(i * 16) + j];
		}
		compress();//sha-256ѹ��
	}
}

int main() {
	UChar Y[Max];
	cout << "��������Ҫ���ܵ��ַ��������1000���� �� " << endl;
	cin >> Y;//�����ַ���
	cout << "Hash of '" << Y << "'" << endl;
	Append(Y);//������
	system("pause");
}
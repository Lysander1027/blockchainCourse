#include <iostream>
#include <fstream>
#include <time.h>
#include"SHA256.h"
using namespace std;

void testPoW();    // ����PoW�㷨
void testSHA256(); // ����ASH256�㷨

int main() {
	cout << "����������1��2\n����1������SHA256���ܲ���\n����2������PoW�㷨����\n";
	int choice = 0;
	cin >> choice;
	getchar();
	switch (choice)
	{
	case 1:
		testSHA256();
		break;
	case 2:
		testPoW();
		break;
	default:
		break;
	}
	
	system("pause");
	return 0;
}

void testSHA256() {
	char string[Max];
	SHA256 sha256 = SHA256();
	//clock_t start, end;   // ��ʱ
	//double duration;
	
	cout << "������Ҫ���ܵ��ַ�����������" << MaxChar << "���ַ�����" << endl;
	cin.getline(string, Max);
	WORD* MD2 = NULL;

	while (1) {
		/*start = clock();
		for(int i =0;i<10000;i++) MD2 = sha256.encryption(string);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;*/

		MD2 = sha256.encryption(string);
		for (int i = 0; i < 8; i++) {
			cout << hex << MD2[i] << " ";
		}
		cout << endl;
		//cout << "\t" << duration << endl;
		cin.getline(string, Max);
	}
}

void testPoW() {
	char string[Max];
	cout << "������Ҫ���ܵ��ַ�����������" << Max << "���ַ�����" << endl;
	cin.getline(string, Max);

	SHA256 sha256 = SHA256();
	int l = strlen(string);

	for (int i = 0; i < 1000; i++) {
		// ���ɲ�ͬ���ַ���
		int t = i, n = 0, digit[100];
		do {
			digit[n] = t % 10 + 48;
			t /= 10;
			n++;
		} while (t != 0);

		for (int i = n - 1; i >= 0; i--) {
			string[l + i] = (Uchar)digit[n - 1 - i];
		}
		string[l + n] = '\0';

		ofstream outfile("output.txt", ios::app);
		outfile << string << "\t";
		outfile.close();
		WORD* MD = sha256.PoW(string);
	}
}
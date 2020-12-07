#ifndef _SHA_256_
#define _SHA_256_
#include <iostream>
using namespace std;
#define MaxChar  1000
#define Max MaxChar+64

typedef unsigned int WORD;
typedef unsigned __int64 UInt64;
typedef unsigned char Uchar;

// SHA256��
class SHA256{
	private:
		WORD NGroup;                  // �ɷֳɵ�512bit�Ŀ���
		Uchar tempString[Max];        // �����м��ܵ��ַ���
		WORD originalMessage[Max/4];  // ���ַ�����ת������������
		WORD messageDigest[8];        // ��ϢժҪ
		int difficulty = 4;           // �Ѷ�ϵ��������ϢժҪǰ��������ٸ���
		int nonce = 0;
	public:
		SHA256() { initValue(); }
		~SHA256() {};
		WORD* encryption(char* string, bool isPoW = false);  // ����SHA256����
		WORD* PoW(char* string);                 // ���й�����֤���㷨
		WORD* PoW(char* string, int diffuculty); // ���й�����֤���㷨�������Ѷ�ϵ��
	private:
		void padding(Uchar* Y);              // ����������
		WORD* dealMessageDigest(WORD W[16]); // ����512bit���ݣ�������ϢժҪ
		void initValue();                    // ����ϢժҪ��Ϊ��ʼֵ 
		void copyString(char* string);       // �������char* �ַ���������ΪUchar*
		void addNonce(int length);           // ��ԭʼ�ַ��������nonce
		void setDifficulty(int n);           // ���ù������Ѷ�
		bool validationPoW(WORD* MD);        // ��֤�Ƿ�ﵽ������Ŀ��

		// ���㺯��
		WORD ROTR(WORD W, int n); // ����ת
		WORD SHR(WORD W, int n);  // ����λ
		// �����߼�����
		WORD Conditional(WORD x, WORD y, WORD z);
		WORD Majority(WORD x, WORD y, WORD z);
		WORD CSigma_0(WORD x);
		WORD CSigma_1(WORD x);
		WORD LSigma_0(WORD x);
		WORD LSigma_1(WORD x);
};

#endif
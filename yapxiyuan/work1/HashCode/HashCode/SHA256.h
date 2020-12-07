#ifndef _SHA256_H
#define _SHA256_H
#include<iostream>
using namespace std;
typedef unsigned int UInt32;//32�ֽ�

//�߼�����
#define Ch(x,y,z) ((x&y)^((~x)&z))
#define Ma(x,y,z) ((x&y)^(x&z)^(y&z))
#define LSigma_0(x) (ROTL(x,30)^ROTL(x,19)^ROTL(x,10))
#define LSigma_1(x) (ROTL(x,26)^ROTL(x,21)^ROTL(x,7))
#define SSigma_0(x) (ROTL(x,25)^ROTL(x,14)^SHR(x,3))
#define SSigma_1(x) (ROTL(x,15)^ROTL(x,13)^SHR(x,10))

//��Ϣ�ṹ
struct Message_Digest {
	UInt32 H[8];
};

class SHA256{
public:
	SHA256() {
		INIT();//initial value
	};
	~SHA256(){};
	Message_Digest Deal(UInt32 W[16]);
private:
	void INIT();//initial
	UInt32 ROTR(UInt32 W, int n);//����ת
	UInt32 ROTL(UInt32 W, int n);//����ת
	UInt32 SHR(UInt32 W, int n);//����λ
	Message_Digest MD;
};

#endif


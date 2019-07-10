/*
1. Floating to Fixed Point

2. Fixed to Floating Point
   Fixed Point(FIX_16_16)

2014707082 �̿���
Computer Architecture Homework
*/
#define FLOAT 0
#define FIXED 1
#include <stdio.h>

void Masking(int Fake, int* expo, int* menti);//exponential part, mentissa part �и�
void bits_represent(int, const int);//Print bit stream Function

int main(void)
{
	float num = 0;

	//bits ������ �и��ϱ����� ������
	int ftexpo_Int = 0;
	int ftmenti_Int = 0;
	int fXexpo_Int = 0;
	int fXmenti_Int = 0;
	int bit_shift = 0;// floating point�� exponential part���� ���� shift Ƚ��
	int Fakein = 0;// �Է��� floating number�� int�� ���̱� ���� ����
	int fXbitstream = 0;//����1���� fixed point�� ������ ����
	int fXbitstream_twos = 0; //���� 1���� fixed point(two's complement)�� ������ ����
	int Sbit = 0; //signed bit�� 0���� 1���� �Ǵ�
	int ftbitstream = 0;//����2���� floating point�� ������ ����
	int fixedMSB = 0; //fixed point�� �ֻ�����Ʈ ��ġ�� ������ ����
	int a = 0;
	puts("Put Your Number: ");
	scanf("%f", &num);
	if (num < 0)
		Sbit = 1;
	Fakein = *(int *)&num;

	printf("\n---------------------------------\n");
	printf("Floating Point\n");
	bits_represent(Fakein,FLOAT);

	printf("\n------------ HW 1 --------------\n");
	Masking(Fakein, &ftexpo_Int, &ftmenti_Int); //exponential part�� mentissa�� �и��Ѵ�.

	bit_shift=(ftexpo_Int - 0x3F800000)>>23; // exponential part���� 127�� �� ���� bit shift �� �̴�.
	fXbitstream = ftmenti_Int + 0x00800000; //mentissa part�� �տ� 1��Ʈ�� ���� ���� fixed point�� bit stream�̴�.
	fXbitstream =fXbitstream >> (7-bit_shift);//Floating mentissa bits length - Fixed mentissa bits length ���� bitshift��ŭ ���͸�ŭ shift�ϸ� Fixed point �ϼ�
											  
	//Signed bit ==1
	if (Sbit == 1) {
		fXbitstream = fXbitstream + 0x80000000;//������ ��� ��ȣ ��Ʈ�� �־��ش�.
		fXbitstream_twos=(fXbitstream ^ 0x7FFFFFFF) + 1; //two's complement �ΰ��
	}
	else
		fXbitstream_twos = fXbitstream;

	printf("Fixed Point - Signed and Magnitude Expression\n");
	bits_represent(fXbitstream,FIXED);
	printf("\n");
	printf("Fixed Point - Two's Complement Expression\n");
	bits_represent(fXbitstream_twos, FIXED);
	printf("\n------------ HW 2 --------------\n");
	fixedMSB = 16 + bit_shift;//16�� bit shift�Ѹ�ŭ�� fixed point�� �ֻ��� ��Ʈ�̴�.
	ftexpo_Int=(bit_shift + 127)<<23; //���� bit shift�ߴ� �Ϳ� 127�� ���ϸ� exponential part�̴�. 

	ftmenti_Int=(fXbitstream&(0xFFFFFFFF >> (16 - bit_shift)))<< (7 - bit_shift);  //floating point�� mentissa�� fixed point�� ������ bits�� ���̸�ŭ���� bit_shift������ �� ��ŭ shift�Ѵ�.

	ftbitstream = ftexpo_Int + ftmenti_Int; //floating point = exponential part + mentissa part
	
	if (Sbit == 1)
		ftbitstream = ftbitstream + 0x80000000;//������ ��� ��ȣ ��Ʈ�� �־��ش�.	

	printf("Floating Point\n");
	bits_represent(ftbitstream,FLOAT);

	return 0;
}

// �Է��� ������ exponential part, mentissa part �и�
void Masking(int Fake,int* expo, int* menti)
{	int fP_exMask = 0x7F800000;
	int fP_menMask = 0x007FFFFF;

	*expo = (Fake & fP_exMask);
	*menti = (Fake & fP_menMask);
}

//bit stream�� ����ϴ� �Լ�
void  bits_represent(int Fake, const int flag)
{
	//Fixed Point�� ǥ���ϴ� ���
	if (flag == FIXED) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 15)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bit AND ������ ���ؼ� �ش� ��Ʈ�� ����
		}
	}
	//Floating�� ǥ���ϴ� ���
	else if (flag == FLOAT) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 22)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bit AND ������ ���ؼ� �ش� ��Ʈ�� ����
		}
	}
	printf("\n");
}
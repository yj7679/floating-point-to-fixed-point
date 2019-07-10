/*
1. Floating to Fixed Point

2. Fixed to Floating Point
   Fixed Point(FIX_16_16)

2014707082 이용직
Computer Architecture Homework
*/
#define FLOAT 0
#define FIXED 1
#include <stdio.h>

void Masking(int Fake, int* expo, int* menti);//exponential part, mentissa part 분리
void bits_represent(int, const int);//Print bit stream Function

int main(void)
{
	float num = 0;

	//bits 영역을 분리하기위한 변수들
	int ftexpo_Int = 0;
	int ftmenti_Int = 0;
	int fXexpo_Int = 0;
	int fXmenti_Int = 0;
	int bit_shift = 0;// floating point의 exponential part에서 얻은 shift 횟수
	int Fakein = 0;// 입력한 floating number를 int로 속이기 위한 변수
	int fXbitstream = 0;//과제1에서 fixed point를 저장할 변수
	int fXbitstream_twos = 0; //과제 1에서 fixed point(two's complement)를 저장할 변수
	int Sbit = 0; //signed bit가 0인지 1인지 판단
	int ftbitstream = 0;//과제2에서 floating point를 저장할 변수
	int fixedMSB = 0; //fixed point의 최상위비트 위치를 저장할 변수
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
	Masking(Fakein, &ftexpo_Int, &ftmenti_Int); //exponential part와 mentissa를 분리한다.

	bit_shift=(ftexpo_Int - 0x3F800000)>>23; // exponential part에서 127을 뺀 것이 bit shift 수 이다.
	fXbitstream = ftmenti_Int + 0x00800000; //mentissa part에 앞에 1비트를 붙인 것이 fixed point의 bit stream이다.
	fXbitstream =fXbitstream >> (7-bit_shift);//Floating mentissa bits length - Fixed mentissa bits length 에서 bitshift만큼 뺀것만큼 shift하면 Fixed point 완성
											  
	//Signed bit ==1
	if (Sbit == 1) {
		fXbitstream = fXbitstream + 0x80000000;//음수인 경우 부호 비트를 넣어준다.
		fXbitstream_twos=(fXbitstream ^ 0x7FFFFFFF) + 1; //two's complement 인경우
	}
	else
		fXbitstream_twos = fXbitstream;

	printf("Fixed Point - Signed and Magnitude Expression\n");
	bits_represent(fXbitstream,FIXED);
	printf("\n");
	printf("Fixed Point - Two's Complement Expression\n");
	bits_represent(fXbitstream_twos, FIXED);
	printf("\n------------ HW 2 --------------\n");
	fixedMSB = 16 + bit_shift;//16에 bit shift한만큼이 fixed point의 최상위 비트이다.
	ftexpo_Int=(bit_shift + 127)<<23; //원래 bit shift했던 것에 127을 더하면 exponential part이다. 

	ftmenti_Int=(fXbitstream&(0xFFFFFFFF >> (16 - bit_shift)))<< (7 - bit_shift);  //floating point의 mentissa와 fixed point의 가수부 bits수 차이만큼에서 bit_shift개수를 뺀 만큼 shift한다.

	ftbitstream = ftexpo_Int + ftmenti_Int; //floating point = exponential part + mentissa part
	
	if (Sbit == 1)
		ftbitstream = ftbitstream + 0x80000000;//음수인 경우 부호 비트를 넣어준다.	

	printf("Floating Point\n");
	bits_represent(ftbitstream,FLOAT);

	return 0;
}

// 입력한 값에서 exponential part, mentissa part 분리
void Masking(int Fake,int* expo, int* menti)
{	int fP_exMask = 0x7F800000;
	int fP_menMask = 0x007FFFFF;

	*expo = (Fake & fP_exMask);
	*menti = (Fake & fP_menMask);
}

//bit stream을 출력하는 함수
void  bits_represent(int Fake, const int flag)
{
	//Fixed Point를 표현하는 경우
	if (flag == FIXED) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 15)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bit AND 연산을 통해서 해당 비트를 추출
		}
	}
	//Floating을 표현하는 경우
	else if (flag == FLOAT) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 22)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bit AND 연산을 통해서 해당 비트를 추출
		}
	}
	printf("\n");
}
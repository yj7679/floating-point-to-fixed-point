/*
KwangWoon Univ
Yong Jik Lee
Computer architecture

1. Floating to Fixed Point

2. Fixed to Floating Point
   Fixed Point(FIX_16_16)

*/
#define FLOAT 0
#define FIXED 1
#include <stdio.h>

void Masking(int Fake, int* expo, int* menti);//To seperate exponential part and mentissa part
void bits_represent(int, const int);//To print bit stream Function

int main(void)
{
	float num = 0;


	int ftexpo_Int = 0;
	int ftmenti_Int = 0;
	int fXexpo_Int = 0;
	int fXmenti_Int = 0;
	int bit_shift = 0;
	int Fakein = 0;// To deceive a as b
	int fXbitstream = 0;// the fixed point value
	int fXbitstream_twos = 0; //the fixed point(two's complement)
	int Sbit = 0; // The signed bit 0 or 1
	int ftbitstream = 0;// The floating point value
	int fixedMSB = 0; // the MSB of fixed point
	int a = 0;
	puts("Put Your Number: ");
	scanf("%f", &num);
	if (num < 0)
		Sbit = 1;
	Fakein = *(int *)&num;

	printf("\n---------------------------------\n");
	printf("Floating Point\n");
	bits_represent(Fakein, FLOAT);

	printf("\n------------ HW 1 --------------\n");
	Masking(Fakein, &ftexpo_Int, &ftmenti_Int); // To sperate exponential part and mentissa

	bit_shift = (ftexpo_Int - 0x3F800000) >> 23; // exponential part - 127 = bit shift count
	fXbitstream = ftmenti_Int + 0x00800000; // What Add 1-bit to MSB is the bits stream of fixed point.
	fXbitstream = fXbitstream >> (7 - bit_shift);// Making Fixed point

	//Signed bit ==1
	if (Sbit == 1) {
		fXbitstream = fXbitstream + 0x80000000;//signed bit processing
		fXbitstream_twos = (fXbitstream ^ 0x7FFFFFFF) + 1; //two's complement
	}
	else
		fXbitstream_twos = fXbitstream;

	printf("Fixed Point - Signed and Magnitude Expression\n");
	bits_represent(fXbitstream, FIXED);
	printf("\n");
	printf("Fixed Point - Two's Complement Expression\n");
	bits_represent(fXbitstream_twos, FIXED);
	printf("\n------------ HW 2 --------------\n");

	//bit level operation
	fixedMSB = 16 + bit_shift;
	ftexpo_Int = (bit_shift + 127) << 23;

	ftmenti_Int = (fXbitstream&(0xFFFFFFFF >> (16 - bit_shift))) << (7 - bit_shift);

	ftbitstream = ftexpo_Int + ftmenti_Int; //floating point = exponential part + mentissa part

	if (Sbit == 1)
		ftbitstream = ftbitstream + 0x80000000;// Signed bit processing

	printf("Floating Point\n");
	bits_represent(ftbitstream, FLOAT);

	return 0;
}

// Seperate exponential part, mentissa part
void Masking(int Fake, int* expo, int* menti)
{
	int fP_exMask = 0x7F800000;
	int fP_menMask = 0x007FFFFF;

	*expo = (Fake & fP_exMask);
	*menti = (Fake & fP_menMask);
}

//print bit stream
void  bits_represent(int Fake, const int flag)
{
	//Fixed Point expression
	if (flag == FIXED) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 15)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bits prin with bit AND operation
		}
	}
	//Floating point expression
	else if (flag == FLOAT) {
		for (int i = 31; i >= 0; i--)
		{
			if (i == 30 || i == 22)
				printf(" ");
			printf("%d", (Fake & (1 << i)) ? 1 : 0);//bits prin with bit AND operation
		}
	}
	printf("\n");
}

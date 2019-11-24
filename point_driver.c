#include <stdio.h>
#include "point.h"

int main()
{
	/* KAMUS */
	POINT P1, P2;
	POINT PGeserX, PGeserY, PGeser, PPutar, PMirrorX, PMirrorY;
	float X, Y;
	float Sudut;
	
	/* ALGORITMA */
	
	// Mengecek BacaPOINT dan MakePOINT
	printf("Masukkan titik 1\n");
	BacaPOINT(&P1);
	printf("Masukkan titik 2\n");
	BacaPOINT(&P2);
	
	// Mengecek TulisPOINT dan MakePOINT
	printf("Titik yang disimpan:\n");
	printf("Titik 1: ");
	TulisPOINT(P1);
	printf("\n");
	printf("Titik 2: ");
	TulisPOINT(P2);
	printf("\n");
	
	// Mengecek EQ
	printf("Apakah titik 1 sama dengan titik 2?\n");
	if (EQ(P1, P2))
	{
		printf("Ya\n");
	}
	else
	{
		printf("Tidak\n");
	}
	
	// Mengecek NEQ
	printf("Apakah titik 1 berbeda dengan titik 2?\n");
	if (NEQ(P1, P2))
	{
		printf("Ya\n");
	}
	else
	{
		printf("Tidak\n");
	}
	
	// Mengecek IsOrigin
	if (IsOrigin(P1))
	{
		printf("Titik 1 adalah titik origin\n");
	}
	else
	{
		printf("Titik 1 bukan titik origin\n");
		if (IsOnSbX(P1) || IsOnSbY(P1))
		{
			// Mengecek IsOnSbX
			if (IsOnSbX(P1))
			{
				printf("Tapi berada di sumbu X\n");
			}
			else
			{
				printf("Titik 1 juga tidak di sumbu X\n");
			}
			
			// Mengecek IsOnSbY
			if (IsOnSbY(P1))
			{
				printf("Tapi berada di sumbu Y\n");
			}
			else
			{
			printf("Titik 1 juga tidak di sumbu Y\n");
			}
		}
		else
		{
			// Mengecek Kuadran
			printf("Titik 1 ada di kuadran %d\n", Kuadran(P1));
		}
	}
	
	// Mengecek NextX
	printf("Jika titik 1 digeser 1 satuan ke kanan: ");
	TulisPOINT(NextX(P1));
	printf("\n");
	
	// Mengecek NextY
	printf("Jika titik 1 digeser 1 satuan ke atas: ");
	TulisPOINT(NextY(P1));
	printf("\n");
	
	// Mengecek Jarak0
	printf("Jarak titik 1 ke titik origin: %f\n", Jarak0(P1));
	
	// Mengecek Panjang
	printf("Jarak antara titik 1 dan titik 2: %f\n", Panjang(P1, P2));
	
	// Mengecek GeserKeSbX
	printf("Titik 1 jika digeser ke sumbu X menjadi: ");
	PGeserX = P1;
	GeserKeSbX(&PGeserX);
	TulisPOINT(PGeserX);
	printf("\n");
	
	// Mengecek GeserKeSbY
	printf("Titik 1 jika digeser ke sumbu Y menjadi: ");
	PGeserY = P1;
	GeserKeSbY(&PGeserY);
	TulisPOINT(PGeserY);
	printf("\n");
	
	printf("Masukkan angka untuk menggeser titik 1\n");
	printf("X: ");
	scanf("%f", &X);
	printf("Y: ");
	scanf("%f", &Y);
	
	// Mengecek PlusDelta
	printf("Titik 1 jika digeser %f searah sumbu X dan %f searah sumbu Y menjadi (dengan PlusDelta): ", X, Y);
	TulisPOINT(PlusDelta(P1, X, Y));
	printf("\n");
	
	// Mengecek PlusDelta dan Geser
	printf("Titik 1 jika digeser %f searah sumbu X dan %f searah sumbu Y menjadi (dengan Geser): ", X, Y);
	PGeser = P1;
	Geser(&PGeser, X, Y);
	TulisPOINT(PGeser);
	printf("\n");
	
	// Mengecek Mirror
	printf("Titik 1 jika dicerminkan terhadap sumbu X: ");
	TulisPOINT(MirrorOf(P1, true));
	printf("\n");
	printf("Titik 1 jika dicerminkan terhadap sumbu Y: ");
	TulisPOINT(MirrorOf(P1, false));
	printf("\n");
	
	// Mengecek MirrorOf dan Mirror
	printf("Titik 1 jika dicerminkan terhadap sumbu X: ");
	PMirrorX = P1;
	Mirror(&PMirrorX, true);
	TulisPOINT(PMirrorX);
	printf("\n");
	printf("Titik 1 jika dicerminkan terhadap sumbu Y: ");
	PMirrorY = P1;
	Mirror(&PMirrorY, false);
	TulisPOINT(PMirrorY);
	printf("\n");
	
	// Mengecek Putar
	printf("Masukkan sudut untuk menggeser titik 1\n");
	scanf("%f", &Sudut);
	printf("Titik 1 jika digeser dengan sudut %f terhadap (0,0) menjadi: ", Sudut);
	PPutar = P1;
	Putar(&PPutar, Sudut);
	TulisPOINT(PPutar);
	printf("\n");
	
	return 0;
}

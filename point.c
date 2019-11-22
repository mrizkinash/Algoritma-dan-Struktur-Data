#include "point.h"
#include <math.h>
#include <stdio.h>

        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	POINT P;

	Absis(P)	= X;
	Ordinat(P)	= Y; 

	return P;
}
/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
	int x,y;
	scanf("%d %d",&x, &y);
	*P = MakePOINT(x,y);
}
void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                
{
	printf("(%d,%d)",Absis(P),Ordinat(P));
}
/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQPoint (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	return((Absis(P1) == Absis(P2)) &&(Ordinat(P1) == Ordinat(P2)));
}
boolean NEQPoint (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
	return((Absis(P1) != Absis(P2)) || (Ordinat(P1) != Ordinat(P2)));

}
/* *** Kelompok menentukan di mana P berada *** */
boolean IsOriginPoint (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
	return((Absis(P) == 0) &&(Ordinat(P) == 0));
}
boolean IsOnSbXPoint (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
	return(Ordinat(P) == 0);
}
boolean IsOnSbYPoint (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
	return(Absis(P) == 0);
}

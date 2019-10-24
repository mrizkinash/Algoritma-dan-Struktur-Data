/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
#include "boolean.h"
#include "queue.h"
#include "stdlib.h"
/* ********* Prototype ********* */
boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
	return(Tail(Q) ==0 && Head(Q) == 0);
}
boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
	return(Tail(Q) == MaxEl(Q));
}
int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if (IsEmpty(Q)) {
		return Nil;
	} else if (Head(Q) <= Tail(Q)){
		return (Tail(Q)-Head(Q)+1);
	} else {
		return (MaxEl(Q) - Head(Q) + Tail(Q) + 1);
	}
}
/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (infotype *) malloc ((Max+1) * sizeof(infotype));
	if((*Q).T != NULL){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
		MaxEl(*Q) = Max;
	} else {
		(*Q).MaxEl = 0;
	}

}
/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
	free((*Q).T);
	MaxEl(*Q) =Nil;
}
/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	if(IsEmpty(*Q)){
		Head(*Q) =1;
		Tail(*Q) =1;
		InfoHead(*Q) = X; 
	} else {
		if(IsFull(*Q)){
			Tail(*Q) =1;
			InfoTail(*Q) =X;
		} else {
			Tail(*Q)++;
			InfoTail(*Q) =X;
		}
	}
}
void Del (Queue * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{

	*X = InfoHead(*Q);
	if(IsFull(*Q)){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}else {
		Head(*Q)++;
	}
}

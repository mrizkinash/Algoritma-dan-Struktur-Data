/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */


#include "boolean.h"
#include "stackt.h"

#include <stdlib.h>

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElST */
/* jadi indeksnya antara 1.. MaxElST+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai NilST */
{
	Top(*S) = NilST;
}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return(Top(S) == NilST);
}
boolean IsFull (Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
	return (Top(S) == MaxElST);
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushStack (Stack * S, infotypeST X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{	
	state NS;

	Top(*S)++;
	CopyState(X, &NS);
	InfoTop(*S) = NS;
}
/* ************ Menghapus sebuah elemen Stack ************ */
void PopStack (Stack * S, infotypeST* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
	*X =InfoTop(*S);
	Top(*S)--;
}


void CopyState (state Sin, state *Sout){
	Player P1out, P2out;
	TabInt ABout;

	CopyQueue(Sin.P1.skill, &(Sout->P1.skill));					// Yang dicopy yang bersifat dinamik
	Sout->P1.turn = Sin.P1.turn;
	CopyList(Sin.P1.listbangunan, &(Sout->P1.listbangunan));
	Sout->P1.et = Sin.P1.et;
	Sout->P1.shieldturn = Sin.P1.shieldturn;
	CopyQueue(Sin.P2.skill, &(Sout->P2.skill));
	Sout->P2.turn = Sin.P2.turn;
	CopyList(Sin.P2.listbangunan, &(Sout->P2.listbangunan));
	Sout->P2.et = Sin.P2.et;
	Sout->P2.shieldturn = Sin.P2.shieldturn;
	CopyArr(Sin.ArrBang, &(Sout->ArrBang));
	Sout->M = Sin.M;
	Sout->G = Sin.G;											// Graph dinamik namun tidak pernah mengalami perubahan selama permainan
}

void DeallocState(state *S){

	DeAlokasiQueue(&(S->P1.skill));
	DealokasiLB(&First(S->P1.listbangunan));
	DeAlokasiQueue(&(S->P2.skill));
	DealokasiLB(&First(S->P2.listbangunan));
	DealokasiAB(&(S->ArrBang));
}
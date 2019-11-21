/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressL dengan pointer */
/* infotype adalah integer */

#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLB (List L)
/* Mengirim true jika list kosong */
{
	return(FirstL(L) == Nil);
}
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLB (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	FirstL(*L) = Nil;
}
/****************** Manajemen Memori ******************/
addressL AlokasiLB (infotype X)
/* Mengirimkan addressL hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressL tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	//Kamus Lokal
	addressL P;

	//Algo
	P = (addressL) malloc (sizeof (ElmtListL));
	if (P != Nil) {
		Info(P) = X;
		Next(P) = Nil;
		return P;
	} else {
		return Nil;
	}
}
void DealokasiLB (addressL *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressL P */
{
	free(*P);
}
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressL SearchLB (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan addressL elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	addressL P;
	boolean found = false;
	P = FirstL(L);

	while((P!= Nil)&& (!(found))){
		if(Info(P) == X){
			found = true;
		} else{
			P = Next(P);
		}
	}
	return P;
}
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstLB (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	//kamus
	addressL P;

	//Algo
	P = AlokasiLB(X);
	if (P != Nil) {
		InsertFirstLB(L, P);
	}
}
void InsVLastLB (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	//kamus
	addressL P;

	//Algo
	P = AlokasiLB(X);
	if (P != Nil) {
		InsertLastLB(L, P);
	}
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstLB (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	addressL P;
	P =FirstL(*L);
	*X = Info(P);
	FirstL(*L) = Next(FirstL(*L));
	Next(P) = Nil;
	DealokasiLB(&P);
}
void DelVLastLB (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	addressL P;
	DelLastLB(L,&P);
	*X = Info(P);
	DealokasiLB(&P);
}
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLB (List *L, addressL P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressL P sebagai elemen pertama */
{
	Next(P) = FirstL(*L);
	FirstL(*L) = P;
}
void InsertAfterLB (List *L, addressL P, addressL Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;

}
void InsertLastLB (List *L, addressL P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	addressL Pr;
	if(IsEmptyLB(*L)){
		InsertFirstLB(L,P);
	} else{
		Pr = FirstL(*L);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		InsertAfterLB(L,P,Pr);
	}
}
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstLB (List *L, addressL *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P =FirstL(*L);
	FirstL(*L) = Next(FirstL(*L));
	Next(*P) = Nil;
}
void DelPLB (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressL P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	addressL P = SearchLB(*L, X);

    if (P != Nil){   
        addressL prec = FirstL(*L);

        if (prec == P){ 
            DelFirstLB(L, &P);
        }
        else {

            while(Next(prec) != P) { 
                prec = Next(prec);
            }

            DelAfterLB(L, &P, prec);
        }
    }
    DealokasiLB(&P);

}
void DelLastLB (List *L, addressL *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
	addressL Prec;
	*P = FirstL(*L);
	Prec = Nil;
	
	while(Next(*P) != Nil){
		Prec = (*P);
		*P = Next(*P);
	}

	if(Prec == Nil){
		FirstL(*L) = Nil;
	} else{
		Next(Prec) = Nil;
	}

}
void DelAfterLB (List *L, addressL *Pdel, addressL Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel =Next(Prec);
	Next(Prec) = Next(Next(Prec));
	Next(*Pdel) = Nil;
}
/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfoLB (List L, TabInt ArrBang)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	addressL P;
	
	P = FirstL(L);
	if (P != Nil) {
		int idxb=Info(P);
		printf("Tipe: %c ",Type(ElmtArr(ArrBang, idxb)));
		printf("(%d,%d) ", AbsisBangunan(ElmtArr(ArrBang, idxb)), OrdinatBangunan(ElmtArr(ArrBang, idxb)) );
		printf("%d ",Army(ElmtArr(ArrBang, idxb)));
		printf("lv. %d\n",Level(ElmtArr(ArrBang, idxb)));
	}
	P = Next(P);
	while (P != Nil) {
		int idxb=Info(P);
		printf("Tipe: %c ",Type(ElmtArr(ArrBang, idxb)));
		printf("(%d,%d) ", AbsisBangunan(ElmtArr(ArrBang, idxb)), OrdinatBangunan(ElmtArr(ArrBang, idxb)) );
		printf("%d ",Army(ElmtArr(ArrBang, idxb)));
		printf("lv. %d\n",Level(ElmtArr(ArrBang, idxb)));
	}
}
int NbElmtLB (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	int count =0;
	addressL P = FirstL(L);

	while(P != Nil){
		count++;
		P = Next(P);
	}
	return count;
}

int CariIdxB(List L, int n){
	addressL P=FirstL(L);
	int idx;
	while(P!=Nil && n>0){
		idx=Info(P);
		P=Next(P);
	}
	return idx;
}
/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>
/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLB (List L)
/* Mengirim true jika list kosong */
{
	return(First(L) == Nil);
}
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLB (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	First(*L) = Nil;
}
/****************** Manajemen Memori ******************/
address AlokasiLB (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	//Kamus Lokal
	address P;

	//Algo
	P = (address) malloc (sizeof (ElmtList));
	if (P != Nil) {
		Info(P) = X;
		Battle(P)=false;
		Next(P) = Nil;
		return P;
	} else {
		return Nil;
	}
}
void DealokasiLB (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(*P);
}
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchLB (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	address P;
	boolean found = false;
	P = First(L);

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
	address P;

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
	address P;

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
	address P;
	P =First(*L);
	*X = Info(P);
	First(*L) = Next(First(*L));
	Next(P) = Nil;
	DealokasiLB(&P);
}
void DelVLastLB (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	address P;
	DelLastLB(L,&P);
	*X = Info(P);
	DealokasiLB(&P);
}
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLB (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;
}
void InsertAfterLB (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;

}
void InsertLastLB (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	address Pr;
	if(IsEmptyLB(*L)){
		InsertFirstLB(L,P);
	} else{
		Pr = First(*L);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		InsertAfterLB(L,P,Pr);
	}
}
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstLB (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P =First(*L);
	First(*L) = Next(First(*L));
	Next(*P) = Nil;
}
void DelPLB (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	address P = SearchLB(*L, X);

    if (P != Nil){   
        address prec = First(*L);

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
void DelLastLB (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
	address Prec;
	*P = First(*L);
	Prec = Nil;
	
	while(Next(*P) != Nil){
		Prec = (*P);
		*P = Next(*P);
	}

	if(Prec == Nil){
		First(*L) = Nil;
	} else{
		Next(Prec) = Nil;
	}

}
void DelAfterLB (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel =Next(Prec);
	Next(Prec) = Next(Next(Prec));
	Next(*Pdel) = Nil;
}
/****************** PROSES SEMUA ELEMEN LIST ******************/

int NbElmtLB (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	int count =0;
	address P = First(L);

	while(P != Nil){
		count++;
		P = Next(P);
	}
	return count;
}

int CariIdxB(List L, int n){
	address P=First(L);
	int idx;
	while(P!=Nil && n>0){
		idx=Info(P);
		P=Next(P);
		n--;
	}
	return idx;
}

boolean CekAttack(List L, int x){
	address P = First(L);
	while(P!=Nil){
		if(x==1) return Battle(P);
		else{
			P = Next(P);
			x--;
		}
	}
	return false;
}

void SudahAttack(List *L, int x){
	address P = First(*L);
	while(P!=Nil){
		if(x==1){
			//printf("%d sudah pernah\n", Info(P));
			Battle(P)=true;
			P = Next(P);
			x--;
		}
		else{
			P = Next(P);
			x--;
		}
	}
}
// bangunan ke x di list sudah battle

void CetakListB(List L, TabInt ArrBang){
	address P = First(L);
	int i=1;
	while(P!=Nil){
		printf("%d. ",i);
		CetakBangunan(ArrBang.TI[Info(P)]);
		i++;
		P=Next(P);
	}
}

void ResetBattle(List *L){
	address P = First(*L);
	while(P!=Nil){
		Battle(P)=false;
		P=Next(P);
	}
}

boolean ceklvl4(List L, TabInt ArrBang){
	address P = First(L);
	while(P!=Nil){
		if(Level(ArrBang.TI[Info(P)])!=4) return false;
		P = Next(P);
	}
	return true;
}

boolean AllAttack(List L,TabInt ArrBang){
	address P;
	P = First(L);
	while(P!=Nil){
		if(Battle(P)==false) return false;
		P = Next(P);
	}
	return true;
}

void AddPasukanLB(List L,TabInt *ArrBang){
	address P;
	P = First(L);
	while(P!=Nil){				
		AddPasukan(&(ArrBang->TI[Info(P)]));
		//printf("%d added\n",Info(P));
		P = Next(P);
	}
}
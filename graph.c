#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyG (MultiList G){
    return(First(G)==Nil);
}
/* Mengirim true jika tidak ada bangunan */
boolean IsEmptyCon (MultiList G, address X){
    return (Next2(X) == Nil);
}
/* Mengirim true jika tidak ada bangunan */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (MultiList *G){
    First(*G)=Nil;
}
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmptyCon (MultiList *G, address P){
    Next2(P)=Nil;
}
/* membuat list yang terhubung dengan L berisi info X */

/****************** Manajemen Memori ******************/
address AlokasiG (infotype X){
    address P;
	P = (address) malloc (sizeof (ElmtList));
	if (P != Nil) {
		Info(P) = X;
		Next(P) = Nil;
        Next2(P) = Nil;
		return P;
	} else return Nil;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

address2 AlokasiCon (infotype X){
    address2 P2;
	P2 = (address2) malloc (sizeof (ElmtList2));
	if (P2 != Nil) {
		Info(P2) = X;
		Next2(P2) = Nil;
		return P;
	} else return Nil;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next2(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiG (address *P){
    free(*P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

void DealokasiCon (address2 *P){
    free(*P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchG (MultiList G, infotype X){
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
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

address2 SearchCon (MultiList G, address P, infotype X){
    address2 P2=Next2(P);
    boolean found = false;
    while(P2!=Nil && !found){
        if(Info(P2)==X) found = true;
        else P2 = Next2(P2);
    }
    return P2;
}
/* mencari address bangunan Y yang terdapat dalam hubungan dengan bangunan X */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
//void InsVFirstG (MultiList *G, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastG (MultiList *G, infotype X){
    address P;
	P = AlokasiG(X);
    
	if (P != Nil) {
		InsertLastG(G, P);
	}
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

//void InsVFirstCon (MultiList *G, address P, infotype Y);

void InsVLastCon (MultiList *G, address P, infotype X){
    address2 P2 = AlokasiCon(X);
    if (P2 != Nil) {
		InsertLastCon(G, P, P2);
	}
}


/*** PENGHAPUSAN ELEMEN ***/
//void DelVFirstG (MultiList *G, infotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
//void DelVLastG (MultiList *G, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
//void DelVFirstCon (MultiList *G, address P,infotype *Y);

//void DelVLastCon (MultiList *G, address P, infotype *Y);


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
//void InsertFirstG (MultiList *G, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
//void InsertAfterG (MultiList *G, address P, address Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastG (MultiList *G, address P){
    address Pr;
	if(IsEmptyLB(*G)){
		Next(P) = First(*G);
	    First(*G) = P;
	} else{
		Pr = First(*G);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		Next(P) = Next(Pr);
	    Next(Pr) = P;
	}
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertFirstCon (MultiList *G, address P1, address2 P2){
    address2 Pr;
	if(IsEmptyLB(*G)){
		Next2(P2) = Next2(P1);
	    Next2(P1) = P2;
	} else{
		Pr = Next2(P1);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		Next(P2) = Nil;
	    Next(Pr) = P2;
	}
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
//void InsertAfterCon (MultiList *G, address P1, address2 P2, address2 Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
//void InsertLastCon (MultiList *G, address P1, address2 P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
//void DelFirstG (MultiList *G, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
//void DelPG (MultiList *G, infotype X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
//void DelLastG (MultiList *G, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
//void DelAfterG (MultiList *G, address *Pdel, address Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtCon (MultiList G, infotype X){
    int cnt=0;
    address P=SearchG(G,X);
    address2 P2=Next2(P);
    while(Next2(P2)!=Nil){
        cnt+=1;
        P2=Next2(P2);
    }
    return cnt;
}
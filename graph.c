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
/* Mengirim true jika tidak ada bangunan yang terhubung dengan bangunan ber address X */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (MultiList *G){
    First(*G)=Nil;
}
/* I.S. sembarang             */
/* F.S. Terbentuk Multilist */
void CreateEmptyCon (MultiList *G, address P){
    Next2(P)=Nil;
}
/* membuat list yang berisi keterhubungan dengan bangunan ber address P  */

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
		return P2;
	} else return Nil;
}
/* Mengirimkan address2 hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address2 tidak nil, dan misalnya */
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
/* Melakukan dealokasi/pengembalian address2 P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchG (MultiList G, infotype X){
    address P;
	boolean found = false;
	P = First(G);

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


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertLastG (MultiList *G, address P){
    address Pr;
	if(IsEmptyG(*G)){
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
void InsertLastCon (MultiList *G, address P1, address2 P2){
    address2 Pr;
	if(Next2(P1)==Nil){
		Next2(P2) = Next2(P1);
	    Next2(P1) = P2;
	} else{
		Pr = Next2(P1);
		while(Next2(Pr) != Nil){
			Pr =Next2(Pr);
		}
		Next2(P2) = Nil;
	    Next2(Pr) = P2;
	}
}

void InsVLastCon (MultiList *G, address P, infotype X){
    address2 P2 = AlokasiCon(X);
    if (P2 != Nil) {
		InsertLastCon(G, P, P2);
	}
}

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

void CetakBConnected(MultiList G, infotype X){
    address P = SearchG(G,X);
    address2 P2 = Next2(P);
    int i=1;
    while(Next2(P2)!=Nil){
        printf("%d. ",i);
        CetakBangunan(ArrBang[Info(P2)]);
    }
}
// mencetak seluruh bangunan yang terhubung dengan bangunan X

int CariIdxBCon(MultiList G, infotype X, infotype Y){
    address P = SearchG(G,X);
    address2 P2 = Next2(P);
    int ans;
    while(P2!=Nil && Y>0){
        ans = Info(P2);
        Y--;
        P2 = Next2(P2);
    }
    return ans;
}
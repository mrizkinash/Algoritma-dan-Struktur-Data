#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyG (Graph G){
    return(FirstG(G)==Nil);
}
/* Mengirim true jika tidak ada bangunan */
boolean IsEmptyCon (Graph G, address X){
    return (Next(X) == Nil);
}
/* Mengirim true jika tidak ada bangunan yang terhubung dengan bangunan ber address X */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (Graph *G){
    FirstG(*G)=Nil;
}
/* I.S. sembarang             */
/* F.S. Terbentuk Graph */
void CreateEmptyCon (Graph *G, address P){
    Next(P)=Nil;
}
/* membuat list yang berisi keterhubungan dengan bangunan ber address P  */

/****************** Manajemen Memori ******************/
adrG AlokasiG (infotype X){
    adrG P;
	P = (address) malloc (sizeof (ElmtRow));
	if (P != Nil) {
		Info(P) = X;
		Nextg(P) = Nil;
        Next(P) = Nil;
		return P;
	} else return Nil;
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

adrG AlokasiCon (infotype X){
    adrG P2;
	P2 = (address) malloc (sizeof (ElmtList));
	if (P2 != Nil) {
		Info(P2) = X;
		Next(P2) = Nil;
		return P2;
	} else return Nil;
}
/* Mengirimkan address2 hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address2 tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next2(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiG (adrG *P){
    free(*P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

void DealokasiCon (address *P){
    free(*P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address2 P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
adrG SearchG (Graph G, infotype X){
    adrG P;
	boolean found = false;
	P = FirstG(G);

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

address SearchCon (Graph G, adrG P, infotype X){
    address P2=Next(P);
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
void InsVLastG (Graph *G, infotype X){
    adrG P;
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
void InsertLastG (Graph *G, adrG P){
    adrG Pr;
	if(IsEmptyG(*G)){
		Nextg(P) = FirstG(*G);
	    FirstG(*G) = P;
	} else{
		Pr = FirstG(*G);
		while(Nextg(Pr) != Nil){
			Pr =Nextg(Pr);
		}
		Nextg(P) = Nextg(Pr);
	    Nextg(Pr) = P;
	}
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertLastCon (Graph *G, adrG P1, address P2){
    address Pr;
	if(Next(P1)==Nil){
		Next(P2) = Next(P1);
	    Next(P1) = P2;
	} else{
		Pr = Next(P1);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		Next(P2) = Nil;
	    Next(Pr) = P2;
	}
}

void InsVLastCon (Graph *G, adrG P, infotype X){
    address P2 = AlokasiCon(X);
    if (P2 != Nil) {
		InsertLastCon(G, P, P2);
	}
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtCon (Graph G, infotype X){
    int cnt=0;
    adrG P=SearchG(G,X);
    address P2=Next(P);
    while(P2!=Nil){
        cnt+=1;
        P2=Next(P2);
    }
    return cnt;
}

int CariIdxBCon(Graph G, infotype X, infotype Y){
    adrG P = SearchG(G,X);
    address P2 = Next(P);
    int ans;
    while(P2!=Nil && Y>0){
        ans = Info(P2);
        Y--;
        P2 = Next(P2);
    }
    return ans;
}

void AddRel (Graph *G, int from, int to) {
    adrG R;
    address C;
    if (IsEmptyG(*G)) {
        R = AlokasiG(from);
        FirstG(*G) = R;
    } else {
        R = FirstG(*G);
        while (Nextg(R) != Nil && Info(R) != from) {
            R = Nextg(R);
        }
        if (Info(R) != from) {
            Nextg(R) = AlokRow(from);
            R = Nextg(R);
        }
    }
    if (Next(R) == Nil) {
        C = AlokasiCon(to);
        Next(R) = C;
    } else {
        C = Next(R);
        while (Next(C) != Nil && Info(C) != to) {
            C = Next(C);
        }
        if (Info(C) != to) {
            Next(C) = AlokasiCon(to);
        }
    }
}

adrG FindLastG (MultiList G){
    adrG P;

    P = FirstG(G);
    while (Next(P) != Nil){

        P = list(P);
    }

    return P;
}
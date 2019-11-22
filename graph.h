#ifndef graph_H
#define graph_H

#include "boolean.h"
#include "bangunan.h"
#include "arraydin.h"
#include "listlinier.h"

#define Nil NULL

typedef struct tElmtRow * adrG;

typedef struct tElmtRow {
	infotype info;
    adrG nextg;
	address next;
} ElmtRow;

typedef struct {
	adrG FirstG;
} Graph;

/* Definisi list : */
/* List kosong : FirstG(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil */

#define Info(P) (P)->info
#define Nextg(G) (G)->nextg
#define list(G) (G)->next
#define FirstG(G) ((G).FirstG)

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyG (Graph G);
/* Mengirim true jika tidak ada bangunan */
boolean IsEmptyCon (Graph G, address X);
/* Mengirim true jika tidak ada bangunan */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (Graph *G);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmptyCon (Graph *G, address P);
/* membuat list yang terhubung dengan L berisi info X */

/****************** Manajemen Memori ******************/
address AlokasiG (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

// address2 AlokasiCon (infotype X);
// /* Mengirimkan address hasil alokasi sebuah elemen */
// /* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
// /* menghasilkan P, maka Info(P)=X, Next2(P)=Nil */
// /* Jika alokasi gagal, mengirimkan Nil */

void DealokasiG (adrG *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

// void DealokasiCon (address2 *P);
// /* I.S. P terdefinisi */
// /* F.S. P dikembalikan ke sistem */
// /* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
adrG SearchG (Graph G, infotype X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

address SearchCon (Graph G, adrG P, infotype X);
/* mencari address bangunan Y yang terdapat dalam hubungan dengan bangunan X */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
//void InsVFirstGG (Graph *G, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastG (Graph *G, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertLastG (Graph *G, adrG P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertFirstGCon (Graph *G, adrG P1, address P2);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsVLastCon (Graph *G, adrG P, infotype X);

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtCon (Graph G, infotype X);
/* mengeluarkan jumlah bangunan yang terhubung dengan bangunan X */

int CariIdxBCon(Graph G, infotype X, infotype Y);

void AddRel (Graph *G, int from, int to);

adrG FindLastG (Graph G);

#endif
#ifndef graph_H
#define graph_H

#include "ADT/boolean.h"
#include "bangunan.h"

#define Nil NULL

typedef int infotype;
typedef struct tElmtlist *address;
typedef struct tElmtlist2 *address2;

typedef struct tElmtlist {
	infotype info;
	address next;
    address2 next2;
} ElmtList;


typedef struct tElmtlist2 {
	infotype info;
    address2 next2;
} ElmtList2;

typedef struct {
	address First;
} MultiList;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil */

#define Info(P) (P)->info
#define Next(P) (P)->next
#define Next2(P) (P)->next2
#define First(G) ((G).First)

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyG (MultiList G);
/* Mengirim true jika tidak ada bangunan */
boolean IsEmptyCon (MultiList G, address X);
/* Mengirim true jika tidak ada bangunan */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (MultiList *G);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmptyCon (MultiList *G, address P);
/* membuat list yang terhubung dengan L berisi info X */

/****************** Manajemen Memori ******************/
address AlokasiG (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

address2 AlokasiCon (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next2(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiG (address *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

void DealokasiCon (address2 *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchG (MultiList G, infotype X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

address2 SearchCon (MultiList G, address P, infotype X);
/* mencari address bangunan Y yang terdapat dalam hubungan dengan bangunan X */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
//void InsVFirstG (MultiList *G, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastG (MultiList *G, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertLastG (MultiList *G, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertFirstCon (MultiList *G, address P1, address2 P2);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsVLastCon (MultiList *G, address P, infotype X);

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtCon (MultiList G, infotype X);
/* mengeluarkan jumlah bangunan yang terhubung dengan bangunan X */

#endif
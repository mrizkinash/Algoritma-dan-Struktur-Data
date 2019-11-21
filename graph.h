#ifndef graph_H
#define graph_H

#include "boolean.h"
#include "bangunan.h"
#include "arraydin.h"

#define Nil NULL

typedef int infotype;
typedef struct tElmtlistG *addressG;
typedef struct tElmtlistG2 *addressG2;

typedef struct tElmtlistG {
	infotype info;
	addressG next;
    addressG2 next2;
} ElmtListG;


typedef struct tElmtlistG2 {
	infotype info;
    addressG2 next2;
} ElmtListG2;

typedef struct {
	addressG FirstG;
} MultiList;

/* Definisi list : */
/* List kosong : FirstG(L) = Nil */
/* Setiap elemen dengan addressG P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressGnya Last, maka Next(Last)=Nil */

#define Info(P) (P)->info
#define Next(P) (P)->next
#define Next2(P) (P)->next2
#define FirstG(G) ((G).FirstG)

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyG (MultiList G);
/* Mengirim true jika tidak ada bangunan */
boolean IsEmptyCon (MultiList G, addressG X);
/* Mengirim true jika tidak ada bangunan */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyG (MultiList *G);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
void CreateEmptyCon (MultiList *G, addressG P);
/* membuat list yang terhubung dengan L berisi info X */

/****************** Manajemen Memori ******************/
addressG AlokasiG (infotype X);
/* Mengirimkan addressG hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressG tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

addressG2 AlokasiCon (infotype X);
/* Mengirimkan addressG hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressG tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next2(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiG (addressG *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressG P */

void DealokasiCon (addressG2 *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressG P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressG SearchG (MultiList G, infotype X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan addressG elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

addressG2 SearchCon (MultiList G, addressG P, infotype X);
/* mencari addressG bangunan Y yang terdapat dalam hubungan dengan bangunan X */

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
void InsertLastG (MultiList *G, addressG P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertFirstCon (MultiList *G, addressG P1, addressG2 P2);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressG P sebagai elemen pertama */
void InsVLastCon (MultiList *G, addressG P, infotype X);

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtCon (MultiList G, infotype X);
/* mengeluarkan jumlah bangunan yang terhubung dengan bangunan X */

void CetakBConnected(MultiList G, infotype X, TabInt ArrBang);
// mencetak seluruh bangunan yang terhubung dengan bangunan X

int CariIdxBCon(MultiList G, infotype X, infotype Y);

addressG FindLastG (MultiList G);

#endif
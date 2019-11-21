/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi addressL dengan pointer */
/* infotype adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"
#include "arraydin.h"

#define Nil NULL

typedef int infotype;
typedef struct tElmtlistL *addressL;

typedef struct tElmtlistL {
	infotype info;
	addressL next;
} ElmtListL;

typedef struct {
	addressL FirstL;
} List;

/* Definisi list : */
/* List kosong : FirstL(L) = Nil */
/* Setiap elemen dengan addressL P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressLnya Last, maka Next(Last)=Nil */

#define Info(P) (P)->info
#define Next(P) (P)->next
#define FirstL(L) ((L).FirstL)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLB (List L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLB (List *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addressL AlokasiLB (infotype X);
/* Mengirimkan addressL hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressL tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiLB (addressL *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressL P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressL SearchLB (List L, infotype X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan addressL elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstLB (List *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastLB (List *L, infotype X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstLB (List *L, infotype *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLastLB (List *L, infotype *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLB (List *L, addressL P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressL P sebagai elemen pertama */
void InsertAfterLB (List *L, addressL P, addressL Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastLB (List *L, addressL P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstLB (List *L, addressL *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelPLB (List *L, infotype X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressL P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLastLB (List *L, addressL *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfterLB (List *L, addressL *Pdel, addressL Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfoLB (List L, TabInt ArrBang);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
int NbElmtLB (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
int CariIdxB(List L, int n);
// mengeluarkan index ArrBang ke n yang dimiliki suatu player

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
//infotype Max (List L);
/* Mengirimkan nilai Info(P) yang maksimum */

/****************** PROSES TERHADAP LIST ******************/
//void Konkat1 (List *L1, List *L2, List *L3);
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */

#endif
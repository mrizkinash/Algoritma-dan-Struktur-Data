/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

#ifndef ARRAYDIN_H
#define ARRAYDIN_H

#include "boolean.h"
#include "bangunan.h"

/*  Kamus Umum */
#define IdxMin 1
/* Indeks minimum array */
#define IdxUndef -999
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType; /* type indeks */
typedef Bangunan ElType;  /* type elemen tabel */
typedef struct
{
  ElType *TI; /* memori tempat penyimpan elemen (container) */
  int Neff;   /* >=0, banyaknya elemen efektif */
  int MaxEl;  /* ukuran elemen */
} TabInt;
/* Indeks yang digunakan [IdxMin..MaxEl] */
/* Jika T adalah TabInt, cara deklarasi dan akses: */
/* Deklarasi : T : TabInt */
/* Maka cara akses:
   T.Neff  untuk mengetahui banyaknya elemen
   T.TI    untuk mengakses seluruh nilai elemen tabel
   T.TI[i] untuk mengakses elemen ke-i */
/* Definisi :
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.TI[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */

/* ********** SELEKTOR ********** */
#define Neff(T) (T).Neff
#define TI(T) (T).TI
#define ElmtArr(T, i) (T).TI[(i)]
#define MaxEl(T) (T).MaxEl

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyAB(TabInt *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */

void DealokasiAB(TabInt *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtAB(TabInt T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */

/* *** Daya tampung container *** */
int MaxElementAB(TabInt T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */

/* *** Selektor INDEKS *** */
IdxType GetFirstIdxAB(TabInt T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

IdxType GetLastIdxAB(TabInt T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidAB(TabInt T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

boolean IsIdxEffAB(TabInt T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyAB(TabInt T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

/* *** Test tabel penuh *** */
boolean IsFullAB(TabInt T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
// void BacaIsi(TabInt *T);
// /* I.S. T sembarang dan sudah dialokasikan sebelumnya */
// /* F.S. Tabel T terdefinisi */
// /* Proses : membaca banyaknya elemen T dan mengisi nilainya */
// /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
// /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
// /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
// /* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
//       IdxMin satu per satu diakhiri enter */
// /*    Jika N = 0; hanya terbentuk T kosong */

void TulisIsiAB(TabInt T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
// TabInt PlusMinusTab(TabInt T1, TabInt T2, boolean plus);
// /* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
// /* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
// /* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
// boolean IsEQ(TabInt T1, TabInt T2);
// /* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */
/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
// IdxType Search1(TabInt T, ElType X);
// /* Search apakah ada elemen tabel T yang bernilai X */
// /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
// /* Jika tidak ada, mengirimkan IdxUndef */
// /* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
// /* Skema Searching yang digunakan bebas */

/* ********** NILAI EKSTREM ********** */
// void MaxMin(TabInt T, ElType *Max, ElType *Min);
// /* I.S. Tabel T tidak kosong */
// /* F.S. Max berisi nilai maksimum T;
//         Min berisi nilai minimum T */

/* ********** OPERASI LAIN ********** */
void CopyArr(TabInt Tin, TabInt *Tout);
// /* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
// /* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
// /* Proses : Menyalin isi Tin ke Tout */

// ElType SumTab(TabInt T);
// /* Menghasilkan hasil penjumlahan semua elemen T */
// /* Jika T kosong menghasilkan 0 */

// int CountX(TabInt T, ElType X);
// /* Menghasilkan berapa banyak kemunculan X di T */
// /* Jika T kosong menghasilkan 0 */

// boolean IsAllGenap(TabInt T);
// /* Menghasilkan true jika semua elemen T genap. T boleh kosong */

// /* ********** SORTING ********** */
// void Sort(TabInt *T, boolean asc);
// /* I.S. T boleh kosong */
// /* F.S. Jika asc = true, T terurut membesar */
// /*      Jika asc = false, T terurut mengecil */
// /* Proses : Mengurutkan T dengan salah satu algoritma sorting,
//    algoritma bebas */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddBangunan(TabInt *T, ElType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

void DelLastElAB(TabInt *T, ElType *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */


/* TAMBAHAN PUNGSI BANGUNAN */
int JmlBOwnedX(TabInt T, int X);
/* menghitung jumlah bangunan yang dimiliki X */

TabInt BOwnedX(TabInt T, int X);
// mengeluarkan array bangunan yang dimiliki oleh X

#endif

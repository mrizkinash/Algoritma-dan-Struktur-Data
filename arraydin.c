#include <stdio.h>
#include <stdlib.h>
#include "arraydin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyAB(TabInt *T, int maxel){
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */

    TI(*T) = (ElType *)malloc((maxel + 1) * sizeof(ElType));
    Neff(*T) = maxel;
    MaxEl(*T) = 30;
}

void DealokasiAB(TabInt *T){
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */

    free(TI(*T));
    MaxEl(*T) = 0;
    Neff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtAB(TabInt T){
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */

    return Neff(T);
}

/* *** Daya tampung container *** */
int MaxElementAB(TabInt T){
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */

    return MaxEl(T);
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdxAB(TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */

    return IdxMin;
}

IdxType GetLastIdxAB(TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

    return Neff(T);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidAB(TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/

    return ((i >= IdxMin) && (i <= MaxEl(T)));
}

boolean IsIdxEffAB(TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

    return ((i >= GetFirstIdxAB(T)) && (i <= GetLastIdxAB(T)));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyAB(TabInt T){
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

    return (Neff(T) == 0);
}

/* *** Test tabel penuh *** */
boolean IsFullAB(TabInt T){
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

    return (Neff(T) == MaxEl(T));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */

void TulisIsiAB(TabInt T){
// Proses : mencetak isi bangunan yang terdapat pada array T
// format 1. <Type Bangunan> (absis,ordinat) <jml army> <level bangunan>
    IdxType i;
    if(Neff(T) > 0){
        for (i = 1; i <=Neff(T); i++){
            printf("%c ",Type(ElmtArr(T,i)));
            printf("(%d,%d) ",AbsisBangunan(ElmtArr(T,i)),OrdinatBangunan(ElmtArr(T,i)));
            printf("%d ",Army(ElmtArr(T,i)));
            printf("lv. %d\n",Level(ElmtArr(T,i)));
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddBangunan(TabInt *T, ElType X){
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

    if (!IsFullAB(*T)){
        ElmtArr(*T, (GetLastIdxAB(*T) + 1)) = X;
        Neff(*T) += 1;
    }
}

void DelLastElAB(TabInt *T, ElType *X){
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

    *X = ElmtArr(*T, GetLastIdxAB(*T));
    Neff(*T) -= 1;
}

/* TAMBAHAN PUNGSI BANGUNAN */
int JmlBOwnedX(TabInt T, int X){
/* menghitung jumlah bangunan yang dimiliki X */
    int cnt=0;
    for(int i=1; i<=Neff(T); i++){
        if(Owner(ElmtArr(T,i))==X) cnt+=1;
    }
    return cnt;
}

TabInt BOwnedX(TabInt T, int X){
    TabInt *owned;
    for(int i=1; i<=Neff(T); i++){
        if(Owner(ElmtArr(T,i))==X) AddBangunan(owned,ElmtArr(T,i));
    }
    return *owned;
}
// mengeluarkan array bangunan yang dimiliki oleh X
/* ********** OPERASI LAIN ********** */
void CopyArr(TabInt Tin, TabInt *Tout){
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */

    IdxType i;

    MakeEmptyAB(Tout, MaxEl(Tin));
    Neff(*Tout) = Neff(Tin);

    for (i = GetFirstIdxAB(Tin); i <= GetLastIdxAB(Tin); i++){
        ElmtArr(*Tout, i) = ElmtArr(Tin, i);
    }
}
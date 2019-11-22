#include <stdio.h>
#include <stdlib.h>
#include "arraydin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyAB(TabInt *T, int maxel){
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */

    TI(*T) = (ElType *)malloc((maxel + 1) * sizeof(ElType));
    Neff(*T) = 0;
    MaxEl(*T) = maxel;
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

    return ((i >= GetFirstIdx(T)) && (i <= GetLastIdx(T)));
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
/* *** Mendefinisikan isi tabel dari pembacaan *** *

void TulisIsiAB(TabInt T){
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

    IdxType i;
    if (Neff(T) > 0){
        for (i = 1; i <=Neff(T); i++){
            printf("%c ",Type(Elmt(T,i)));
            printf("(%d,%d) ",AbsisBangunan(Elmt(T,i)),OrdinatBangunan(Elmt(T,i)))
            printf("%d ",Army(Elmt(T,i)));
            printf("lv. %d\n",Level(Elmt(T,i)));
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddBangunan(TabInt *T, ElType X){
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

    if (!IsFull(*T)){
        Elmt(*T, (GetLastIdx(*T) + 1)) = X;
        Neff(*T) += 1;
    }
}

void DelLastElAB(TabInt *T, ElType *X){
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

    *X = Elmt(*T, GetLastIdx(*T));
    Neff(*T) -= 1;
}

/* TAMBAHAN PUNGSI BANGUNAN */
int JmlBOwnedX(TabInt T, int X){
/* menghitung jumlah bangunan yang dimiliki X */
    int cnt=0;
    for(int i=1; i<=Neff(T); i++){
        if(Owner(Elmt(T,i))==X) cnt+=1;
    }
    return cnt;
}

TabInt BOwnedX(TabInt T, int X){
    TabInt *owned;
    for(int i=1; i<=Neff(T); i++){
        if(Owner(Elmt(T,i))==X) AddBangunan(&owned,Elmt(T,i));
    }
    return *owned;
}
// mengeluarkan array bangunan yang dimiliki oleh X

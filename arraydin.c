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
/* *** Mendefinisikan isi tabel dari pembacaan *** */
// void BacaIsi(TabInt *T){
// /* I.S. T sembarang dan sudah dialokasikan sebelumnya */
// /* F.S. Tabel T terdefinisi */
// /* Proses : membaca banyaknya elemen T dan mengisi nilainya */
// /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
// /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
// /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
// /* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
//       IdxMin satu per satu diakhiri enter */
// /*    Jika N = 0; hanya terbentuk T kosong */

//     int N;
//     IdxType i;
//     ElType temp;

//     scanf("%d", &N);
//     while ((N < 0) || (N > MaxEl(*T))){
//         scanf("%d", &N);
//     }

//     if (N > 0){
//         for (i = IdxMin; i <= N; i++){
//             scanf("%d", &temp);
//             Elmt(*T, i) = temp;
//         }
//         Neff(*T) = N;
//     }
// }

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

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
// TabInt PlusMinusTab(TabInt T1, TabInt T2, boolean plus){
// /* Prekondisi : T1 dan T2 memiliki Neff sama dan tidak kosong */
// /* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
// /* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */

//     TabInt TOut;
//     IdxType i;

//     MakeEmpty(&TOut, Neff(T1));
//     Neff(TOut) = Neff(T1);

//     if (plus){
//         for (i = IdxMin; i <= Neff(TOut); i++){
//             Elmt(TOut, i) = Elmt(T1, i) + Elmt(T2, i);
//         }
//     }
//     else{
//         for (i = IdxMin; i <= Neff(TOut); i++){
//             Elmt(TOut, i) = Elmt(T1, i) - Elmt(T2, i);
//         }
//     }

//     return TOut;
// }

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
// boolean IsEQ(TabInt T1, TabInt T2){
// /* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */

//     IdxType i;
//     boolean check;

//     i = IdxMin;
//     check = true;
//     if (Neff(T1) == Neff(T2)){
//         while ((check) && (i <= Neff(T1))){
//             if (Elmt(T1, i) != Elmt(T2, i)){
//                 check = false;
//             }
//             else{
//                 i++;
//             }
//         }
//     }
//     else{
//         check = false;
//     }

//     return check;
// }

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
// IdxType Search1(TabInt T, ElType X){
// /* Search apakah ada elemen tabel T yang bernilai X */
// /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
// /* Jika tidak ada, mengirimkan IdxUndef */
// /* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
// /* Skema Searching yang digunakan bebas */

//     IdxType i;
//     boolean found;

//     if (IsEmpty(T)){
//         return IdxUndef;
//     }
//     else{
//         i = IdxMin;
//         found = false;
//         while ((!found) && (i <= Neff(T))){
//             if (Elmt(T, i) == X){
//                 found = true;
//             }
//             else{
//                 i++;
//             }
//         }

//         if (found){
//             return i;
//         }
//         else{
//             return IdxUndef;
//         }
//     }
// }

// boolean SearchB(TabInt T, ElType X){
// /* Search apakah ada elemen tabel T yang bernilai X */
// /* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
// /* Skema searching yang digunakan bebas */

//     IdxType i;
//     boolean found;

//     i = IdxMin;
//     found = false;

//     if (!IsEmpty(T)){
//         while ((!found) && (i <= Neff(T))){
//             if (Elmt(T, i) == X){
//                 found = true;
//             }
//             else{
//                 i++;
//             }
//         }
//     }

//     return found;
// }

/* ********** NILAI EKSTREM ********** */
// void MaxMin(TabInt T, ElType *Max, ElType *Min){
// /* I.S. Tabel T tidak kosong */
// /* F.S. Max berisi nilai maksimum T;
//         Min berisi nilai minimum T */

//     IdxType i;

//     *Max = Elmt(T, GetFirstIdx(T));
//     *Min = Elmt(T, GetFirstIdx(T));

//     if (Neff(T) > 1){
//         for (i = (GetFirstIdx(T) + 1); i <= GetLastIdx(T); i++){
//             if (Elmt(T, i) > *Max){
//                 *Max = Elmt(T, i);
//             }
//             if (Elmt(T, i) < *Min){
//                 *Min = Elmt(T, i);
//             }
//         }
//     }
// }

/* ********** OPERASI LAIN ********** */
// void CopyTab(TabInt Tin, TabInt *Tout){
// /* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
// /* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
// /* Proses : Menyalin isi Tin ke Tout */

//     IdxType i;

//     MakeEmpty(Tout, MaxEl(Tin));
//     Neff(*Tout) = Neff(Tin);

//     for (i = GetFirstIdx(Tin); i <= GetLastIdx(Tin); i++){
//         Elmt(*Tout, i) = Elmt(Tin, i);
//     }
// }

// ElType SumTab(TabInt T){
// /* Menghasilkan hasil penjumlahan semua elemen T */
// /* Jika T kosong menghasilkan 0 */

//     ElType total;
//     IdxType i;

//     total = 0;

//     if (!IsEmpty(T)){
//         for (i = GetFirstIdx(T); i <= GetLastIdx(T); i++){
//             total += Elmt(T, i);
//         }
//     }

//     return total;
// }

// int CountX(TabInt T, ElType X){
// /* Menghasilkan berapa banyak kemunculan X di T */
// /* Jika T kosong menghasilkan 0 */

//     IdxType i;
//     int count;

//     count = 0;
//     if(!IsEmpty(T)){
//         for (i = GetFirstIdx(T); i <= GetLastIdx(T); i++){
//             if (Elmt(T, i) == X){
//                 count += 1;
//             }
//         }
//     }

//     return count;
// }

// boolean IsAllGenap(TabInt T){
// /* Menghasilkan true jika semua elemen T genap. T boleh kosong */

//     IdxType i;
//     boolean genap;

//     i = GetFirstIdx(T);
//     genap = true;
//     if (IsEmpty(T)){
//         return false;
//     }
//     else{
//         while ((genap) && (i <= GetLastIdx(T))){
//             if (Elmt(T,i) % 2 != 0){
//                 genap = false;
//             }
//             else{
//                 i++;
//             }
//         }

//         return genap;
//     }
// }

// /* ********** SORTING ********** */
// void Sort(TabInt *T, boolean asc){
// /* I.S. T boleh kosong */
// /* F.S. Jika asc = true, T terurut membesar */
// /*      Jika asc = false, T terurut mengecil */
// /* Proses : Mengurutkan T dengan salah satu algoritma sorting,
//    algoritma bebas */

//     IdxType i, j;
//     ElType temp;

//     if (asc){
//         for(i = (GetFirstIdx(*T) + 1); i <= (GetLastIdx(*T)); i++){
//             j = i;

//             while(j > GetFirstIdx(*T) && Elmt(*T, j) < Elmt(*T, (j - 1))){
//                 temp = Elmt(*T, j);
//                 Elmt(*T, j) = Elmt(*T, (j - 1));
//                 Elmt(*T, (j - 1)) = temp;
//                  j--;
//             }
//         }
//     }

//     else{
//         for(i = (GetFirstIdx(*T) + 1); i <= (GetLastIdx(*T)); i++){
//             j = i;

//             while(j > GetFirstIdx(*T) && Elmt(*T, j) > Elmt(*T, (j - 1))){
//                 temp = Elmt(*T, j);
//                 Elmt(*T, j) = Elmt(*T, (j - 1));
//                 Elmt(*T, (j - 1)) = temp;
//                  j--;
//             }
//         }
//     }
// }

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

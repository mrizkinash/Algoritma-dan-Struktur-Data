/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#include "matriks.h"
#include "boolean.h"
#include "stdio.h"
#include "stdlib.h"

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
	NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
 }
/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValidMatriks (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return((i>=1)&&(i<=100)&&(j<=100)&&(j>=1));
}
/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrsMatriks (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKolMaktriks (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrsMatriks (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return NBrsEff(M);
}
indeks GetLastIdxKolMatriks (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return NKolEff(M);
}

boolean IsIdxEffMatriksMatriks (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return ((i >= 1) && (i <= NBrsEff(M)) && (j <= NKolEff(M)) && (j >= 1));
}
ElTypeMat GetElmtDiagonalMatriks (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return(ElmtMat(M,i,i));
}
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    int i,j;

    MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),MHsl);
    for (i=1;i<=NBrsEff(MIn);i++){
        for(j=1;j<=NKolEff(MIn);j++){
            ElmtMat(*MHsl,i,j) = ElmtMat(MIn,i,j);
        }
    }
}
/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
{
    int i, j, temp;
    char CC; 

    MakeMATRIKS(NB, NK, M);
    for (i = 1; i <= NB; i++)
    {
        for (j = 1; j <= NK; j++)
        {
            scanf("%d", &MOwn(ElmtMat(*M, i, j)));
            scanf(" %c", &MType(ElmtMat(*M, i, j)));
        }
    }
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    int i, j;

    for (i = 1; i <= NBrsEff(M); i++)
    {
        for (j = 1; j <= NKolEff(M); j++)
        {

            printf("%c", MType(ElmtMat(M, i, j)));

            if (j != NKolEff(M))
            {
                printf(" ");
            } else {
                
                printf("\n");
                
            }
        }
    }
}

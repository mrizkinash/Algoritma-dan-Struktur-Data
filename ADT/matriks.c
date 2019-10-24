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
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return((i>=1)&&(i<=100)&&(j<=100)&&(j>=1));
}
/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return NBrsEff(M);
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return NKolEff(M);
}

boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return ((i >= 1) && (i <= NBrsEff(M)) && (j <= NKolEff(M)) && (j >= 1));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return(Elmt(M,i,i));
}
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    int i,j;

    MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),MHsl);
    for (i=1;i<=NBrsEff(MIn);i++){
        for(j=1;j<=NKolEff(MIn);j++){
            Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
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
    int i, j;

    MakeMATRIKS(NB, NK, M);
    for (i = 1; i <= NB; i++)
    {
        for (j = 1; j <= NK; j++)
        {
            scanf("%d", &Elmt(*M, i, j));
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

            printf("%d", M.Mem[i][j]);

            if (j != NKolEff(M))
            {
                printf(" ");
            } else {
                if (i != NBrsEff(M))
                {
                    printf("\n");
                }
            }
        }
    }
}
/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
{
    int i, j;
    MATRIKS M3;

    MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &M3);
    for (i = 1; i <= NBrsEff(M1); i++)
    {
        for (j = 1; j <= NKolEff(M1); j++)
        {
            Elmt(M3, i, j) = Elmt(M1, i, j) + Elmt(M2,i,j);
        }
    }
    return M3;
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
    int i, j;
    MATRIKS M3;

    MakeMATRIKS(NBrsEff(M1), NKolEff(M1), &M3);
    for (i = 1; i <= NBrsEff(M1); i++)
    {
        for (j = 1; j <= NKolEff(M1); j++)
        {
            Elmt(M3, i, j) = Elmt(M1, i, j) - Elmt(M2, i, j);
        }
    }
    return M3;
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
   int i,j,k;
    MATRIKS Mnew;
    
    MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&Mnew);
    
    for (i=BrsMin; i<=NBrsEff(M1); i++){
        for (j=KolMin; j<=NKolEff(M2); j++){
            Elmt(Mnew,i,j) = 0;
            for (k=1; k<=NKolEff(M1); k++){
                Elmt(Mnew,i,j)+=(Elmt(M1,i,k)*Elmt(M2,k,j));
            }
        }
    }
    return Mnew;
}
MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
    // int i, j;
    // MATRIKS M1;

    // for (i = 1; i <= NBrsEff(M); i++)
    // {
    //     for (j = 1; j <= NKolEff(M); j++)
    //     {
    //         Elmt(M, i, j) *= X;
    //     }
    // }
    // return M;
    indeks i,j;
    MATRIKS Ml;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&Ml);
    for (i = GetFirstIdxBrs(M);i <= GetLastIdxBrs(M);i++) {
        for (j = GetFirstIdxKol(M); j <= GetLastIdxKol(M); j++) {
            Elmt(Ml,i,j) = (Elmt(M,i,j) * X);
        }
    }
    return Ml;
}
void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
    *M = KaliKons(*M,K);
}
/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2)
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    int i,j;
    boolean b;
     
     i=1;
     j=1;
    if ((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2))){
        b =true;
        while (b && (i<= GetLastIdxBrs(M1)) && (GetLastIdxKol(M1))){
            if (Elmt(M1,i,j) != Elmt(M2,i,j))
            {
                /* code */
                b= false;
            }
            i++;
            j++;
        }
    } else{
        b = false;
    }

    return b;
 
}
boolean NEQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    int i, j;
    boolean b;

    i = 1;
    j = 1;
    if ((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2)))
    {
        b = false;
        while( (!b) && (i <= GetLastIdxBrs(M1)) && (GetLastIdxKol(M1)))
            {
                if (Elmt(M1, i, j) != Elmt(M2, i, j))
                {
                    /* code */
                    b = true;
                }
                i++;
                j++;
            }
    }
    else
    {
        b = true;
    }

    return b;

}
boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
    return ((NBrsEff(M1) == NBrsEff(M2)) && ( NKolEff(M1) == NKolEff(M2)));
}
/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
 return (NBrsEff(M) * NKolEff(M));
}
/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    return (NBrsEff(M) == NKolEff(M));
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M)
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    // int i,j;
    // boolean simetri;
    
    // i=1;
    // j=1;
    // simetri = true;

    // if(IsBujurSangkar(M)){
    //     while(simetri && (i <= GetLastIdxBrs(M) && (GetLastIdxKol(M)))){
    //         if( Elmt(M,i,j) != (Elmt(M,j,i))){
    //             simetri =false;
    //         }
    //         i++;
    //         j++;
    //     }
    // } else{
    //     simetri =false;
    // }

    // return simetri;
    int i, j;
    boolean b;

    if (IsBujurSangkar(M))
    {
        b = true;
        for (i = 1; i <= NBrsEff(M); i++)
        {
            for (j = 1; j <= NKolEff(M); j++)
            {
                if (Elmt(M, i, j) != Elmt(M, j, i))
                {
                    b = false;
                }
            }
        }
    }
    else
    {
        b = false;
    }
    return b;
}
boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    int i, j;
    boolean satuan;

    satuan = true;
    if (IsBujurSangkar(M))
    {
        i = GetFirstIdxBrs(M);
        while ((i <= GetLastIdxBrs(M)) && (satuan))
        {
            j = GetFirstIdxKol(M);
            while ((j <= GetLastIdxKol(M) && (satuan)))
            {
                if (i == j)
                {
                    if (Elmt(M, i, j) != 1)
                    {
                        satuan = false;
                    }
                }
                else
                {
                    if (Elmt(M, i, j) != 0)
                    {
                        satuan = false;
                    }
                }
                j = j + 1;
            }
            i = i + 1;
        }
    }
    else
    {
        satuan = false;
    }
    return satuan;
}
boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi:
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    float p, k;
    int i, j;

    k = 0;
    for (i = 1; i <= NBrsEff(M); i++)
    {
        for (j = 1; j <= NKolEff(M); j++)
        {
            if (Elmt(M, i, j) != 0)
            {
                k += 1;
            }
        }
    }

    p = k / (NBrsEff(M) * NKolEff(M));
    return (p <= 0.05);
}
MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    return(KaliKons(M,(-1)));
}
float Determinan (MATRIKS M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
    MATRIKS M1;
    indeks i, j, k, l, m, n;
    float det;

    //Algoritma
    det = 0;
    if (NBrsEff(M) == 2)
    {
        return ((Elmt(M, GetFirstIdxBrs(M), GetFirstIdxKol(M)) * Elmt(M, GetLastIdxBrs(M), GetLastIdxKol(M))) - (Elmt(M, GetFirstIdxBrs(M), GetLastIdxKol(M)) * Elmt(M, GetLastIdxBrs(M), GetFirstIdxKol(M))));
    }
    else
    {
        j = GetLastIdxKol(M);
        for (i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++)
        {
            MakeMATRIKS((NBrsEff(M) - 1), (NKolEff(M) - 1), &M1);
            for (k = GetFirstIdxBrs(M), m = GetFirstIdxBrs(M1); k < i; k++, m++)
            {
                for (l = GetFirstIdxKol(M), n = GetFirstIdxKol(M1); l < GetLastIdxKol(M); l++, n++)
                {
                    Elmt(M1, m, n) = Elmt(M, k, l);
                }
            }
            for (k = i + 1; k <= GetLastIdxBrs(M); k++, m++)
            {
                for (l = GetFirstIdxKol(M), n = GetFirstIdxKol(M1); l < GetLastIdxKol(M); l++, n++)
                {
                    Elmt(M1, m, n) = Elmt(M, k, l);
                }
            }
            if ((j + i) % 2 == 0)
            {
                det = det + (Elmt(M, i, j) * Determinan(M1));
            }
            else
            {
                det = det + (-1) * Elmt(M, i, j) * Determinan(M1);
            }
        }
        return det;
    }
}
void PInverse1 (MATRIKS * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    int i, j;

    for (i = 1; i <= NBrsEff(*M); i++)
    {
        for (j = 1; j <= NKolEff(*M); j++)
        {
            Elmt(*M, i, j) *= (-1);
        }
    }
}
void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
    MATRIKS T;
    int i, j;

    MakeMATRIKS(NBrsEff(*M), NKolEff(*M), &T);
    for (i = 1; i <= NBrsEff(*M); i++)
    {
        for (j = 1; j <= NKolEff(*M); j++)
        {
            Elmt(T, j, i) = Elmt(*M, i, j);
        }
    }

    for (i = 1; i <= NBrsEff(*M); i++)
    {
        for (j = 1; j <= NKolEff(*M); j++)
        {
            Elmt(*M, i, j) = Elmt(T, i, j);
        }
    }
}

/* Operasi berbasis baris dan per kolom */

float RataBrs (MATRIKS M, indeks i)
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
{
	int sum,j,count;
	sum=0;
	count=0;
	for(j=1; j<=GetLastIdxKol(M);j++){
		sum+=Elmt(M,i,j);
		count++;
	}
	return(sum/count);
	}
float RataKol (MATRIKS M, indeks j)
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
{
	int sum,i,count;
	sum=0;
	count=0;
	for(i=1; i<=GetLastIdxBrs(M);i++){
		sum+=Elmt(M,i,j);
		count++;
	}
	return(sum/count);
	}
void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min)
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
{
	int j, m;
	
	j = GetFirstIdxKol(M);
	*max = Elmt(M,i,j);
	*min = Elmt(M,i,j);
	
	
	for( m=2; m<=GetLastIdxKol(M);m++){
			if(*max < Elmt(M,i,m)){
				*max = Elmt(M,i,m);
			}
			
			if(*min > Elmt(M,i,m)){
				*min = Elmt(M,i,m);
			}
		}
	}
void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min)
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
{
	int i, m;
	
	i = GetFirstIdxBrs(M);
	*max = Elmt(M,i,j);
	*min = Elmt(M,i,j);
	
	
	for( m=2; m<=GetLastIdxBrs(M);m++){
			if(*max < Elmt(M,m,j)){
				*max = Elmt(M,m,j);
			}
			
			if(*min > Elmt(M,m,j)){
				*min = Elmt(M,m,j);
			}
		}
}
int CountXBrs (MATRIKS M, indeks i, ElType X)
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
{
    int j;
	int count=0;
	for(j =1; j<=GetLastIdxKol(M);j++){
		if(Elmt(M,i,j) == X){
			count++;
			}
		}
		return count;
	}
int CountXKol (MATRIKS M, indeks j, ElType X)
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
{
    int i;
	int count=0;
	for(i =1; i<=GetLastIdxBrs(M);i++){
		if(Elmt(M,i,j) == X){
			count++;
			}
		}
		return count;
}

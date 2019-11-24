#include "matriks.h"
#include "mesinkata.h"
#include <stdio.h>

int KarakterToInt (char CC){

    return (int) CC - 48;
}

int KataToInt (Kata CKata){
    int i, retval;

    i = 1;
    retval = 0;
    while (i <= CKata.Length){

        retval = (retval * 10) + KarakterToInt(CKata.TabKata[i]);
        i++;
    }

    return retval;
}

int main(){
	MATRIKS M;
	int NB, NK, i, j;

	printf("Program akan membaca config.txt dan mengonfigurasi matriks dari baris pertama\n");
	STARTKATA();
	NB = KataToInt(CKata);
	printf("Tinggi Matriks = %d\n", NB);
	ADVKATA();
	NK = KataToInt(CKata);
	printf("Lebar Matriks = %d\n", NK);
	
	MakeMATRIKS(NB + 1, NK + 1, &M);
	printf("Mengisi ujung matriks dengan pagar...\n");
	for (i = 0; i <= M.NBrsEff; i++){          // Bikin pager
        for (j = 0; j<= M.NKolEff; j++){

            if ((i % M.NBrsEff == 0) || (j % M.NKolEff == 0)){
                        
                MOwn(ElmtMat(M, i, j)) = 0;
                MType(ElmtMat(M, i, j)) = '*';
            }
            else {

            	MOwn(ElmtMat(M, i, j)) = 0;
                MType(ElmtMat(M, i, j)) = ' ';	
            }
        }
    }
    printf("Matriks yang dihasilkan\n");
    TulisMATRIKS(M);
    printf("\n");
    printf("Set 4 Elemen Matriks yang paling dekat dengan tengah menjadi B\n");
    MType(ElmtMat(M, 5, 7)) = 'B';
    MType(ElmtMat(M, 5, 8)) = 'B';
    MType(ElmtMat(M, 6, 7)) = 'B';
    MType(ElmtMat(M, 6, 8)) = 'B';
    TulisMATRIKS(M);
}
#include "mesinkata.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

boolean IsSameString(Kata CKata, char cmp[]){
	boolean isSame;
	int i;

	isSame = true;
	i = 1;

	while ((i <= CKata.Length) && (isSame)){

		if (CKata.TabKata[i] != cmp[i - 1]){

			isSame = false;
		}
		i++;
	}

	if ((int)(cmp[i - 1]) != 0){

		isSame = false;
	}

	return isSame;
}

int main(){
	int jumlah, i;
	char test[] = "test";

	printf("Membaca file config...\n");
	STARTKATA();
	printf("Tinggi Matriks = %d\n", KataToInt(CKata));
	ADVKATA();
	printf("Lebar Matriks = %d\n", KataToInt(CKata));
	ADVKATA();

	jumlah = KataToInt(CKata);
	printf("Jumlah bangunan = %d\n", jumlah);
	ADVKATA();
	for (i = 1; i <= jumlah; i++){

		printf("Bangunan ke %d\n", i);
		printf("Tipe Bangunan = %c\n", CKata.TabKata[1]);
		ADVKATA();
		printf("Posisi bangunan = (%d, ", KataToInt(CKata));
		ADVKATA();
		printf("%d)\n", KataToInt(CKata));
		ADVKATA();
		printf("\n");
	}
	printf("Membaca keterhubungan bangunan...\n");
	for (i = 1; i <= jumlah * jumlah; i++){

		if (i % jumlah == 0){

			printf("%c\n", CKata.TabKata[1]);
		}
		else {

			printf("%c ", CKata.TabKata[1]);
		}

		ADVKATA();
	}

	printf("Menerima Command User\n");
	printf("Masukkan Command : \n" );
	STARTKATACMD();
	printf("Command yang dimasukkan = ");
	for (i = 1; i <= CKata.Length; i++){

		printf("%c", CKata.TabKata[i]);
	}

	printf("\n");
	printf("Command setelah di lowercase = ");

	for (i = 1; i <= CKata.Length; i++){

		CKata.TabKata[i] = tolower(CKata.TabKata[i]);
		printf("%c", CKata.TabKata[i]);
	}
	printf("\n");

	printf("Apakah command yang dimasukkan attack?\n");
	if (IsSameString(CKata, "attack")){

		printf("yes\n");
	}
	else{

		printf("no\n");
	}

	return 0;
}
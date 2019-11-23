#include "saveload.h"

#include <stdlib.h>

static FILE *save;

/*void IntToCKata(int X){
	int n, length, i, temp;

	n = 10;
	length = 1;
	while (X / n > 0){

		length++;
		n *= 10;;
	}
	n /= 10;
	CKata.Length = length;

	for (i = 1; i <= length; i++){


		CKata.TabKata[i] = (char)((X / n) + 48);
		X -= (X / n) * n;
		n /= 10;
	}
}*/


void SAVEGAME(state S){
	int i;
	adrG P;
	address Q;

	printf("Saving...\n");
	// Mempersiapkan save file untuk ditulis
	save = fopen("savedata.txt", "w");

	if (save == NULL){

		printf("Unable to save file data.\n");
		exit(EXIT_FAILURE);
	}

	// Menuliskan queue skill Player 1 ke file
	if (!IsEmptyQueue(S.P1.skill)){

		for (i = 1; i <= NBElmtQueue(S.P1.skill); i++){

			fprintf(save, "%d ", S.P1.skill.T[i]);
		}
	}

	// Menuliskan apakah ini turn Player 1 atau tidak, apakah player 1 punya extra turn atau tidak, dan apakah player 1 memiliki shieldturn atau tidak
	fprintf(save, "%d %d %d\n", S.P1.turn, S.P1.et, S.P1.shieldturn);

	// List Bangunan milik player diambil dari penulisan ArrayBang

	// Menuliskan queue skill Player 2 ke file
	if (!IsEmptyQueue(S.P2.skill)){

		for (i = 1; i <= NBElmtQueue(S.P2.skill); i++){

			fprintf(save, "%d ", S.P2.skill.T[i]);
		}
	}

	// Menuliskan apakah ini turn Player 2 atau tidak, apakah player 2 punya extra turn atau tidak, dan apakah player 2 memiliki shieldturn atau tidak
	fprintf(save, "%d %d %d\n", S.P2.turn, S.P2.et, S.P2.shieldturn);

	// Menuliskan jumlah bangunan yang ada
	fprintf(save, "%d\n", NbElmtAB(S.ArrBang));

	for (i = 1; i <= NbElmtAB(S.ArrBang); i++){

		// Menuliskan kepemilikan, jumlah pasukan, level, tipe, dan posisi bangunan
		fprintf(save, "%d %d %d %c %d %d\n", Owner(ElmtArr(S.ArrBang, i)), Army((ElmtArr(S.ArrBang, i))), Level((ElmtArr(S.ArrBang, i))), Type((ElmtArr(S.ArrBang, i))), AbsisBangunan((ElmtArr(S.ArrBang, i))), OrdinatBangunan((ElmtArr(S.ArrBang, i))));			
	}

	P = FirstG(S.G);
	while (P != Nil){

		fprintf(save, "%d ", Info(P));
		Q = list(P);
		while (Q != Nil){

			fprintf(save, "%d ", Info(Q));
			Q = Next(Q);
		}
		
		fprintf(save, "\n");
		P = Nextg(P); 
	}
	fprintf(save, ".");
	fclose(save);
    printf("Game saved successfully.\n");
}
#include "saveload.h"

#include <stdlib.h>

static FILE *save;

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

void ReadMatriksSize(MATRIKS *M){
    int tinggi, lebar, i, j;

    tinggi = KataToInt(CKata);
    ADVKATA();
    lebar = KataToInt(CKata);
    ADVKATA();

    MakeMATRIKS(tinggi + 1, lebar + 1, M);  // Membuat matriks (+ 1 karna pagar Map ujung kanan dan bawah, pagar kiri menggunakan indeks 0 yang awalnya tidak dipakai)

    for (i = 0; i <= (*M).NBrsEff; i++){          // Bikin pager
        for (j = 0; j<= (*M).NKolEff; j++){

            if ((i == 0) || (i == (*M).NBrsEff) || (j == 0) || (j == (*M).NKolEff)){
                        
                MOwn(ElmtMat(*M, i, j)) = 0;
                MType(ElmtMat(*M, i, j)) = '*';
            }
            else {

                MOwn(ElmtMat(*M, i, j)) = 0;
                MType(ElmtMat(*M, i, j)) = ' ';  
            }
        }
    }    
}

void ReadBangunan(state *S/*TabInt *ArrBang, List *L1, List *L2, MATRIKS *M*/){
    Bangunan B;
    int size, x, i, j;
    char type;

    CreateEmptyLB(&(S->P1.listbangunan));
    CreateEmptyLB(&(S->P2.listbangunan));
    size = KataToInt(CKata);
    ADVKATA();
    MakeEmptyAB(&(S->ArrBang),size); // bikin array bangunan
    x = 1; // idx array bangunan
            
    while (x <= size){
        // Bikin bangunan disini
        type = CKata.TabKata[1];
        ADVKATA();
        i = KataToInt(CKata);
        ADVKATA();
        j = KataToInt(CKata);

        CreateBangunan(&B,type,i,j); // create bangunan ke x
        ElmtArr(S->ArrBang,x) = B; // masukin bangunan yg baru di create ke arrbang
        S->ArrBang.TI[x].P.X = i;
        S->ArrBang.TI[x].P.Y = j;
        if(x==1){
            S->ArrBang.TI[x].owner = x;
            InsVLastLB(&(S->P1.listbangunan), 1);   // bangunan 1 milik pemain 1
            MOwn(ElmtMat(S->M, i, j)) = 1; // Kepemilikan bangunan di matriks diset jadi 1 (player 1)
        }
        else if(x==2){
            S->ArrBang.TI[x].owner = x;
            InsVLastLB(&(S->P2.listbangunan), 2); // bangunan 2 milik pemain 2
            MOwn(ElmtMat(S->M, i, j)) = 2; // Kepemilikan bangunan di matriks diset jadi 2 (player 2)
        }
        else {
            S->ArrBang.TI[x].owner = 0;
            MOwn(ElmtMat(S->M, i, j)) = 0; // Kepemilikan bangunan di matriks diset jadi 0 (bukan punya siapa siapa)
        }

        MType(ElmtMat(S->M, i, j)) = type;

        ADVKATA();
        x+=1;
    }
}

void ReadGraph(Graph *G, int size){
    CreateEmptyG(G);
    for(int i=1; i<=size; i++){
        for(int j=1; j<=size; j++){
            if(CKata.TabKata[1]=='1') AddRel(G,i,j);
            ADVKATA();
        }
    }
}

void LoadPlayer(Player *P){
	int i, length;

	InitPlayer(P);
	length = KataToInt(CKata);
	ADVKATA();
	for (i = 1; i <= length; i++){

		AddQueue(&(P->skill), KataToInt(CKata));
		ADVKATA();
	}
	P->turn = KataToInt(CKata);
	ADVKATA();
	P->et = KataToInt(CKata);
	ADVKATA();
	P->shieldturn = KataToInt(CKata);
	ADVKATA();

}

void LoadBangunan(state *S){
    Bangunan B;
    int size, x, i, j, milik, army, level;
    char type;

    CreateEmptyLB(&(S->P1.listbangunan));
    CreateEmptyLB(&(S->P2.listbangunan));
    size = KataToInt(CKata);
    ADVKATA();
    MakeEmptyAB(&(S->ArrBang),size); // bikin array bangunan
    x = 1; // idx array bangunan
            
    while (x <= size){
        // Bikin bangunan disini
        milik = KataToInt(CKata);
        ADVKATA();
        army = KataToInt(CKata);
        ADVKATA();
        level = KataToInt(CKata);
        ADVKATA();
        type = CKata.TabKata[1];
        ADVKATA();
        i = KataToInt(CKata);
        ADVKATA();
        j = KataToInt(CKata);

        CreateBangunan(&B,type,i,j); // create bangunan ke x
        Army(B) = army;
        Level(B) = level;
        ElmtArr(S->ArrBang,x) = B; // masukin bangunan yg baru di create ke arrbang
        S->ArrBang.TI[x].P.X = i;
        S->ArrBang.TI[x].P.Y = j;
        if(milik==1){
            S->ArrBang.TI[x].owner = x;
            InsVLastLB(&(S->P1.listbangunan), 1);   // bangunan 1 milik pemain 1
            MOwn(ElmtMat(S->M, i, j)) = 1; // Kepemilikan bangunan di matriks diset jadi 1 (player 1)
        }
        else if(milik==2){
            S->ArrBang.TI[x].owner = x;
            InsVLastLB(&(S->P2.listbangunan), 2); // bangunan 2 milik pemain 2
            MOwn(ElmtMat(S->M, i, j)) = 2; // Kepemilikan bangunan di matriks diset jadi 2 (player 2)
        }
        else {
            S->ArrBang.TI[x].owner = 0;
            MOwn(ElmtMat(S->M, i, j)) = 0; // Kepemilikan bangunan di matriks diset jadi 0 (bukan punya siapa siapa)
        }

        MType(ElmtMat(S->M, i, j)) = type;

        ADVKATA();
        x+=1;
    }
}

void SAVEGAME(state S){
	int i, size;
	adrG P;
	address Q;

	printf("Saving...\n");
	// Mempersiapkan save file untuk ditulis
	save = fopen("savedata.txt", "w");

	if (save == NULL){

		printf("Unable to save file data.\n");
		exit(EXIT_FAILURE);
	}

	// Menuliskan tinggi dan lebar matriks
	fprintf(save, "%d %d\n", GetLastIdxBrsMatriks(S.M) - 1, GetLastIdxKolMatriks(S.M) - 1);

	// Menuliskan jumlah skill dan isi queue skill Player 1 ke file
	fprintf(save, "%d ", NBElmtQueue(S.P1.skill));
	if (!IsEmptyQueue(S.P1.skill)){

		for (i = 1; i <= NBElmtQueue(S.P1.skill); i++){

			fprintf(save, "%d ", S.P1.skill.T[i]);
		}
	}
	fprintf(save, "\n");

	// Menuliskan apakah ini turn Player 1 atau tidak, apakah player 1 punya extra turn atau tidak, dan apakah player 1 memiliki shieldturn atau tidak
	fprintf(save, "%d %d %d\n", S.P1.turn, S.P1.et, S.P1.shieldturn);

	// List Bangunan milik player diambil dari penulisan ArrayBang

	// Menuliskan jumlah skill dan isi queue skill Player 2 ke file
	fprintf(save, "%d ", NBElmtQueue(S.P2.skill));
	if (!IsEmptyQueue(S.P2.skill)){

		for (i = 1; i <= NBElmtQueue(S.P2.skill); i++){

			fprintf(save, "%d ", S.P2.skill.T[i]);
		}
	}
	fprintf(save, "\n");

	// Menuliskan apakah ini turn Player 2 atau tidak, apakah player 2 punya extra turn atau tidak, dan apakah player 2 memiliki shieldturn atau tidak
	fprintf(save, "%d %d %d\n", S.P2.turn, S.P2.et, S.P2.shieldturn);

	// Menuliskan jumlah bangunan yang ada
	size = NbElmtAB(S.ArrBang);
	fprintf(save, "%d\n", NbElmtAB(S.ArrBang));

	for (i = 1; i <= size; i++){

		// Menuliskan kepemilikan, jumlah pasukan, level, tipe, dan posisi bangunan
		fprintf(save, "%d %d %d %c %d %d\n", Owner(ElmtArr(S.ArrBang, i)), Army((ElmtArr(S.ArrBang, i))), Level((ElmtArr(S.ArrBang, i))), Type((ElmtArr(S.ArrBang, i))), AbsisBangunan((ElmtArr(S.ArrBang, i))), OrdinatBangunan((ElmtArr(S.ArrBang, i))));			
	}

	P = FirstG(S.G);
	while (P != Nil){

		i = 1;
		while (i <= size){

			if (SearchCon(S.G, P, i) == Nil){

				fprintf(save, "0 ");
			}
			else {

				fprintf(save, "1 ");
			}
			i++;
		}
		fprintf(save, "\n");
		P = Nextg(P);
		/*fprintf(save, "%d ", Info(P));
		Q = list(P);
		while (Q != Nil){

			fprintf(save, "%d ", Info(Q));
			Q = Next(Q);
		}
		
		fprintf(save, "\n");
		P = Nextg(P);*/ 
	}
	fprintf(save, ".");
	fclose(save);
    printf("Game saved successfully.\n");
}

void LOADGAME(state *S){

	STARTKATALOAD();
	ReadMatriksSize(&(S->M));
	LoadPlayer(&(S->P1));
	LoadPlayer(&(S->P2));
	LoadBangunan(S);
	ReadGraph(&(S->G), NbElmtAB(S->ArrBang));
}
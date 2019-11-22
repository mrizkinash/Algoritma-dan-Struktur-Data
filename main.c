#include "point.h"
#include "arraydin.h"
#include "matriks.h"
#include "mesinkata.h"
#include "queue.h"
#include "stackt.h"
#include "listlinier.h"
#include "boolean.h"
#include "graph.h"
#include "bangunan.h"

#include <stdio.h>
#include <stdlib.h>
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

void ReadMatriksSize(MATRIKS *M){

    tinggi = KataToInt(CKata);
    ADVKATA();
    lebar = KataToInt(CKata);
    ADVKATA();

    MakeMATRIKS(tinggi + 2, lebar + 2, &M);  // Membuat matriks (+ 2 karna pagar Mapnya)

    for (i = 0; i <= M.NBrsEff; i++){          // Bikin pager
    for (j = 0; j<= M.NKolEff; j++){

        if ((i == 0) || (i == M.NBrsEff) || (j == 0) || (j == M.NKolEff)){
                        
            MOwn(ElmtMat(M, i, j)) = 0;
            MType(ElmtMat(M, i, j)) = '*';
        }
    }    
}

void ReadBangunan(TabInt *ArrBang, List *L1, List *L2, MATRIKS *M){
    Bangunan B;
    int size, x, i, j;
    char type;

    CreateEmptyLB(L1);
    CreateEmptyLB(L2);
    size = KataToInt(CKata);
    ADVKATA();
    MakeEmptyAB(ArrBang,size + 1);
    x = 1; // idx array bangunan
            
    while (x <= size){
        // Bikin bangunan disini
        type = CKata.TabKata[1];
        ADVKATA();
        i = KataToInt(CKata);
        ADVKATA();
        j = KataToInt(CKata);

        CreateBangunan(&B,type,i,j); // create bangunan ke x
        ElmtArr(*ArrBang,x) = B; // masukin bangunan yg baru di create ke arrbang
        if(x==1){

            InsVLastLB(L1,1);   // bangunan 1 milik pemain 1
            MOwn(ElmtMat(*M, i, j)) = 1; // Kepemilikan bangunan di matriks diset jadi 1 (player 1)
        }
        else if(x==2){

            InsVLastLB(L2,2); // bangunan 2 milik pemain 2
            MOwn(ElmtMat(*M, i, j)) = 2; // Kepemilikan bangunan di matriks diset jadi 2 (player 2)
        }
        else {

            MOwn(ElmtMat(*M, i, j)) = 0; // Kepemilikan bangunan di matriks diset jadi 0 (bukan punya siapa siapa)
        }

        MType(ElmtMat(*M, i, j)) = type;

        ADVKATA();
        x+=1;
    }
}

void ReadGraph(Graph *G, int size){
    int i;

    i = 1;
    CreateEmptyG(G);

    while (!EndKata){

        if (i % size == 1){

            InsVLastG(G, (i / size) + 1);
            if (CKata.TabKata[1] == '1'){

                InsVLastCon(G, FindLastG(*G), 1);                
            }            
        }
        else{

            if (CKata.TabKata[1] == '1'){

                if (i % size == 0){

                    InsVLastCon(G, FindLastG(*G), size)    
                }
                else{

                    InsVLastCon(G, FindLastG(*G), (i % size));
                }
            }
        }

        i++;
        ADVKATA();
    }
}

int main(){
    TabInt ArrBang; //array dinamis yang menyimpan seluruh bangunan
    List L1, L2; // L1( list keterhubungan bangunan yang dimiliki player 1)
                   // L2( list keterhubungan bangunan yang dimiliki player 2)
    MATRIKS M;
    boolean P1Turn, P2Turn, EndGame;
    int i;

    // DEKRALASI A, M, P BANGUNAN
    /*int AC[5],MC[5],AT[5],MT[5],AF[5],MF[5],AV[5],MV[5];        // Indeks dari 0
    boolean PC[5],PT[5],PF[5],PV[5];
    AC[1]=10; AC[2]=15; AC[3]=20; AC[4]=25;
    MC[1]=40; MC[2]=60; MC[3]=80; MC[4]=100;
    AT[1]=5;  AT[2]=10; AT[3]=20; AT[4]=30;
    MT[1]=20; MT[2]=30; MT[3]=40; MT[4]=50;
    AF[1]=10; AF[2]=20; AF[3]=30; AF[4]=40;
    MF[1]=20; MF[2]=40; MF[3]=60; MF[4]=80;
    AV[1]=5;  AV[2]=10; AV[3]=15; AV[4]=20;
    MV[1]=20; MV[2]=30; MV[3]=40; MV[4]=50;
    for(int i=1; i<=4; i++){
        PC[i]=false;
        PT[i]=true;
        PV[i]=false;
        PF[i]=false;
    }
    PF[3]=true; PF[4]=true;*/

    // Untuk sekarang permainan langsung dimulai saat program dimulai
    STARTKATA();         // Baca dari file config
    ReadMatriksSize(&M);
    ReadBangunan(&ArrBang, &L1, &L2, &M);
    ReadGraph(G, NbElmtAB(ArrBang));

    EndGame = false;
    P1Turn = true;
    P2Turn = false;

    while (!EndGame){

        TulisMATRIKS(M);
        if (P1Turn){

            printf("Player 1\n");
            CetakListB(L1, ArrBang);
            printf("Skill Available : ");
            // Bikin fungsi PrintIsiQueue disini
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang
            for (i = 1; i <= CKata.Length; i++){

                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (strcmp(CKata.TabKata, "attack")){


            }
            else if (strcmp(CKata.TabKata, "level_up")){


            }
            else if (strcmp(CKata.TabKata, "skill")){


            }
            else if (strcmp(CKata.TabKata, "undo")){


            }
            else if (strcmp(CKata.TabKata, "end_turn")){


            }
            /*else if (strcmp(CKata.TabKata, "save")){


            }*/
            /*else if (strcmp(CKata.TabKata, "move")){


            }*/
            else if (strcmp(CKata.TabKata, "exit")){


            }

        }
        else if (P2Turn){

            printf("Player 2\n");
            CetakListB(L2, ArrBang);
            printf("Skill Available : ");
            // Bikin fungsi PrintIsiQueue disini
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang   
            for (i = 1; i <= CKata.Length; i++){

                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (strcmp(CKata.TabKata, "attack")){


            }
            else if (strcmp(CKata.TabKata, "level_up")){


            }
            else if (strcmp(CKata.TabKata, "skill")){


            }
            else if (strcmp(CKata.TabKata, "undo")){


            }
            else if (strcmp(CKata.TabKata, "end_turn")){


            }
            /*else if (strcmp(CKata.TabKata, "save")){


            }*/
            /*else if (strcmp(CKata.TabKata, "move")){


            }*/
            else if (strcmp(CKata.TabKata, "exit")){

                
            }
        }
    }
    return 0;
}
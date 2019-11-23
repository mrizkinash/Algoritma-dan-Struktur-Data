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
#include "command.h"
#include "player.h"
#include "state.h"

#include <stdio.h>
#include <stdlib.h>
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

void ReadMatriksSize(MATRIKS *M){
    int tinggi, lebar, i, j;

    tinggi = KataToInt(CKata);
    ADVKATA();
    lebar = KataToInt(CKata);
    ADVKATA();

    MakeMATRIKS(tinggi + 2, lebar + 2, M);  // Membuat matriks (+ 2 karna pagar Mapnya)

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
        if(x==1){

            InsVLastLB(&(S->P1.listbangunan), 1);   // bangunan 1 milik pemain 1
            MOwn(ElmtMat(S->M, i, j)) = 1; // Kepemilikan bangunan di matriks diset jadi 1 (player 1)
        }
        else if(x==2){

            InsVLastLB(&(S->P2.listbangunan), 2); // bangunan 2 milik pemain 2
            MOwn(ElmtMat(S->M, i, j)) = 2; // Kepemilikan bangunan di matriks diset jadi 2 (player 2)
        }
        else {
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
    // while (!EndKata){

        // if (i % size == 1){

        //     InsVLastG(G, (i / size) + 1);
        //     if (CKata.TabKata[1] == '1'){

        //         InsVLastCon(G, FindLastG(*G), 1);                
        //     }            
        // }
        // else{

        //     if (CKata.TabKata[1] == '1'){

        //         if (i % size == 0){

        //             InsVLastCon(G, FindLastG(*G), size);    
        //         }
        //         else{

        //             InsVLastCon(G, FindLastG(*G), (i % size));
        //         }
        //     }
        // }

        // i++;
        // ADVKATA();
    //}
}

void instantUpgrade(state *S){
    // seluruh bangunan yg dimiliki player levelnya naik 1
	Player cek;
	if(S->P1.turn) cek=S->P1;
	else cek=S->P2;
    address adr = First(cek.listbangunan);
    while(adr != Nil){
        S->ArrBang.TI[Info(adr)].level += 1;
        adr = Next(adr);
    }
    printf("skill 'Instant Upgrade' berhasil dilakukan!\n");
}

void instantReinforcement(state *S){
    // seluruh bangunan +5 army
	Player cek;
	if(S->P1.turn) cek=S->P1;
	else cek=S->P2;
    address adr;
    adr = First(cek.listbangunan);
    while(adr != Nil){
        Army(S->ArrBang.TI[Info(adr)]) += 5;
        adr = Next(adr);
    }
    printf("skill 'Instant Reinforcement' berhasil dilakukan!\n");
}

void Barrage(state *S){
    // iterasi buat semua bangunan lawan di -10 army
	Player cek;
	if(S->P1.turn) cek=S->P1;
	else cek=S->P2;
    address adr;
    adr = First(cek.listbangunan);
    while(adr != Nil){
        if (Army(S->ArrBang.TI[Info(adr)]) >= 10){
            Army(S->ArrBang.TI[Info(adr)]) -= 10;
        }else{
            Army(S->ArrBang.TI[Info(adr)]) = 0;
        }
        adr = Next(adr);
    }
    
    printf("skill 'Barrage' berhasil dilakukan!\n");
}

void extraTurn(state *S){
	Player cek;
	if(S->P1.turn) cek=S->P1;
	else cek=S->P2;
	cek.et=true;
}

void UseSkill(state *S){
    int InfoSkill;
	Player *cek;
	if(S->P1.turn) cek=&S->P1;
	else cek=&S->P2;
    InfoSkill = InfoHead(cek->skill);
    if (InfoSkill == 1){
        instantUpgrade(S);
    }else if (InfoSkill == 3){
        instantReinforcement(S);
    }else if (InfoSkill == 4){
        Barrage(S);
    }else if (InfoSkill == 2){
        extraTurn(S);
    }
    DelQueue(&(cek->skill), &InfoSkill);
}

int main(){
    Player *P1,*P2;
    state S;
    P1 = &(S.P1);
    P2 = &(S.P2);
    InitPlayer(P1);
    InitPlayer(P2);
    //Queue Q1, Q2;
    //Graph G;
    //TabInt ArrBang; //array dinamis yang menyimpan seluruh bangunan
    //List L1, L2; // L1( list keterhubungan bangunan yang dimiliki player 1)
                   // L2( list keterhubungan bangunan yang dimiliki player 2)
    MATRIKS M;
    //boolean P1Turn, P2Turn, EndGame;
    boolean EndGame;
    int i;

    // Untuk sekarang permainan langsung dimulai saat program dimulai
    // printf("a");
    STARTKATA();         // Baca dari file config
    ReadMatriksSize(&(S.M));
    ReadBangunan(&S);
    ReadGraph(&(S.G), NbElmtAB(S.ArrBang));

    EndGame = false;
    P1->turn = true;
    P2->turn = false;
    CreateEmptyQueue(&(S.P1.skill), 10);      // Inisialisasi Queue dan ngasih Instant Upgrade (direpresentasikan dengan 1 untuk sementara) ke Skill Queue kedua player 
    CreateEmptyQueue(&(S.P2.skill), 10);
    AddQueue(&(S.P1.skill), 1);       
    AddQueue(&(S.P2.skill), 1);
    while (!EndGame){

        TulisMATRIKS(S.M);
        if (P1->turn){

            printf("Player 1\n");
            CetakListB(S.P1.listbangunan, S.ArrBang);
            printf("Skill Available : ");
            PrintSkill(S.P1.skill);
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang
            for (i = 1; i <= CKata.Length; i++){

                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (IsSameString(CKata, "attack")){
                attack(&S);
            }
            else if (IsSameString(CKata, "level_up")){
               level_up(&S);
            }
            else if (IsSameString(CKata, "skill")){
                 UseSkill(&S);
            }
            /*
            else if (IsSameString(CKata, "undo")){


            }*/
            else if (IsSameString(CKata, "end_turn")){
                P2->turn=true;
                P1->turn=false;
            }
            else if (IsSameString(CKata, "save")){


            }
            else if (IsSameString(CKata, "move")){
                move(&S);
            }
            else if (IsSameString(CKata, "exit")){
                EndGame = true;
            }

        }
        else if (P2->turn){

            printf("Player 2\n");
            CetakListB(S.P2.listbangunan, S.ArrBang);
            printf("Skill Available : ");
            PrintSkill(S.P2.skill);
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang   
            for (i = 1; i <= CKata.Length; i++){
                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (IsSameString(CKata, "attack")){
                attack(&S);
            }
            else if (IsSameString(CKata, "level_up")){
                level_up(S.P2.listbangunan, &(S.ArrBang));
            }
            else if (IsSameString(CKata, "skill")){
                UseSkill(&S);
            }/*
            else if (IsSameString(CKata, "undo")){


            }*/
            else if (IsSameString(CKata, "end_turn")){
                P2->turn=false;
                P1->turn=true;
            }/*
            else if (IsSameString(CKata, "save")){


            }*/
            else if (IsSameString(CKata, "move")){
                move(&S);
            }
            else if (IsSameString(CKata, "exit")){
                EndGame=true;
            }
        }
    }

    return 0;
}
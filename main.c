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
#include "saveload.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void welcome(){
    printf("                                                                                                   .-.       \n");
    printf("                                                                                                  {{#}}      \n");
    printf("          {}                                                                                       8@8       \n");
    printf("        .::::.                                                                                     888       \n");
    printf("    @\\\\/W\\\/\\\/W\\\//@                                                                                 8@8       \n");
    printf("     \\\\/^\\\/\\\/^\\\//                                                                             _    )8(    _  \n");
    printf("      \\\_O_{}_O_/                                                                             (@)__/8@8\\\__(@) \n");
    printf(" ____________________                                                                         `~'-=|:|=-'~`  \n");
    printf("|<><><>  |  |  <><><>|                                                                             |.|       \n");
    printf("|<>      |  |      <>|                            .__                                              |S|       \n");    
    printf("|<>      |  |      <>|         __  _  __   ____   |  |     ____     ____     _____     ____        |'|       \n");
    printf("|<>   .--------.   <>|         \\\ \\\/ \\\/ / _/ __ \\\  |  |   _/ ___\\\   /  _ \\\   /     \\\  _/ __ \\\       |.|       \n");
    printf("|     |   ()   |     |          \\\     /  \\\  ___/  |  |__ \\\  \\\___  (  <_> ) |  Y Y  \\\ \\\  ___/       |P|       \n");
    printf("|_____| (O\\\/O) |_____|           \\\/\\\_/    \\\___  > |____/  \\\___  >  \\\____/  |__|_|  /  \\\___  >      |'|       \n");
    printf("|     \\\   /\\\   /     |                        \\\/              \\\/                 \\\/       \\\/       |.|       \n");
    printf("|------\\\  \\\/  /------|                                                                             |U|       \n");
    printf("|       '.__.'       |                                  T O                                        |'|       \n");
    printf("|        |  |        |                                                                             |.|       \n");
    printf(":        |  |        :                      A V A T A R     G A M E                                |N|       \n");
    printf(" \\\       |  |       /                                                                              |'|       \n");
    printf("  \\\<>    |  |    <>/                                                                               |.|       \n");
    printf("   \\\<>   |  |   <>/                                                                                |K|       \n");
    printf("    `\\\<> |  | <>/'                                                                                 |'|       \n");
    printf("      `-.|__|.-`                                                                                   \\\ /       \n");
    printf("                                                                                                    ^        \n");
    

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
    printf("-------------------------------------------------\n");
    printf("|  skill 'Instant Upgrade' berhasil dilakukan!  |\n");
    printf("-------------------------------------------------\n");
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
    printf("-------------------------------------------------------\n");
    printf("|  skill 'Instant Reinforcement' berhasil dilakukan!  |\n");
    printf("-------------------------------------------------------\n");
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
    printf("-----------------------------------------\n");
    printf("|  skill 'Barrage' berhasil dilakukan!  |\n");
    printf("-----------------------------------------\n");
}

void extraTurn(state *S){
    if (S->P1.turn) S->P1.et = true;
    if (S->P2.turn) S->P2.et = true;
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
    }else if(InfoSkill == 5){
        if(S->P1.turn) S->P1.shieldturn=2;
        else S->P2.shieldturn=2;
    }
    DelQueue(&(cek->skill), &InfoSkill);
}

int main(){
    Player *P1,*P2;
    state S;
    Stack statestack;
    CreateEmptyStack(&statestack);
    P1 = &(S.P1);
    P2 = &(S.P2);
    InitPlayer(P1);
    InitPlayer(P2);
    //boolean P1Turn, P2Turn, EndGame;
    boolean EndGame;
    int i;

    welcome();
    printf("***************************************\n");
    printf("*** PLEASE CHOOSE ! NEW_GAME / LOAD ***\n");
    printf("***************************************\n");
    printf("ENTER CHOICE : ");
    STARTKATACMD();
    for (i = 1; i <= CKata.Length; i++){
        CKata.TabKata[i] = tolower(CKata.TabKata[i]);
    }
    if (IsSameString(CKata, "new_game")){

        STARTKATA();         // Baca dari file config
        ReadMatriksSize(&(S.M));
        ReadBangunan(&S);
        ReadGraph(&(S.G), NbElmtAB(S.ArrBang));
        P1->turn = true;
        P2->turn = false;
        CreateEmptyQueue(&(S.P1.skill), 10);      // Inisialisasi Queue dan ngasih Instant Upgrade (direpresentasikan dengan 1 untuk sementara) ke Skill Queue kedua player 
        CreateEmptyQueue(&(S.P2.skill), 10);
        AddQueue(&(S.P1.skill), 1);       
        AddQueue(&(S.P2.skill), 1);
    }
    else if (IsSameString(CKata, "load")){

        LOADGAME(&S);
    }
    int aksi=0;
    EndGame = false;
    while (!EndGame){
        //TulisMATRIKS(S.M);
        if (P1->turn){
            printf("          _                                   _ \n");
            printf("  _ __   | |   __ _   _   _    ___   _ __    / |\n");
            printf(" | '_ \\\  | |  / _` | | | | |  / _ \\\ | '__|   | |\n");
            printf(" | |_) | | | | (_| | | |_| | |  __/ | |      | |\n");
            printf(" | .__/  |_|  \\\__,_|  \\\__, |  \\\___| |_|      |_|\n");
            printf(" |_|                  |___/                     \n");
            TulisMATRIKS(S.M);
            //printf("Player 1\n");
            CetakListB(S.P1.listbangunan, S.ArrBang);
            printf("Skill Available : ");
            PrintSkill(S.P1.skill);
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang
            for (i = 1; i <= CKata.Length; i++){
                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (IsSameString(CKata, "attack")){
                PushStack(&statestack,S);
                attack(&S);
                if(NbElmtLB(S.P2.listbangunan)==0){
                    printf("PLAYER 2 WIN!!!");
                    EndGame=true;
                }
                aksi++;
                //if(aksi) printf("masuk bro\n");
            }
            else if (IsSameString(CKata, "level_up")){
                PushStack(&statestack,S);
                level_up(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "skill")){
                PushStack(&statestack,S);
                UseSkill(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "undo")){
                if(aksi>0){
                    state prev;
                    PopStack(&statestack,&prev);
                    DeallocState(&S);
                    S = prev;
                    aksi-=1;
                }else printf("Anda belum melakukan aksi apapun\n");
            }
            else if (IsSameString(CKata, "end_turn")){
                if (S.P1.et){
                    printf("Extra turn has been used!\n");
                    AddPasukanLB(S.P1.listbangunan,&(S.ArrBang));
                    ResetBattle(&(S.P1.listbangunan));
                    S.P1.et = false;
                    CreateEmptyStack(&statestack);
                }
                else{
                    P2->turn=true;
                    P1->turn=false;
                    AddPasukanLB(S.P2.listbangunan,&(S.ArrBang));
                    ResetBattle(&(S.P2.listbangunan));
                    if (S.P2.shieldturn > 0) S.P2.shieldturn -= 1;
                    CreateEmptyStack(&statestack);
                    }
                aksi=0;
            }
            else if (IsSameString(CKata, "save")){
                SAVEGAME(S);
            }
            else if (IsSameString(CKata, "move")){
                PushStack(&statestack,S);
                move(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "exit")){
                EndGame = true;
            }else printf("Command tidak terdaftar\n");

        }
        else if (P2->turn){
            printf("          _                                   ____ \n");
            printf("  _ __   | |   __ _   _   _    ___   _ __    |___ \\\ \n");
            printf(" | '_ \\\  | |  / _` | | | | |  / _ \\\ | '__|     __) |\n");
            printf(" | |_) | | | | (_| | | |_| | |  __/ | |       / __/ \n");
            printf(" | .__/  |_|  \\\__,_|  \\\__, |  \\\___| |_|      |_____|\n");
            printf(" |_|                  |___/\n");
            TulisMATRIKS(S.M);       
            //printf("Player 2\n");
            CetakListB(S.P2.listbangunan, S.ArrBang);
            printf("Skill Available : ");
            PrintSkill(S.P2.skill);
            printf("ENTER COMMAND : ");
            STARTKATACMD();  // Command yang dimasukin ada di CKata sekarang   
            for (i = 1; i <= CKata.Length; i++){
                CKata.TabKata[i] = tolower(CKata.TabKata[i]);       // Ngelowercase input user, supaya input seperti aTtAcK pun bisa diterima
            }
            
            if (IsSameString(CKata, "attack")){
                PushStack(&statestack,S);
                attack(&S);
                if(NbElmtLB(S.P1.listbangunan)==0){
                    printf("PLAYER 1 WIN!!!");
                    EndGame=true;
                }
                aksi++;
            }
            else if (IsSameString(CKata, "level_up")){
                PushStack(&statestack,S);
                level_up(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "skill")){
                PushStack(&statestack,S);
                UseSkill(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "undo")){
                if(aksi>0){
                    state prev;
                    PopStack(&statestack,&prev);
                    DeallocState(&S);
                    S = prev;
                    aksi-=1;
                }else printf("Anda belum melakukan aksi apapun\n");
            }
            else if (IsSameString(CKata, "end_turn")){
                if (S.P2.et){
                    printf("Extra turn has been used!\n");
                    AddPasukanLB(S.P1.listbangunan,&(S.ArrBang));
                    ResetBattle(&(S.P1.listbangunan));
                    S.P2.et = false;
                }
                else{
                P2->turn=false;
                P1->turn=true;
                AddPasukanLB(S.P1.listbangunan,&(S.ArrBang));
                ResetBattle(&(S.P1.listbangunan));
                if (S.P1.shieldturn > 0) S.P1.shieldturn -= 1;}
                CreateEmptyStack(&statestack);
            }
            else if (IsSameString(CKata, "save")){
                SAVEGAME(S);
            }
            else if (IsSameString(CKata, "move")){
                PushStack(&statestack,S);
                move(&S);
                aksi++;
            }
            else if (IsSameString(CKata, "exit")){
                EndGame=true;
            }else printf("Command tidak terdaftar\n");
        }
    }

    return 0;
}
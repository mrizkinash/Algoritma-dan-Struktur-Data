#include <stdio.h>
#include "command.h"

void attack(state *S){
    boolean all; // ngecek apakah seluruh bangunan yg dimiliki player sudah pernah attack
    if(S->P1.turn) all = AllAttack(S->P1.listbangunan,S->ArrBang);
    else all = AllAttack(S->P2.listbangunan,S->ArrBang);
    if(!all){ // klo masih ada bangunan yg blom attack
        printf("Daftar Bangunan:\n"); // cetak bangunan yg player punya
        if(S->P1.turn) CetakListB(S->P1.listbangunan,S->ArrBang);
        else CetakListB(S->P2.listbangunan,S->ArrBang);
        printf("Bangunan yang digunakan untuk menyerang: ");
        int x;
        scanf("%d",&x);
        // cek udh pernah nyerang atau belum
        boolean sudah;
        if(S->P1.turn) sudah=CekAttack(S->P1.listbangunan,x);
        else sudah=CekAttack(S->P2.listbangunan,x);
        
        if(!sudah){
            int menyerang;
            if(S->P1.turn) menyerang= CariIdxB(S->P1.listbangunan,x);
            else menyerang= CariIdxB(S->P2.listbangunan,x);
            printf("Daftar bangunan yang dapat diserang:\n");
            int TLawan[30];
            adrG P = SearchG(S->G,menyerang);
            address P2= Next(P);
            int i=1;
            int player;
            if(S->P1.turn) player=1;
            else player=2;
            while(P2!=Nil){
                if(Owner(S->ArrBang.TI[Info(P2)])!=player){
                    TLawan[i]=Info(P2);
                    printf("%d. ",i);
                    CetakBangunan(S->ArrBang.TI[TLawan[i]]);
                    i++;
                }
                P2=Next(P2);
            }

            if(i==0) printf("Tidak terdapat bangunan yang bisa diserang");
            else{
                printf("Bangunan yang diserang: ");
                int y;
                scanf("%d",&y);
                int diserang;
                diserang = TLawan[y];
                printf("Jumlah pasukan: ");
                int pas;
                scanf("%d",&pas);
                while (pas>Army(S->ArrBang.TI[menyerang])){
                    printf("jumlah pasukan tidak valid\n");
                    scanf("%d",&pas);
                }

                int new_pas;
                if(GetP(S->ArrBang.TI[diserang])){ // klo ada pertahanan
                    new_pas = ( (0.75*pas) - Army(S->ArrBang.TI[diserang]));
                    if(new_pas<0){
                        Army(S->ArrBang.TI[menyerang])-=pas; // ngurangin pasukan sendiri
                        Army(S->ArrBang.TI[diserang])-=(0.75*pas); // ngurangin pasukan lawan 3/4 dr jumalah pasukan yg attack
                        printf("Bangunan gagal direbut\n");
                    }else{
                        if(player==1){
                        //bangunan jd punya player 1
                        ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 1);
                        Army(S->ArrBang.TI[menyerang])-=pas;
                        DelPLB (&(S->P2.listbangunan), diserang); // apus bangunan dari list player 2
                        InsVLastLB(&(S->P1.listbangunan),diserang);// nambahin bangunan di list L1
                        }
                        else{
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 2);
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P1.listbangunan), diserang); // apus dari list player 1
                            InsVLastLB(&(S->P2.listbangunan),diserang);// nambahin bangunan di list L2
                        }
                        printf("Bangunan menjadi milikmu\n");
                        if(S->P1.turn){
                            SudahAttack(&(S->P1.listbangunan),x); // ubah jadi pernah nyerang
                            //printf("halo\n");
                            if(Type(S->ArrBang.TI[diserang])=='F') AddQueue(&(S->P2.skill),2); // syarat dapet skill extra turn 
                            else if(NbElmtLB(S->P1.listbangunan)==10) AddQueue(&(S->P1.skill),4); // syarat dapet skill barrage 
                        }else{
                            SudahAttack(&(S->P2.listbangunan),x);
                            if(Type(S->ArrBang.TI[diserang])=='F') AddQueue(&(S->P1.skill),2);
                            else if(NbElmtLB(S->P2.listbangunan)==10) AddQueue(&(S->P2.skill),4);
                        }
                    }
                }
                else{
                    new_pas = pas-Army(S->ArrBang.TI[diserang]);
                    if(new_pas<0){
                        Army(S->ArrBang.TI[menyerang])-=pas; // ngurangin pasukan sendiri
                        Army(S->ArrBang.TI[diserang])-=pas; // ngurangin pasukan lawan
                        printf("Bangunan gagal direbut\n");
                    }else{
                        //kondisi menang
                        if(player==1){
                            //bangunan jd punya player 1
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 1);
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P2.listbangunan), diserang); // apus bangunan dari list player 2
                            InsVLastLB(&(S->P1.listbangunan),diserang);// nambahin bangunan di list L1
                        }
                        else{
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 2);
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P1.listbangunan), diserang); // apus dari list player 1
                            InsVLastLB(&(S->P2.listbangunan),diserang);// nambahin bangunan di list L2
                        }
                        printf("Bangunan menjadi milikmu\n");
                        if(S->P1.turn){
                            SudahAttack(&(S->P1.listbangunan),x); // ubah jadi pernah nyerang
                            //printf("halo\n");
                            if(Type(S->ArrBang.TI[diserang])=='F') AddQueue(&(S->P2.skill),2); // syarat dapet skill extra turn 
                            else if(NbElmtLB(S->P1.listbangunan)==10) AddQueue(&(S->P1.skill),4); // syarat dapet skill barrage 
                        }else{
                            SudahAttack(&(S->P2.listbangunan),x);
                            if(Type(S->ArrBang.TI[diserang])=='F') AddQueue(&(S->P1.skill),2);
                            else if(NbElmtLB(S->P2.listbangunan)==10) AddQueue(&(S->P2.skill),4);
                        }
                    }
                }
            }
        } else printf("Bangunan ini sudah pernah melakukan attack\n");
    } else printf("Seluruh bangunan anda sudah pernah melakukan attack\n");
}

void level_up(state *S){
    boolean all; // cek udh semuanya level 4 atau blom
    if (S->P1.turn) ceklvl4(S->P1.listbangunan,S->ArrBang);
    else ceklvl4(S->P2.listbangunan,S->ArrBang);
    if(all) printf("seluruh bangunan sudah berada di level tertinggi\n");
    else{
        printf("Daftar Bangunan:\n");
        if (S->P1.turn) CetakListB(S->P1.listbangunan,S->ArrBang);
        else CetakListB(S->P2.listbangunan,S->ArrBang);
        printf("Bangunan yang akan di level up: ");
        int x;
        scanf("%d",&x);
        int lvlup;
        if(S->P1.turn) lvlup = CariIdxB(S->P1.listbangunan,x);
        else lvlup = CariIdxB(S->P2.listbangunan,x);
        if(Level(S->ArrBang.TI[lvlup])==4) printf("Bangunan ini sudah di level tertinggi\n"); // klo bangunan yg dipilih udah lvl 4
        else{
            LevelUpBangunan(&(S->ArrBang.TI[lvlup]));
            if(S->P1.turn && ceklvl4(S->P1.listbangunan,S->ArrBang)) AddQueue(&(S->P1.skill),3); // syarat dapet skill instant reinforcement
            else if(S->P2.turn && ceklvl4(S->P2.listbangunan,S->ArrBang)) AddQueue(&(S->P2.skill),3); // syarat dapet skill instant reinforcement
            printf("Anda sukses melakukan level up!\n");
        }
    }
}

void move(TabInt *ArrBang, Graph G, int player, List L){
    printf("Daftar Bangunan:\n");
    CetakListB(L,*ArrBang);
    printf("Pilih bangunan: ");
    int x;
    scanf("%d",&x);
    int asal;
    asal= CariIdxB(L,x);
    printf("Daftar bangunan yang dapat terdekat:\n");
        int TLawan[30]; // menyimpan data bangunan yg tersambung dan milik sendiri
        adrG P = SearchG(G,asal);
        address P2= Next(P);
        int i=1;
        while(P2!=Nil){
            if(Owner(ArrBang->TI[Info(P2)])==player){
                TLawan[i]=Info(P2);
                printf("%d. ",i);
                CetakBangunan(ArrBang->TI[Info(P2)]);
                i++;
            }
            P2=Next(P2);
        }
        printf("Bangunan yang akan menerima: ");
        int y;
        scanf("%d",&y);
        int terima;
        terima = TLawan[y];
        printf("Jumlah pasukan: ");
        int gain;
        scanf("%d",&gain);
        MovePasukan(&(ArrBang->TI[asal]),&(ArrBang->TI[terima]), gain);
}
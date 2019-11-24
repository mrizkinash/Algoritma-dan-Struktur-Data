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
            int i=0;
            int player;
            if(S->P1.turn) player=1;
            else player=2;
            while(P2!=Nil){
                if(Owner(S->ArrBang.TI[Info(P2)])!=player){
                    i++;
                    TLawan[i]=Info(P2);
                    printf("%d. ",i);
                    CetakBangunan(S->ArrBang.TI[TLawan[i]]);
                }
                P2=Next(P2);
            }

            if(i==0) printf("Tidak ada\n");
            else{
                printf("Bangunan yang diserang: ");
                int y;
                scanf("%d",&y);
                while(y<0 || y>i){
                    printf("Masukkan tidak valid\n");
                    printf("Bangunan yang diserang: ");
                    scanf("%d",&y);
                }
                int diserang;
                diserang = TLawan[y];
                printf("Jumlah pasukan: ");
                int pas;
                scanf("%d",&pas);
                while (pas>Army(S->ArrBang.TI[menyerang]) || pas < 0){
                    printf("Jumlah pasukan tidak valid\n");
                    printf("Jumlah pasukan: ");
                    scanf("%d",&pas);
                }

                int new_pas;
                if(GetP(S->ArrBang.TI[diserang]) || S->P2.shieldturn >0){ // klo ada pertahanan
                    new_pas = ( (0.75*pas) - Army(S->ArrBang.TI[diserang]));
                    if(new_pas<0){
                        Army(S->ArrBang.TI[menyerang])-=pas; // ngurangin pasukan sendiri
                        Army(S->ArrBang.TI[diserang])-=(0.75*pas); // ngurangin pasukan lawan 3/4 dr jumalah pasukan yg attack
                        printf("----------------------------\n");
                        printf("|  Bangunan gagal direbut  |\n");
                        printf("----------------------------\n");
                    }else{
                        if(player==1){
                            //bangunan jd punya player 1
                            if((Owner(S->ArrBang.TI[diserang])==2) && (NbElmtLB(S->P2.listbangunan)==3)) AddQueue(&(S->P2.skill),5);
                            if(Type(S->ArrBang.TI[diserang])=='F' && Owner(S->ArrBang.TI[diserang])==2) AddQueue(&(S->P2.skill),2); // syarat dapet skill extra turn 
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 1);
                            S->M.Mem[(S->ArrBang.TI[diserang].P.X)][(S->ArrBang.TI[diserang].P.Y)].Owner = 1;
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P2.listbangunan), diserang); // apus bangunan dari list player 2
                            InsVLastLB(&(S->P1.listbangunan),diserang);// nambahin bangunan di list L1
                    }
                        else{
                            if((Owner(S->ArrBang.TI[diserang])==2) && (NbElmtLB(S->P1.listbangunan)==3)) AddQueue(&(S->P1.skill),5);
                            if(Type(S->ArrBang.TI[diserang])=='F' && Owner(S->ArrBang.TI[diserang])==1) AddQueue(&(S->P1.skill),2);
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 2);
                            S->M.Mem[(S->ArrBang.TI[diserang].P.X)][(S->ArrBang.TI[diserang].P.Y)].Owner = 2;
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P1.listbangunan), diserang); // apus dari list player 1
                            InsVLastLB(&(S->P2.listbangunan),diserang);// nambahin bangunan di list L2
                        }
                        printf("------------------------------\n");
                        printf("|  Bangunan menjadi milikmu!  |\n");
                        printf("------------------------------\n");
                        if(S->P1.turn){
                            SudahAttack(&(S->P1.listbangunan),x); // ubah jadi pernah nyerang
                            if(NbElmtLB(S->P1.listbangunan)==10) AddQueue(&(S->P1.skill),4); // syarat dapet skill barrage 
                        }else{
                            SudahAttack(&(S->P2.listbangunan),x);
                            if(NbElmtLB(S->P2.listbangunan)==10) AddQueue(&(S->P2.skill),4);
                        }
                    }
                }else{ // kalo gada pertahanan
                    new_pas = pas-Army(S->ArrBang.TI[diserang]);
                    if(new_pas<0){
                        Army(S->ArrBang.TI[menyerang])-=pas; // ngurangin pasukan sendiri
                        Army(S->ArrBang.TI[diserang])-=pas; // ngurangin pasukan lawan
                        printf("----------------------------\n");
                        printf("|  Bangunan gagal direbut  |\n");
                        printf("----------------------------\n");
                    }else{
                        //kondisi menang
                        if(player==1){
                            //bangunan jd punya player 1
                            if((Owner(S->ArrBang.TI[diserang])==2) && (NbElmtLB(S->P2.listbangunan)==3)) AddQueue(&(S->P2.skill),5);
                            if(Type(S->ArrBang.TI[diserang])=='F' && Owner(S->ArrBang.TI[diserang])==2) AddQueue(&(S->P2.skill),2); // syarat dapet skill extra turn
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 1);
                            S->M.Mem[(S->ArrBang.TI[diserang].P.X)][(S->ArrBang.TI[diserang].P.Y)].Owner = 1;
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P2.listbangunan), diserang); // apus bangunan dari list player 2
                            InsVLastLB(&(S->P1.listbangunan),diserang);// nambahin bangunan di list L1
                        }
                        else{
                            if((Owner(S->ArrBang.TI[diserang])==2) && (NbElmtLB(S->P1.listbangunan)==3)) AddQueue(&(S->P1.skill),5);
                            if(Type(S->ArrBang.TI[diserang])=='F' && Owner(S->ArrBang.TI[diserang])==1) AddQueue(&(S->P1.skill),2);
                            ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 2);
                            S->M.Mem[(S->ArrBang.TI[diserang].P.X)][(S->ArrBang.TI[diserang].P.Y)].Owner = 2;
                            Army(S->ArrBang.TI[menyerang])-=pas;
                            DelPLB (&(S->P1.listbangunan), diserang); // apus dari list player 1
                            InsVLastLB(&(S->P2.listbangunan),diserang);// nambahin bangunan di list L2
                        }
                        printf("------------------------------\n");
                        printf("|  Bangunan menjadi milikmu!  |\n");
                        printf("------------------------------\n");
                        if(S->P1.turn){
                            
                            SudahAttack(&(S->P1.listbangunan),x); // ubah jadi pernah nyerang
                            //printf("halo\n"); 
                            if(NbElmtLB(S->P1.listbangunan)==10) AddQueue(&(S->P2.skill),4); // syarat dapet skill barrage 
                        }else{
                            SudahAttack(&(S->P2.listbangunan),x);
                            if(NbElmtLB(S->P2.listbangunan)==10) AddQueue(&(S->P1.skill),4);
                        }
                    }
                }
            }
        } else{
            printf("------------------------------------------------\n");
            printf("|  Bangunan ini sudah pernah melakukan attack  |\n");
            printf("------------------------------------------------\n");
        }
    } else{
        printf("---------------------------------------------------------\n");
        printf("|  Seluruh bangunan anda sudah pernah melakukan attack  |\n");
        printf("---------------------------------------------------------\n");
    }
}

void level_up(state *S){
    boolean all; // cek udh semuanya level 4 atau blom
    if (S->P1.turn) all =ceklvl4(S->P1.listbangunan,S->ArrBang);
    else all = ceklvl4(S->P2.listbangunan,S->ArrBang);
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
            if(Army(S->ArrBang.TI[lvlup]) >= 0.5 * GetM(S->ArrBang.TI[lvlup])){
                LevelUpBangunan(&(S->ArrBang.TI[lvlup]));
                printf("-------------------------------------\n");
                printf("|  Anda sukses melakukan level up!  |\n");
                printf("-------------------------------------\n");
            }else LevelUpBangunan(&(S->ArrBang.TI[lvlup]));
            if(S->P1.turn && ceklvl4(S->P1.listbangunan,S->ArrBang)) AddQueue(&(S->P1.skill),3); // syarat dapet skill instant reinforcement
            else if(S->P2.turn && ceklvl4(S->P2.listbangunan,S->ArrBang)) AddQueue(&(S->P2.skill),3); // syarat dapet skill instant reinforcement
        }
    }
}

void move(state *S){
    int player;
    if (S->P1.turn) player=1;
    else player = 2;
    printf("Daftar Bangunan:\n");
    if (S->P1.turn) CetakListB(S->P1.listbangunan,S->ArrBang);
    else CetakListB(S->P2.listbangunan,S->ArrBang);
    printf("Pilih bangunan: ");
    int x;
    scanf("%d",&x);
    int asal;
    if(S->P1.turn) asal = CariIdxB(S->P1.listbangunan,x);
    else asal = CariIdxB(S->P2.listbangunan,x);

    printf("Daftar bangunan yang terdekat:\n");
    int TLawan[30];
    adrG P = SearchG(S->G,asal);
    address P2= Next(P);
    int i=0;
    while(P2!=Nil){
        if(Owner(S->ArrBang.TI[Info(P2)])==player){
            i++;
            TLawan[i]=Info(P2);
            printf("%d. ",i);
            CetakBangunan(S->ArrBang.TI[TLawan[i]]);
        }
        P2=Next(P2);
    }
    if(i==0) printf("Tidak ada");
    else{
        printf("Bangunan yang akan menerima: ");
        int y;
        scanf("%d",&y);
        while(y<0 || y>i){
            printf("Masukkan tidak valid\n");
            printf("Bangunan yang akan menerima: ");
            scanf("%d",&y);
        }
        int terima;
        terima = TLawan[y];
        printf("Jumlah pasukan: ");
        int gain;
        scanf("%d",&gain);
        while(gain<0 || gain> Army(S->ArrBang.TI[asal])){
            printf("Jumlah pasukan tidak valid\n");
            printf("Jumlah Pasukan: ");
            scanf("%d",&gain);
        }
        while(Army(S->ArrBang.TI[terima])+gain>GetM(S->ArrBang.TI[terima])){
            printf("Jumlah pasukan melebihi batas\n");
            printf("Jumlah Pasukan: ");
            scanf("%d",&gain);
        }
        MovePasukan(&(S->ArrBang.TI[asal]),&(S->ArrBang.TI[terima]), gain);
        printf("-------------------------------------\n");
        printf("|  Anda sukses memindahkan pasukan  |\n");
        printf("-------------------------------------\n");
    }
}
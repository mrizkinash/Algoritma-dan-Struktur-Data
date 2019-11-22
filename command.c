#include <stdio.h>
#include "command.h"

void attack(state *S){
    printf("Daftar Bangunan:\n");
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
        int TLawan[30]; // menyimpan data bangunan yg bisa di attack
        // MakeEmptyAB(TLawan,30);
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
        printf("Bangunan yang diserang: ");
        int y;
        scanf("%d",&y);
        int diserang;
        diserang = TLawan[y];
        printf("Jumlah pasukan: ");
        int pas;
        scanf("%d",&pas);
        while (pas<Army(S->ArrBang.TI[menyerang])){
            printf("jumlah pasukan tidak valid\n");
            scanf("%d",&pas);
        }
        // kondisi kalah
        if(pas<Army(S->ArrBang.TI[diserang])){
            Army(S->ArrBang.TI[diserang])-=pas;
            printf("Bangunan gagal direbut\n");
        }else{
            //kondisi menang
            int new_pas = pas-Army(S->ArrBang.TI[diserang]);
            if(player==1){
                //bangunan jd punya player 1
                ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 1);
                DelPLB (&(S->P2.listbangunan), diserang);
                // nambahin bangunan di list L1
            }
            else{
                ChangeOwnerB(&(S->ArrBang.TI[diserang]), new_pas, 2);
                DelPLB (&(S->P1.listbangunan), diserang);
                // nambahin bangunan di list L2
            }
            printf("Bangunan menjadi milikmu\n");
            if(S->P1.turn) SudahAttack(&(S->P1.listbangunan),x);
            SudahAttack(&(S->P2.listbangunan),x); // ubah jadi pernah nyerang
        }
    }
}

void level_up(List L, TabInt *ArrBang){
    printf("Daftar Bangunan:\n");
    CetakListB(L,*ArrBang);
    printf("Bangunan yang akan di level up: ");
    int x;
    scanf("%d",&x);
    int lvlup;
    lvlup = CariIdxB(L,x);
    LevelUpBangunan(&(ArrBang->TI[lvlup]));
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
        MakeEmptyAB(&TLawan,30);
        adrG P = SearchG(G,asal);
        address P2= Next2(P);
        int i=1;
        while(P2!=Nil){
            if(Owner(ArrBang->TI[Info(P2)])==player){
                TLawan[i]=Info(P2);
                printf("%d. ",i);
                CetakBangunan(ArrBang->TI[info(P2)]);
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
        MovePasukan(&ArrBang[asal], &ArrBang[terima], gain);
}
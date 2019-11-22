#include <stdio.h>
#include "command.h"

void attack(TabInt *ArrBang, Graph G, int player, List *L1, List *L2){
    Bangunan a;
    printf("Daftar Bangunan:\n");
    if(player==1) CetakListB(*L1,*ArrBang);
    else CetakListB(*L2,*ArrBang);
    printf("Bangunan yang digunakan untuk menyerang: ");
    int x;
    scanf("%d",&x);
    // cek udh pernah nyerang atau belum
    boolean sudah;
    if(player==1) sudah = CekAttack(*L1, x);
    else sudah = CekAttack(*L2, x);
    
    if(!sudah){
        int menyerang;
        if(player==1) menyerang= CariIdxB(*L1,x);
        else menyerang= CariIdxB(*L2,x);
        printf("Daftar bangunan yang dapat diserang:\n");
        int TLawan[30]; // menyimpan data bangunan yg bisa di attack
        // MakeEmptyAB(TLawan,30);
        adrG P = SearchG(G,menyerang);
        address P2= Next(P);
        int i=1;
        while(P2!=Nil){
            if(Owner(ArrBang->TI[Info(P2)])!=player){
                TLawan[i]=Info(P2);
                printf("%d. ",i);
                CetakBangunan(ArrBang->TI[TLawan[i]]);
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
        while (pas<Army(ArrBang->TI[menyerang])){
            printf("jumlah pasukan tidak valid\n");
            scanf("%d",&pas);
        }
        // kondisi kalah
        if(pas<Army(ArrBang->TI[diserang])){
            Army(ArrBang->TI[diserang])-=pas;
            printf("Bangunan gagal direbut\n");
        }else{
            //kondisi menang
            int new_pas = pas-Army(ArrBang->TI[diserang]);
            if(player==1){
                //bangunan jd punya player 1
                ChangeOwnerB(&(ArrBang->TI[diserang]), new_pas, 1);
                DelPLB (&L2, diserang);
            }
            else{
                ChangeOwnerB(&(ArrBang->TI[diserang]), new_pas, 2);
                DelPLB (&L1, diserang);
            }
            printf("Bangunan menjadi milikmu\n");
            SudahAttack(L,x); // ubah jadi pernah nyerang
        }
    }
}

void level_up(List L, TabInt ArrBang){
    printf("Daftar Bangunan:\n");
    CetakListB(L,ArrBang);
    printf("Bangunan yang akan di level up: ");
    int x;
    scanf("%d",&x);
    int lvlup;
    lvlup = CariIdxB(L,x);
    LevelUpBangunan(&(ArrBang.TI[lvlup]));
}

void move(TabInt *ArrBang, Graph G, int player, List *L){
    printf("Daftar Bangunan:\n");
    CetakListB(*L,*ArrBang);
    printf("Pilih bangunan: ");
    int x;
    scanf("%d",&x);
    int asal;
    asal= CariIdxB(*L,x);
    printf("Daftar bangunan yang dapat terdekat:\n");
        int TLawan[30]; // menyimpan data bangunan yg tersambung dan milik sendiri
        MakeEmptyAB(&TLawan);
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
            P2=Next2(P2);
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
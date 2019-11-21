void attack(TabInt ArrBang, Graph G, int player, List L){
    printf("Daftar Bangunan:\n");
    CetakBangunan(L);
    printf("Bangunan yang digunakan untuk menyerang: ");
    int x;
    scanf("%d",&x);
    // cek udh pernah nyerang atau belum
    boolean sudah;
    sudah = CekAttack(L, x);
    if(!sudah){
        int menyerang;
        menyerang= CariIdxB(L,x);
        printf("Daftar bangunan yang dapat diserang:\n");
        TabInt *TLawan; // menyimpan data bangunan yg bisa di attack
        MakeEmptyAB(&TLawan);
        address P = SearchG(G,menyerang);
        address2 P2= Next2(P);
        int i=1;
        while(P2!=Nil){
            if(Owner(ArrBang[Info(P2)])!=Player){
                *Tlawan[i]=Info(P2);
                printf("%d. ",i);
                CetakBangunan(ArrBang[info(P2)]);
                i++;
            }
            P2=Next2(P2);
        }
        printf("Bangunan yang diserang: ");
        int y;
        scanf("%d",&y);
        int diserang;
        diserang = Tlawan[y];
        printf("Jumlah pasukan: ");
        int pas;
        scanf("%d",&pas);
        while (pas<Army(ArrBang[menyerang])){
            printf("jumlah pasukan tidak valid\n");
            scanf("%d",&pas);
        }
        //kondisi menang
        int new_pas = pas-Army(ArrBang[diserang]);
        if(player==1){
            //bangunan jd punya player 1
            ChangeOwnerB(ArrBang[diserang], new_pas, 1);
            DelPLB (&L2, diserang);
        }
        else{
            ChangeOwnerB(ArrBang[diserang], new_pas, 2);
            DelPLB (&L1, diserang);
        }
        printf("Bangunan menjadi milikmu\n");
        SudahAttack(&L,x); // ubah jadi pernah nyerang
    }
}

void level_up(List L){
    printf("Daftar Bangunan:\n");
    CetakBangunan(L);
    printf("Bangunan yang akan di level up: ");
    int x;
    scanf("%d",&x);
    int lvlup;
    lvlup = CariIdxB(L,x);
    LevelUpBangunan(&ArrBang[lvlup]);
}

void move(List L){
    printf("Daftar Bangunan:\n");
    CetakBangunan(L);
    printf("Pilih bangunan: ");
    int x;
    scanf("%d",&x);
    int asal;
    asal= CariIdxB(L,x);
    printf("Daftar bangunan yang dapat terdekat:\n");
        TabInt *TLawan; // menyimpan data bangunan yg bisa di attack
        MakeEmptyAB(&TLawan);
        address P = SearchG(G,menyerang);
        address2 P2= Next2(P);
        int i=1;
        while(P2!=Nil){
            if(Owner(ArrBang[Info(P2)])!=Player){
                *Tlawan[i]=Info(P2);
                printf("%d. ",i);
                CetakBangunan(ArrBang[info(P2)]);
                i++;
            }
            P2=Next2(P2);
        }
        printf("Bangunan yang akan menerima: ");
        int y;
        scanf("%d",&y);
        int terima;
        terima = Tlawan[y];
        printf("Bangunan yang akan menerima: ");
        int gain;
        scanf("%d",&gain);
        MovePasukan(&ArrBang[asal], &ArrBang[terima], int gain);
}
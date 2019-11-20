#include "ADT/point.h"
#include "ADT/arraydin.h"
#include "ADT/matriks.h"
#include "ADT/mesinkata.h"
#include "ADT/queue.h"
#include "ADT/stackt.h"
#include "ADT/listlinier.h"
#include "ADT/boolean.h"
#include "ADT/graph.h"
#include "bangunan.h"

#include <stdio.h>
#include <stdlib.h>

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

int main(){
    int counter, tinggi, lebar, i, j;
    MATRIKS M;
    char type;
    TabInt ArrBang; //array dinamis yang menyimpan seluruh bangunan
    List *L1, *L2; // L1( list keterhubungan bangunan yang dimiliki player 1)
                   // L2( list keterhubungan bangunan yang dimiliki player 2)

    // DEKRALASI A, M, P BANGUNAN
    int AC[4],MC[4],AT[4],MT[4],AF[4],MF[4],AV[4],MV[4];
    boolean PC[4],PT[4],PF[4],PV[4];
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
    PF[3]=true; PF[4]=true;

    CreateEmptyLB(&L1);
    CreateEmptyLB(&L2);


    
    counter = 1;
    STARTKATA();         // Baca dari file config
    while (!EndKata){

        if (counter == 1){

            tinggi = KataToInt(CKata);
            ADVKATA()
            lebar = KataToInt(CKata);

            MakeMATRIKS(tinggi + 1, lebar + 1, &M);  // Membuat matriks (+ 2 karna pagar Mapnya)

            for (i = 0; i <= M.NBrsEff; i++){          // Bikin pager
                for (j = 0; j<= M.NKolEff; j++){

                    if ((i == 0) || (i == M.NBrsEff) || (j == 0) || (j == M.NKolEff)){
                        // matriks ganti jd nyimpen type sm owner aja
                        Elmt(M, i, j) = B;
                    }
                }
            }
            counter++;
        }
        else if(counter == 2){
            int size = KataToInt(CKata)
            counter += size;
            ADVKATA();
            MakeEmptyAB(&ArrBang,size);
            int x=1; // idx array bangunan
            Bangunan B;
            while (counter > 2){
                // Bikin bangunan disini
                type = CKata.TabKata[1];
                ADVKATA();
                i = KataToInt(CKata);
                ADVKATA();
                j = KataToInt(CKata);

                B = Elmt(ArrBang,x);
                CreateBangunan(&B,type,i,j); // create bangunan ke x
                if(x==1) InsVLastLB(&L1,1); // bangunan 1 milik pemain 1
                else if(x==2) InsVLastLB(&L2,2); // bangunan 2 milik pemain 2
                
                // matriks ganti jd nyimpen type sm owner aja
                Elmt(M, i, j) = B;  // Bangunan dijadikan elemen matriks of bangunan

                ADVKATA();
                x+=1;
                counter--
            }
            counter++;
        }
        else if (counter == 3){

            // Keterhubungan bangunan disini
        }
    }

    return 0;
}

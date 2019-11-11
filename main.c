#include "ADT/point.h"
#include "ADT/arraydin.h"
#include "ADT/matriks.h"
#include "ADT/mesinkata.h"
#include "ADT/queue.h"
#include "ADT/stackt.h"
#include "ADT/listlinier.h"
#include "ADT/graph.h"

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

void initBangunan (Bangunan *B, char CC, int X, int Y){

    setBangunanType(B, CC);
    setBangunanLevel(B, 1);
    setBangunanPoint(B, X, Y);

    if (CC == 'C'){

        (*B).gain = 10;
        (*B).max = 40;
        initArmy(B, 40);
        setBangunanShield(B, false);
    }
    else if (CC == 'T'){

        (*B).gain = 5;
        (*B).max = 20;
        initArmy(B, 30);
        setBangunanShield(B, true);
    }
    else if (CC == 'F'){

        (*B).gain = 10;
        (*B).max = 20;
        initArmy(B, 80);
        setBangunanShield(B, false);
    }
    else if (CC == 'V'){

        (*B).gain = 5;
        (*B).max = 20;
        initArmy(B, 20);
        setBangunanShield(B, false);
    }
    else{

        (*B).gain = 0;
        (*B).max = 0;
        initArmy(B, 0);
        setBangunanShield(B, false);
    }
}

int main(){
    int counter, tinggi, lebar, i, j;
    MATRIKS M;
    Bangunan B;
    char type;

    counter = 1;
    STARTKATA()         // Baca dari file config
    while (!EndKata){

        if (counter == 1){

            tinggi = KataToInt(CKata);
            ADVKATA()
            lebar = KataToInt(CKata);

            MakeMATRIKS(tinggi + 2, lebar + 2, &M);  // Membuat matriks (+ 2 karna pagar Mapnya)

            for (i = 1; i <= M.NBrsEff; i++){          // Bikin pager
                for (j = 1; j<= M.NKolEff; j++){

                    if ((i == 1) || (i == M.NBrsEff) || (j == 1) || (j == M.NKolEff)){

                        initBangunan(&B, '*', i, j);
                        Elmt(M, i, j) = B;
                    }
                }
            }
            counter++;
        }
        else if(counter == 2){

            counter += KataToInt(CKata);
            ADVKATA();
            while (counter > 2){

                // Bikin bangunan disini
                type = CKata.TabKata[1];
                ADVKATA();
                i = KataToInt(CKata);
                ADVKATA();
                j = KataToInt(CKata);

                initBangunan(&B, type, i, j);
                Elmt(M, i, j) = B;  // Bangunan dijadikan elemen matriks of bangunan

                ADVKATA();
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

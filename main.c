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
int main(){
    int counter, tinggi, lebar, i, j;
    MATRIKS M;

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

                        Elmt(M, i, j) = '*'
                    }
                }
            }
            counter++;
        }
        else if(counter == 2){

            counter += KataToInt(CKata);
            while (counter > 2){

            // Bikin bangunan disini
            }
        }
    }

    return 0;
}

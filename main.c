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
    int counter, tinggi, lebar, i, j, size, x;
    MATRIKS M;
    char type;
    TabInt ArrBang; //array dinamis yang menyimpan seluruh bangunan
    List L1, L2; // L1( list keterhubungan bangunan yang dimiliki player 1)
                   // L2( list keterhubungan bangunan yang dimiliki player 2)
    MultiList G;
    Bangunan B;

    // DEKRALASI A, M, P BANGUNAN
    /*int AC[5],MC[5],AT[5],MT[5],AF[5],MF[5],AV[5],MV[5];        // Indeks dari 0
    boolean PC[5],PT[5],PF[5],PV[5];
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
    PF[3]=true; PF[4]=true;*/

    CreateEmptyLB(&L1);
    CreateEmptyLB(&L2);

    counter = 1;
    STARTKATA();         // Baca dari file config
    while (!EndKata){

        if (counter == 1){ // Membaca baris 1, Konfigurasi lebar dan tinggi peta

            tinggi = KataToInt(CKata);
            ADVKATA();
            lebar = KataToInt(CKata);

            MakeMATRIKS(tinggi + 2, lebar + 2, &M);  // Membuat matriks (+ 2 karna pagar Mapnya)

            for (i = 0; i <= M.NBrsEff; i++){          // Bikin pager
                for (j = 0; j<= M.NKolEff; j++){

                    if ((i == 0) || (i == M.NBrsEff) || (j == 0) || (j == M.NKolEff)){
                        
                        MOwn(ElmtMat(M, i, j)) = 0;
                        MType(ElmtMat(M, i, j)) = '*';
                    }
                }
            }
            counter++;
        }
        else if(counter == 2){
            
            size = KataToInt(CKata);
            counter += size;
            ADVKATA();
            MakeEmptyAB(&ArrBang,size + 1);
            x=1; // idx array bangunan
            
            while (counter > 2){
                // Bikin bangunan disini
                type = CKata.TabKata[1];
                ADVKATA();
                i = KataToInt(CKata);
                ADVKATA();
                j = KataToInt(CKata);

                CreateBangunan(&B,type,i,j); // create bangunan ke x
                ElmtArr(ArrBang,x) = B; // masukin bangunan yg baru di create ke arrbang
                if(x==1){

               		InsVLastLB(&L1,1);	 // bangunan 1 milik pemain 1
               		MOwn(ElmtMat(M, i, j)) = 1; // Kepemilikan bangunan di matriks diset jadi 1 (player 1)
               	}
                else if(x==2){

                	InsVLastLB(&L2,2); // bangunan 2 milik pemain 2
                	MOwn(ElmtMat(M, i, j)) = 2; // Kepemilikan bangunan di matriks diset jadi 2 (player 2)
                }
                else {

                	MOwn(ElmtMat(M, i, j)) = 0;	// Kepemilikan bangunan di matriks diset jadi 0 (bukan punya siapa siapa)
                }

                MType(ElmtMat(M, i, j)) = type;

                ADVKATA();
                x+=1;
                counter--;
            }
            counter++;
        }
        else if (counter >= 3){

            // Keterhubungan bangunan disini
            CreateEmptyG(&G);
            CreateEmptyCon(&G, FirstG(G));
            i = 1;
            while (!EndKata){

            	if (i % size == 1){
            		
            		InsVLastG(&G, CKata.TabKata[1]);

            	}
            	else{

            		InsVLastCon(&G, FindLastG(G), CKata.TabKata[1]);
            	}

            	i++;
            	ADVKATA();
            }
        }
    }

    TulisMATRIKS(M);

    return 0;
}

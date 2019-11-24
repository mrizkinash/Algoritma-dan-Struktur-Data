#include "bangunan.h"
#include "graph.h"
#include "stackt.h"
#include "listlinier.h"


int main(){
    int AC[5],MC[5],AT[5],MT[5],AF[5],MF[5],AV[5],MV[5];		// Indeks dari 0
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
    PF[3]=true; PF[4]=true;

    TabInt arrbang;
    Graph G;
    List L1,L2;
    CreateEmptyG(&G);
    MakeEmptyAB(&arrbang);
    CreateEmptyLB(&L1);
    CreateEmptyLB(&L2);
    arrbang.Neff = 5;
    arrbang.TI[1].type = 'C';
    arrbang.TI[1].level = 1;
    arrbang.TI[1].army = 20;
    arrbang.TI[1].owner = 1;
    InsertLastLB(&L1,1);
    arrbang.TI[2].type = 'T';
    arrbang.TI[2].level = 1;
    arrbang.TI[2].army = 20;
    arrbang.TI[2].owner = 0;

    arrbang.TI[3].type = 'F';
    arrbang.TI[3].level = 1;
    arrbang.TI[3].army = 30;
    arrbang.TI[3].owner = 0;

    arrbang.TI[4].type = 'C';
    arrbang.TI[4].level = 1;
    arrbang.TI[4].army = 20;
    arrbang.TI[4].owner = 2;
    InsertLastLB(&L2,4);
    arrbang.TI[5].type = 'V';
    arrbang.TI[5].level = 1;
    arrbang.TI[5].army = 30;
    arrbang.TI[5].owner = 1;
    InsertLastLB(&L1,5);


    for(int i=1; i<=5; i++) InsVLastG(&G,i);
    address P = SearchG(G,1);
    InsVLastCon(&G,P,2);
    InsVLastCon(&G,P,5);
    P = SearchG(G,2);
    InsVLastCon(&G,P,1);
    InsVLastCon(&G,P,4);
    InsVLastCon(&G,P,5);
    P = SearchG(G,3);
    InsVLastCon(&G,P,4);
    InsVLastCon(&G,P,5);
    P = SearchG(G,4);
    InsVLastCon(&G,P,2);
    InsVLastCon(&G,P,3);
    P = SearchG(G,5);
    InsVLastCon(&G,P,1);
    InsVLastCon(&G,P,2);
    InsVLastCon(&G,P,3);
    attack(arrbang, G, 1, &L1, &L2);
    level_up(L1);
    move(L1);
}

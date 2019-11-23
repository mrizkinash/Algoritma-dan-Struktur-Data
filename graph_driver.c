#include "graph.h"
#include <stdio.h>

int main(){
    Graph G;
    CreateEmptyG(&G);
    for(int i=0; i<5; i++) InsVLastG (&G, i+1);
    for(int i=1; i<=5; i++){
        for(int j=1; j<=5; j++){
            if(i<j) AddRel(&G,i,j);
        }
    }
    adrG P;
    P = FirstG(G);
    while(Nextg(P)!=Nil){
        printf("%d ",Info(P));
        address P2;
        P2 = Next(P);
        while(P2!=Nil){
            printf("%d ",Info(P2));
            P2 = Next(P2);
        }
        printf("\n");
        P = Nextg(P);
    }
}
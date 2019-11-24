#include "queue.h"
#include <stdio.h>

int main(){
    Queue Q;
    CreateEmptyQueue(&Q,10);
    for(int i=0; i<10; i++) AddQueue(&Q,i+1);
    PrintQueue(Q);
    for(int i=0; i<10; i++){
        int X;
        if(i%2==0){
            printf("%d\n",i);
            DelQueue(&Q,&X);
            printf("Nih yang diapus : %d\n",X);
        }
    }
    printf("Queue yang baru: ");
    PrintQueue(Q);
}
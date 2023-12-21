#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define klucz 100

struct komunikat{
    long typ;
    char dane[256];
};

int main(){
    struct komunikat kom;
    int kolejka;
    char c;

    kolejka=msgget(klucz,0777|IPC_CREAT);
    while(1){
        if (msgrcv(kolejka,&kom,sizeof(char),0,0))
        {
            c = kom.dane[0];
            printf("serwer: otrzymalem %c od %5ld\n", c, kom.typ);
            c=++kom.dane[0]; // zmiana znaku na nastepny
            printf("serwer: odsylam %5c do %5ld\n", c, kom.typ);
            msgsnd(kolejka,&kom,sizeof(char),0);
        }
        msgctl(kolejka,IPC_RMID,0);
    }

    return 0;
}
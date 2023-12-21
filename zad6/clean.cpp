#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include<unistd.h>

int main() {
    int playerID=0;
    int semK = 10;
    int key = 1;
    int key2 = 2;
    int memory = shmget(key,512,0777 | IPC_CREAT | IPC_EXCL);
    if (memory == -1)
    {
        playerID=1;
        key = 2;
        key2 = 1;
    }

    memory = shmget(key,512,0777 | IPC_CREAT);
    int memory2 = shmget(key2,512,00777 | IPC_CREAT);
    int semaphore = semget(semK,2,IPC_CREAT);
    semctl(semaphore,0,SETVAL,0);
    semctl(semaphore,1,SETVAL,1);
    shmctl(memory, IPC_RMID, NULL);
    shmctl(memory2, IPC_RMID, NULL);
    semctl(semaphore,0,IPC_RMID);
    return 0;
}

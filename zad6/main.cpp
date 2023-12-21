#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include<unistd.h>

void read(int memory,std::string* res)
{
    char* strR = (char*)shmat(memory, nullptr, 0);
    std::cout << "card-chosen-by-Second-player:" << strR << std::endl;
    *res = strR;
    shmdt(strR);
}
void write(int memory,std::string* res)
{
    char* strW = (char*)shmat(memory, nullptr, 0);
    std::cout << "choose card A-B-C: ";
    std::cin.getline(strW, 512);
    std::cout << "card-chosen: " << strW << std::endl;
    *res = strW;
    shmdt(strW);
}
int main() {
    int score = 0;
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
    struct sembuf
            wait_0={0,-1,0},
            signal_1={1,1,0},
            wait_1={1,-1,0},
            signal_0={0,1,0};
    memory = shmget(key,512,0777 | IPC_CREAT);
    int memory2 = shmget(key2,512,0777 | IPC_CREAT);
    int semaphore = semget(semK,2,0777|IPC_CREAT);
    semctl(semaphore,0,SETVAL,0);
    semctl(semaphore,1,SETVAL,1);
    std::cout << semaphore <<" "<<memory<< " " << memory2 <<" " <<playerID<<"\n";
    int iter = 3;
    for (int i = 0; i < iter;i++)
    {
        if (playerID==0)
        {
            std::string w;
            std::string r;
            write(memory,&w);
            semop(semaphore,&wait_0,1);
            read(memory2,&r);
            if (w == r)
            {
                printf("%s %s\n",w.c_str(),r.c_str());
                std::cout<<"you've lost"<<"\n";
                score -= 1;
            } else {
                printf("%s %s\n",w.c_str(),r.c_str());
                std::cout<<"you've won"<<"\n";
                score += 1;
            }
            semop(semaphore,&signal_1,1);
        }
        else
        {
            std::string w;
            std::string r;
            write(memory,&w);
            semop(semaphore,&wait_1,1);
            read(memory2,&r);
            if (w == r)
            {
                printf("%s %s\n",w.c_str(),r.c_str());
                std::cout<<"you've won"<<"\n";
                score += 1;
            } else {
                printf("%s %s %d\n",w.c_str(),r.c_str(),w==r);
                std::cout<<"you've lost"<<"\n";
                score -= 1;
            }
            semop(semaphore,&signal_0,1);
        }

    }
    if (playerID==0)
    {
        shmctl(memory, IPC_RMID, NULL);
        semctl(semaphore,0,IPC_RMID);
    }
    return 0;
}

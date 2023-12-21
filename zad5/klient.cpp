#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#define inputK 1234
#define outputK 5678

struct Message {
    long mtype;
    pid_t client_pid;
    char word[256];
};

int main() {

    std::string word;
    std::cin >> word;
    int input_queue = msgget(inputK, IPC_CREAT | 0666);
    int output_queue = msgget(outputK, IPC_CREAT | 0666);
    Message msg;
    msg.mtype = 1;
    msg.client_pid = getpid();
    strcpy(msg.word, word.c_str());
    msgsnd(input_queue, &msg, sizeof(msg), 0);
    msgrcv(output_queue, &msg, sizeof(msg), getpid(), 0);
    std::cout << "Zapytanie: " << word << ", Odpowiedz: " << msg.word << std::endl;
    return 0;
}

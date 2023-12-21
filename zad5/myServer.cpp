#include <fstream>
#include <string>
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
    int input_queue = msgget(inputK, IPC_CREAT | 0666);
    int output_queue = msgget(outputK, IPC_CREAT | 0666);

    Message msg{};

    while (true) {
        msgrcv(input_queue, &msg, sizeof(msg), 1, 0);
        std::ifstream dictionary("dictionary.txt");
        std::string translation;
        std::string wordToTranslate = msg.word;
        bool wordFound = false;
        while (dictionary >> translation) {
            std::string polishWord;
            dictionary >> polishWord;
            if (polishWord == wordToTranslate) {
                wordFound = true;
                break;
            }
        }
        msg.mtype = msg.client_pid;

        if (wordFound) {
            strcpy(msg.word, translation.c_str());
        } else {
            strcpy(msg.word, "Nie znam takiego slowa");
        }
        msgsnd(output_queue, &msg, sizeof(msg), 0);
        sleep(2);
    }

    return 0;
}

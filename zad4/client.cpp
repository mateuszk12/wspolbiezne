#include <iostream>
#include <sys/stat.h>
#include <csignal>
#include <fcntl.h>
#include <cstring>

int main() {
    std::string opt;
    std::cin >> opt;
    opt = " "+opt;
    const char *serverFifo = "serverFifo";
    const char *clientFifo = "clientFif2";
    char result[20];
    strcpy(result,clientFifo);
    strcat(result,opt.c_str());
    printf("%s\n",result);
    int stat = mkfifo(clientFifo,0666);
    if (stat<0)
    {
        printf("fifo client not created\n");
    } else {
        printf("fifo client creatd\n");
    }
    int fdS = open(serverFifo,O_WRONLY);
    write(fdS,result,13);
    close(fdS);
    while(true)
    {
        int fd = open(clientFifo,O_RDONLY);
        char str[13];
        read(fd,str,sizeof(str));
        printf("%s\n",str);
        return 0;
    }
}

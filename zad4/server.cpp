#include <iostream>
#include <sys/stat.h>
#include <csignal>
#include <fcntl.h>
#include <stdio.h>
#include <fstream>
#include <map>
#include <sstream>

void signal_handler(int signal_num)
{
    printf("interrupt: %d\n",signal_num);
}
void sigusr_handler(int signal_num)
{
    printf("interrupt: %d\n",signal_num);
    exit(1);
}
int main(int argc, char *argv[]) {
    signal(SIGTERM,signal_handler);
    signal(SIGUSR1,sigusr_handler);
    std::map<std::string,std::string> db = {{"0","Powell"},{"1","Zimmer"},{"2","Wiliams"}};
    const char *serverFifo = "serverFifo";
    int stat = mkfifo(serverFifo,0777);
    if (stat<0)
    {
        printf("fifo server not created\n");
    } else {
        printf("fifo server creatd\n");
    }
    while(true)
    {
        std::string line;
        int fd = open(serverFifo,O_RDONLY);
        char string[13];
        read(fd,string,13);
        line = string;
        printf("%s\n",line.c_str());
        std::stringstream ss(line);
        std::string adr;
        std::string id;
        ss>>adr;
        ss>>id;
        int fdC = open(adr.c_str(),O_WRONLY);
        write(fdC,db[id].c_str(),sizeof(db[id].c_str()));
        close(fd);
        sleep(2);
    }
    return 0;
}

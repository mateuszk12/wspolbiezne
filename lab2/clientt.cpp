#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
int main()
{
    std::string bufor = "./bufor";
    std::string target = "./c1/test\n";
    while (open("./lockfile",O_CREAT|O_EXCL,0)==-1) {
        printf("Serwer zajety, prosze czekac\n");
        sleep(1);
    }
    std::string text;
    std::cout << "your text: ";
    std::cin >> text;
    std::fstream file;
    file.open(bufor);
    file<<target<<text;
    file.close();
    return 0;
}

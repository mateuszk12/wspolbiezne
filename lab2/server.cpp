#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
int main()
{
    while (true)
    {
        std::fstream file;
        std::fstream clientFile;
        
        std::string line;
        std::string text;
        std::string path;
        std::string bufor = "./bufor";
        std::string lockfile = "./lockfile";
        bool wasSth = false;
        file.open(bufor);
        while (file.is_open()) {
            std::getline(file, path);
            while (std::getline(file, line)) {
                text += line;
            };
            clientFile.open(path);
            clientFile << "hello there " << text;
            clientFile.close();
            if (!std::filesystem::is_empty(bufor))
            {
                wasSth = true;
            }
            file.close();
            std::ofstream cleanFile;
            cleanFile.open(bufor,
                           std::ios::out | std::ios::trunc);
            cleanFile.close();
        }
        if (std::filesystem::exists(lockfile) && std::filesystem::is_empty(bufor) && wasSth)
            {
                std::filesystem::remove(lockfile);
                std::cout << path << "\n";
                printf("lockfile deleted\n");
            }
        sleep(1);
    }
    return 0;
}

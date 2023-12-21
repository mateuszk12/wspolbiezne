#include <iostream>
#include <fstream>
#include <string>

int main()
{
    int num;
    std::ofstream wfile;
    bool exit = false;
    std::cout << "podaj liczbę: "<<std::endl;
    std::cin >> num;
    wfile.open("./dane.txt");
    wfile<<std::to_string(num);
    wfile.close();
    while(true)
    {
        std::string line;
        std::ifstream rfile;
        rfile.open("./dane.txt");
         while (std::getline(rfile, line)) {
            if (std::to_string(num) != line)
                {
                    std::cout << line << std::endl;
                    exit = true;
                break;
                }
                
            }   
            if (exit)
            {
                break;
            }
    }
    return 0;
}
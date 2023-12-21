#include <fstream>
#include <string>
#include <unistd.h>
int main() {
    std::string prev;
    prev = "";
    while(true)
    {
        std::string line;
        std::ifstream rfile;
        rfile.open("./dane.txt");
        if (rfile.is_open()) {
            while (std::getline(rfile, line)) {
                if (prev != line)
                {
                    rfile.close();
                    std::ofstream wfile;
                    wfile.open("./dane.txt");
                    int numm = std::stoi(line) + 5;
                    wfile<<std::to_string(numm);
                    prev = std::to_string(numm);
                }
            }

        };
    }

}

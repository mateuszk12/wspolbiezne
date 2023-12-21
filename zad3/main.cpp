#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <sys/wait.h>
#include <unistd.h>

const std::string input = "\\input{";
void countWordOccurrences(const std::string &filename, const std::string &word, int& count) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            if (token == word) {
                count++;
            }
        }
        if (line.find(input) != std::string::npos) {
            size_t startPos = line.find(input) + input.length();
            size_t endPos = line.find("}");
            std::string nestedFileName = line.substr(startPos, endPos - startPos);
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                std::cerr << "Pipe failed" << std::endl;
                exit(1);
            }
            int pid = fork();
            if (pid < 0) {
                std::cerr << "Fork failed" << std::endl;
                exit(1);
            } else if (pid == 0) {
                int childCount = 0;
                countWordOccurrences(nestedFileName, word, childCount);
                close(pipefd[0]);
                write(pipefd[1], &childCount, sizeof(childCount));
                close(pipefd[1]);
                printf("%d\t%d\t%s\n",pid,childCount,nestedFileName.c_str());
                exit(0);
            } else {
                close(pipefd[1]);
                int childCount = 0;
                read(pipefd[0], &childCount, sizeof(childCount));
                close(pipefd[0]);
                waitpid(pid, NULL, 30);
                printf("%d\t%d\t%s\n",pid,childCount+count,filename.c_str());
                count += childCount;
            }
        }
    }
    file.close();
}
int main(int argc, char* argv[])
{
    std::string filename;
    std::string word;
    for (int count{0}; count < argc; count++) {
        if (strcmp(argv[count], "-p") == 0) {
            filename = argv[count + 1];
        }
        if (strcmp(argv[count], "-s") == 0) {
            word = argv[count + 1];
        }
    }
    int count = 0;
    int& refCount = count;
    countWordOccurrences(filename, word,refCount);
    std::cout << "Occurrences of '" << word << "': " << count << std::endl;
    return 0;
}
#include <iostream>
#include <mutex>
#include <cmath>
#include <vector>
#include <thread>
#include <condition_variable>
#include <csignal>

std::mutex save_mutex;
std::mutex ready_mutex;
void generatelist(int b, int e, std::mutex *mtx,std::vector<long>* result) {
    std::vector<int> primeNumbers;
    bool isPrime = true;

    for (int i = b; i <= e; i++) {
        if (i < 2) {

            continue;
        }
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            std::lock_guard<std::mutex> lock(*mtx);
            result->push_back(i);
        }
        isPrime = true;
    }
    std::lock_guard<std::mutex> lock(ready_mutex);
}

int main() {
    std::vector<std::thread> listOfThreads;
    std::vector<long> result;
    int nOfThreds = 5;
    int num = 100;
    int start = 40;
    unsigned long inc = num/ nOfThreds;
    for (unsigned long i = start; i < num; i += inc)
    {
        unsigned long int b = i;
        unsigned long long int e = i + inc;
        if (i + 2 * inc)
            listOfThreads.push_back(std::thread(generatelist,b,e,&save_mutex,&result));
    }
    for (auto &listOfThread: listOfThreads)
    {
        listOfThread.join();
    }
    for (auto i : result)
    {
        std::cout << i << " ";
    }
    return 0;
}

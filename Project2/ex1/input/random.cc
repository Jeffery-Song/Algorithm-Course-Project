#include <iostream>
#include <fstream>
#define num 31
int main() {
    std::ofstream f;
    f.open("input.txt", std::ios::out);
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        int number = rand() % 32 + 1;
        f << number << std::endl;
    }
    f.close();
    return 0;
}
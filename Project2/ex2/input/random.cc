#include <iostream>
#include <fstream>
#define num 120
int main() {
    std::ofstream f;
    f.open("input.txt", std::ios::out);
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        double number = rand() % 200 - 100;
        number += (rand() % 10) / 10.0;
        f << number << std::endl;
    }
    f.close();
    return 0;
}
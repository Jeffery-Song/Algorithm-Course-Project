#include <iostream>
#include <fstream>
#define num 0x20000
int main() {
    std::ofstream f;
    f.open("input_string.txt", std::ios::out);
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        int size = rand() % 32 + 1;
        for (int j = 0; j < size; j++) {
            f << (char)('a' + rand() % 26);
        }
        f << '\n';
    }
    f.close();
    return 0;
}
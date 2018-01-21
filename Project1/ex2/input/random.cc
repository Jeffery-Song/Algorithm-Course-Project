#include <iostream>
#include <fstream>
#define num 0x20000
int main() {
    std::ofstream f;
    f.open("input_string.txt", std::ios::out);
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        int rst = rand() & 0xffff;
        if (!rst) {
            i--;
            continue;
        }
        f << rst << '\n';
    }
    f.close();
    return 0;
}
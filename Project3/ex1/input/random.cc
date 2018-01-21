#include <iostream>
#include <fstream>
#define num 60
int main() {
    bool array[256] = {false};
    std::ofstream f;
    f.open("input.txt", std::ios::out);
    srand((unsigned)time(NULL));
    for (int i = 0; i < num; i++) {
        int number = rand() % 256;
        while (array[number]) number = rand() % 256;
        array[number] = true;
        f << number << std::endl;
    }
    f.close();
    return 0;
}

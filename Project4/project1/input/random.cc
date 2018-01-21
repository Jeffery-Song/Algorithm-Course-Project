#include <iostream>
#include <fstream>
#include <array>
#include <string>
#define vertex_size (1 << (in_size + 2))
int main() {
    //int number = 1 << (size + 2);
    std::array<std::array<bool, vertex_size>, vertex_size> edges = { {false} };
    std::ofstream f;
    f.open("size" + std::to_string(in_size) + "/input.txt", std::ios::out);
    srand((unsigned)time(NULL));
    int edge_size = vertex_size * (in_size + 2);
    for (int i = 0; i < edge_size; i++) {
        int a = rand() % vertex_size;
        int b = rand() % vertex_size;
        while (a == b || edges[a][b] == true) {
            a = rand() % vertex_size;
            b = rand() % vertex_size;
        }
        edges[a][b] = true;
        f << a << ' ' << b << std::endl;
    }
    f.close();
    return 0;
}

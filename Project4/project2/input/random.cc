#include <iostream>
#include <fstream>
#include <array>
#include <string>
#define vertex_size (1 << (in_size + 2))
int main() {
    //int number = 1 << (size + 2);
    //std::array<std::array<bool, vertex_size>, vertex_size> edges = { {false} };
    bool connected[vertex_size][vertex_size] = {{false}};
    int edges[vertex_size][vertex_size];
    std::ofstream f;
    f.open("size" + std::to_string(in_size) + "/input.txt", std::ios::out);
    srand((unsigned)time(NULL));
    int log_vertex_size = in_size + 2;
    int edge_size = vertex_size * log_vertex_size;
    for (int i = 0; i < log_vertex_size; i++) {
        int a = rand() % vertex_size;
        int b = rand() % vertex_size;
        while (a == b || connected[a][b] == true) {
            a = rand() % vertex_size;
            b = rand() % vertex_size;
        }
        connected[a][b] = true;
        edges[a][b] = rand() % log_vertex_size - log_vertex_size;
        f << a << ' ' << b << ' ' << edges[a][b] << std::endl;
    }
    for (int i = log_vertex_size; i < edge_size; i++) {
        int a = rand() % vertex_size;
        int b = rand() % vertex_size;
        while (a == b || connected[a][b] == true) {
            a = rand() % vertex_size;
            b = rand() % vertex_size;
        }
        connected[a][b] = true;
        edges[a][b] = rand() % vertex_size + 1;
        f << a << ' ' << b << ' ' << edges[a][b] << std::endl;
    }
    f.close();
    return 0;
}

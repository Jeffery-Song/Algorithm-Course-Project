#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <set>
#include <chrono>
//#define in_size 1
#define vertex_size (1 << (in_size + 2))
#define max_finish_time ((vertex_size << 1) + 1)
enum Color_e {WHITE = 0, GRAY, BLACK};
typedef bool Graph[vertex_size][vertex_size];
typedef std::array<unsigned int, vertex_size> Time;
typedef Color_e Color[vertex_size];
typedef int Node_List[vertex_size];
//typedef std::array<std::array<bool, vertex_size>, vertex_size> Graph;
//typedef std::array<unsigned int, vertex_size> Time;
//typedef std::array<Color_e, vertex_size> Color;
//typedef std::array<int, vertex_size> Node_List;
typedef int Vertex;
void DFS_visit(Graph &G, Vertex u, int& time, Time& finish_time, Color& colors) {
    time++;
    colors[u] = GRAY;
    for (Vertex v = 0; v < vertex_size; v++) {
        if (G[u][v]) {
            if (colors[v] == WHITE) {
                DFS_visit(G, v, time, finish_time, colors);
            }
        }
    }
    colors[u] = BLACK;
    time++;
    finish_time[u] = time;
}
Time DFS_finish(Graph &G) {
    Color colors;
    Time finish_time;
    for (int i = 0; i < vertex_size; i++) {
        colors[i] = WHITE;
        finish_time[i] = 0;
    }
    int time = 0;
    for (Vertex u = 0; u < vertex_size; u++) {
        if (colors[u] == WHITE) {
            DFS_visit(G, u, time, finish_time, colors);
        }
    }
    return finish_time;
}
void DFS_visit(Graph &G, Vertex u, Color& colors, std::set<Vertex>& block) {
    colors[u] = GRAY;
    for (Vertex v = 0; v < vertex_size; v++) {
        if (G[u][v]) {
            if (colors[v] == WHITE) {
                block.insert(v);
                DFS_visit(G, v, colors, block);
            }
        }
    }
    colors[u] = BLACK;
}
std::vector<std::set<Vertex>> DFS(Graph& G, Node_List& list) {
    Color colors;
    std::vector<std::set<Vertex>> blocks;
    for (int i = 0; i < vertex_size; i++) {
        colors[i] = WHITE;
    }
    for (int i = 0; i < vertex_size; i++) {
        Vertex u = list[i];
        if (colors[u] == WHITE) {
            std::set<Vertex> block;
            block.insert(u);
            DFS_visit(G, u, colors, block);
            blocks.push_back(block);
        }
    }
    return blocks;
}
int main() {
    Graph G = {{false}};
    std::fstream input, print, output, time;
    input.open("../input/size" + std::to_string(in_size) + "/input.txt", std::ios_base::in);
    print.open("../output/size" + std::to_string(in_size) + "/g.gv", std::ios_base::out);
    time.open("../output/size" + std::to_string(in_size) + "/time1.txt", std::ios_base::out);
    print << "digraph G {\n";
    Vertex u, v;
    while (input >> u >> v) {
        G[u][v] = true;
        print << "    " << std::to_string(u) << " -> " << std::to_string(v) << ";\n";
    }
    print << '}';
    print.close();
    //std::array<, vertex_size> f, d;
    Graph GT;
    for (int i = 0; i < vertex_size; i++) {
        for (int j = 0; j < vertex_size; j++) {
            GT[i][j] = G[j][i];
        }
    }
    unsigned int C[max_finish_time] = {0};
    auto start = std::chrono::system_clock::now();
    Time f = std::move(DFS_finish(G));
    Node_List nodes_by_decrease_f;
    for (Vertex u = 0; u < vertex_size; u++) {
        C[f[u]]++;
    }
    for (int i = max_finish_time - 2; i >= 0; i--) {
        C[i] += C[i + 1];
    }
    for (Vertex u = 0; u < vertex_size; u++) {
        nodes_by_decrease_f[C[f[u]] - 1] = u;
        // 2 vertexs' finish_time can't be the same
    }
    std::vector<std::set<Vertex>> blocks(std::move(DFS(GT, nodes_by_decrease_f)));
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time << "total: " << double(duration.count()) * std::chrono::nanoseconds::period::num;
    output.open("../output/size" + std::to_string(in_size) + "/output1.txt", std::ios_base::out);
    print.open("../output/size" + std::to_string(in_size) + "/sub.gv", std::ios_base::out);
    print << "digraph G {" << std::endl;
    int i = 0;
    for (auto& block : blocks) {
        output << '(';
        print << "    subgraph cluster" << i << " {" << std::endl;
        for (Vertex u : block) {
            output << u << "  ";
            print << "        " << u << ";" << std::endl;
            for (Vertex v : block) {
                if (G[u][v]) {
                    print << "        " << u << " -> " << v << ";" << std::endl;
                }
            }
        }
        print << "    }" << std::endl;
        i++;
        output << ")  ";
    }
    i = 0;
    for (auto& block_u : blocks) {
        i++;
        int j = 0;
        for (auto& block_v : blocks) {
            j++;
            if (i == j) {
                continue;
            }
            for (Vertex u : block_u) {
                for (Vertex v : block_v) {
                    if (G[u][v]) {
                        print << "    " << u << " -> " << v << ";" << std::endl;
                    }
                }
            }
        }
    }
    print << "}";
    output.close();
    print.close();
    time.close();
}
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <set>
#include <chrono>
//#define in_size 1
#define vertex_size (1 << (in_size + 2))
#define vertex_size_1 ((1 << (in_size + 2)) + 1)
typedef int Graph[vertex_size][vertex_size];
typedef int Graph_1[vertex_size_1][vertex_size_1];
typedef int Node_List[vertex_size];
typedef int Node_List_1[vertex_size_1];
typedef int Vertex;

bool bellman_ford(Graph_1 G, Vertex s, Node_List_1& d) {
    for (int i = 0; i < vertex_size_1; i++) {
        d[i] = INT32_MAX;
    }
    d[s] = 0;
    for (int i = 1; i < vertex_size_1; i++) {
        for (Vertex u = 0; u < vertex_size_1; u++) {
            for (Vertex v = 0; v < vertex_size_1; v++) {
                if (G[u][v] == INT32_MAX) continue;
                if (d[u] == INT32_MAX) continue;
                if (d[v] > d[u] + G[u][v]) {
                    d[v] = d[u] + G[u][v];
                }
            }
        }
    }
    for (Vertex u = 0; u < vertex_size_1; u++) {
        for (Vertex v = 0; v < vertex_size_1; v++) {
            if (G[u][v] == INT32_MAX) continue;
            if (d[u] == INT32_MAX) continue;
            if (d[u] != INT32_MAX && v[d] == INT32_MAX || d[u] + G[u][v] < d[v]) return false;
        }
    }
    return true;
}

class Heap {
public:
    Heap(Vertex s) {
        for (int i = 0; i < vertex_size; i++) {
            d[i] = INT32_MAX;
            Vertexs[i] = i;
            index[i] = i;
        }
        d[s] = 0;
        Vertexs[0] = s;
        Vertexs[s] = 0;
        index[s] = 0;
        index[0] = s;
        size = vertex_size;
    }
    inline Vertex parent (Vertex u) {
        return (u - 1) >> 1;
    }
    inline Vertex left (Vertex u) {
        return (u << 1) + 1;
    }
    inline Vertex right (Vertex u) {
        return (u + 1) << 1;
    }
    void min_heapify(Vertex i) {
        int max_parent = (size >> 1) - 1;
        while (i <= max_parent) {
            int min = i;
            if (d[Vertexs[min]] > d[Vertexs[left(i)]]) {
                min = left(i);
            }
            if (right(i) < size && d[Vertexs[min]] > d[Vertexs[right(i)]]) {
                min = right(i);
            }
            if (min == i) break;
            Vertex t = Vertexs[min];
            Vertexs[min] = Vertexs[i];
            Vertexs[i] = t;
            index[t] = i;
            index[Vertexs[min]] = min;
            i = min;
        }
    }
    Vertex extract_min() {
        size--;
        Vertex t = Vertexs[size];
        Vertexs[size] = Vertexs[0];
        Vertexs[0] = t;
        index[t] = 0;
        index[Vertexs[size]] = size;
        min_heapify(0);
        return Vertexs[size];
    }
    // a vertex u, Vertex[i] = u, d[u] = u.d
    // index[Vertexs[i]] = i
    // Vertexs[index[u]] = u
    void decrease(Vertex u, int k) {
        d[u] = k;
        int i = index[u];
        while (i > 0 && d[Vertexs[parent(i)]] > d[u]) {
            int t = Vertexs[parent(i)];
            Vertexs[parent(i)] = u;
            Vertexs[index[u]] = t;
            index[t] = index[u];
            index[u] = parent(i);
            i = index[u];
        }
    }
    Node_List Vertexs;
    Node_List d;
    Node_List index;
    int size;
};

bool dijkstra(Graph G, Vertex s, Node_List& precursor) {
    bool S[vertex_size] = {false};
    Heap H(s);
    while (H.size > 0) {
        Vertex u = H.extract_min();
        S[u] = true;
        if (H.d[u] == INT32_MAX) {
            return false;
        }
        for (Vertex v = 0; v < vertex_size; v++) {
            if (S[v]) continue;
            if (G[u][v] == INT32_MAX) continue;
            if (H.d[v] > H.d[u] + G[u][v]) {
                H.decrease(v, H.d[u] + G[u][v]);
                precursor[v] = u;
            }
        }
    }
    precursor[s] = s;
    return true;
}

std::string recursive_path(Vertex u, Vertex s, Node_List &precursor, int &distance, Graph_1 &G) {
    static std::string str[vertex_size][vertex_size];
    static int distances[vertex_size][vertex_size];
    if (str[s][u].size() == 0) {

        if (u == precursor[u]) {
            str[s][u] = std::to_string(u);
            distances[s][u] = 0;

        } else {
            str[s][u] = recursive_path(precursor[u], s, precursor, distance, G) + ", " + std::to_string(u);
            distances[s][u] = distances[s][precursor[u]] + G[precursor[u]][u];
        }
    }
    distance = distances[s][u];
    return str[s][u];
}

int main() {
    std::fstream input, print, output, time;
    input.open("../input/size" + std::to_string(in_size) + "/input.txt", std::ios_base::in);
    print.open("../output/size" + std::to_string(in_size) + "/g.gv", std::ios_base::out);
    time.open("../output/size" + std::to_string(in_size) + "/time2.txt", std::ios_base::out);
    Graph G;
    print << "digraph G {" << std::endl;
    Graph_1 G1;
    for (int i = 0; i < vertex_size; i++) {
        int j = 0;
        for (; j < vertex_size; j++) {
            G[i][j] = G1[i][j] = INT32_MAX;
        }
        G1[i][vertex_size] = INT32_MAX;
    }
    for (int i = 0; i < vertex_size; i++) {
        G1[vertex_size][i] = 0;
    }
    G1[vertex_size][vertex_size] = INT32_MAX;
    Vertex u, v;
    while (input >> u) {
        input >> v;
        int weight;
        input >> weight;
        G[u][v] = G1[u][v] = weight;
        print << "    " << u << " -> " << v << " [label = " << weight << "];" << std::endl;
    }
    print << "}";
    print.close();
    Node_List_1 h;

    auto start = std::chrono::system_clock::now();
    if (!bellman_ford(G1, vertex_size, h)) {
        std::cerr << "negative weight cycle detected" << std::endl;
        return 0;
    }
    for (Vertex u = 0; u < vertex_size; u++) {
        for (Vertex v = 0; v < vertex_size; v++) {
            if (G[u][v] == INT32_MAX) {
            } else {
                G[u][v] += h[u] - h[v];
            }
        }
    }
    Node_List precursors[vertex_size];
    for (Vertex u = 0; u < vertex_size; u++) {
        if (!dijkstra(G, u, precursors[u])) {
            std::cerr << "unconnected graph" << std::endl;
        }
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time << "total: " << double(duration.count()) * std::chrono::nanoseconds::period::num;
    output.open("../output/size" + std::to_string(in_size) + "/output2.txt", std::ios_base::out);
    for (Vertex u = 0; u < vertex_size; u++) {
        for (Vertex u1 = 0; u1 < vertex_size; u1++) {
            int distance = 0;
            output << u << " -> " << u1 << " : {" << recursive_path(u1, u, precursors[u], distance, G1) << "} = ";
            output << distance << std::endl;
        }
    }
    if (in_size == 1 | in_size == 2) {
        for (Vertex u = 0; u < vertex_size; u++) {
            print.open("../output/size" + std::to_string(in_size) + "/start" + std::to_string(u) + ".gv", std::ios_base::out);
            print << "digraph G {" << std::endl;
            print << "    " << u << "[style = diagonals];" << std::endl;
            for (Vertex u1 = 0; u1 < vertex_size; u1++) {
                for (Vertex v = 0; v < vertex_size; v++) {
                    if (G[u1][v] == INT32_MAX) continue;
                    print << "    " << u1 << " -> " << v << " [label = " << G1[u1][v] << "]";
                    if (precursors[u][v] == u1) {
                        print << " [style = bold][color = red]";
                    }
                    print << ";" << std::endl;
                }
            }
            print << "}";
            print.close();
            system(("dot -Tpng ../output/size" + std::to_string(in_size) + "/start" + std::to_string(u) + ".gv -o ../output/size" + std::to_string(in_size) + "/start" + std::to_string(u) + ".png").c_str());
        }
    }

    if (in_size == 1) {
        for (int i = 0; i < vertex_size; i++) {
            std::cout << h[i] << "  ";
        }
        std::cout << std::endl;
        Vertex u = 0;
        print.open("../output/size" + std::to_string(in_size) + "/test_start" + std::to_string(u) + ".gv", std::ios_base::out);
        print << "digraph G {" << std::endl;
        print << "    " << u << "[style = diagonals];" << std::endl;
        for (Vertex u1 = 0; u1 < vertex_size; u1++) {
            for (Vertex v = 0; v < vertex_size; v++) {
                if (G[u1][v] == INT32_MAX) continue;
                print << "    " << u1 << " -> " << v << " [label = " << G[u1][v] << "]";
                if (precursors[u][v] == u1) {
                    print << " [style = bold][color = red]";
                }
                print << ";" << std::endl;
            }
        }
        print << "}";
        print.close();
        system(("dot -Tpng ../output/size" + std::to_string(in_size) + "/test_start" + std::to_string(u) + ".gv -o ../output/size" + std::to_string(in_size) + "/test_start" + std::to_string(u) + ".png").c_str());

        
    }

    input.close();
    output.close();
    time.close();
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>

void count_sort(int* A, int* B) {
    int C[65536];
    for (int i = 0; i < 65536; i++) {
        C[i] = 0;
    }
    for (int i = 0; i < number; i++) {
        C[A[i]]++;
    }
    for (int i = 1; i < 65536; i++) {
        C[i] += C[i - 1];
    }
    for (int j = number - 1; j >= 0; j--) {
        C[A[j]]--;
        B[C[A[j]]] = A[j];
    }
}

int main() {
    std::fstream f;
    f.open("../input/input_string.txt");
    int s[number], B[number];
    for (int i = 0; i < number; i++) {
        f >> s[i];
    }
    f.close();

    auto start = std::chrono::system_clock::now();

    count_sort(s, B);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/count_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << B[i] << '\n';
    }
    f.close();
    return 0;
}
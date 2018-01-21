#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>

int partition(int* A, int p, int r) {
    int i = p;
    for (int j = p; j < r; j++) {
        if (A[j] <= A[r]) {
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++;
        }
    }
    int tmp = A[i];
    A[i] = A[r];
    A[r] = tmp;
    return i;
}

void quick_sort(int* A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}


int main() {
    std::fstream f;
    f.open("../input/input_string.txt");
    int s[number];
    for (int i = 0; i < number; i++) {
        f >> s[i];
    }
    f.close();

    auto start = std::chrono::system_clock::now();

    quick_sort(s, 0, number - 1);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/quick_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << s[i] << '\n';
    }
    f.close();
    return 0;
}
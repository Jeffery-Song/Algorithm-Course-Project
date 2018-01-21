#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#define bits_step 4
#define max_number (1<<bits_step)

void count_sort(int* A, int* B, int bitoffset) {
    int C[max_number];
    for (int i = 0; i < max_number; i++) {
        C[i] = 0;
    }
    for (int i = 0; i < number; i++) {
        C[(A[i] >> bitoffset) & (max_number - 1)]++;
    }
    for (int i = 1; i < max_number; i++) {
        C[i] += C[i - 1];
    }
    if (bitoffset == 0) {
        for (int i = 0; i < number; i++) {
            B[i] = 0;
        }
    }
    for (int i = number - 1; i >= 0; i--) {
        C[(A[i] >> bitoffset) & (max_number - 1)]--;
        B[C[(A[i] >> bitoffset) & (max_number - 1)]] = A[i];
    }
}

int* base_sort(int* A , int* B) {
    int bitoffset = 0;
    int *orig = A, *result = B;
    for (; bitoffset < 16; bitoffset += bits_step) {
        count_sort(orig, result, bitoffset);
        int *tmp = orig;
        orig = result;
        result = tmp;
    }
    return orig;
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

    int* result = base_sort(s, B);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/base_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f <<result[i] << '\n';
    }
    f.close();
    return 0;
}
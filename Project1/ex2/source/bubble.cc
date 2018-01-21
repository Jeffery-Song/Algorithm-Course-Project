#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>

void bubble_sort(int* A) {
    for (int i = number - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (A[j] > A[j + 1]) {
                int tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
            }
        }
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

    bubble_sort(s);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/bubble_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << s[i] << '\n';
    }
    f.close();
    return 0;
}
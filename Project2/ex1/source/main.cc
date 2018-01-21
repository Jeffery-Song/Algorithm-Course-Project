#include <iostream>
#include <fstream>
#include <chrono>
void print(std::ofstream &f, const int s[][number], int i = 0, int j = number - 1) {
    if (i == j) {
        f << 'A' << i + 1;
    } else {
        f << '(';
        print(f, s, i, s[i][j]);
        f << ',';
        print(f, s, s[i][j] + 1, j);
        f << ')';
    }
}
int main() {
    std::ifstream f;
    std::ofstream outf;
    std::ofstream timef;
    f.open("../input/input.txt", std::ios_base::in);
    if (number == 5) {
        outf.open("../output/result.txt", std::ios_base::out);
        timef.open("../output/time.txt", std::ios_base::out);
    } else {
        outf.open("../output/result.txt", std::ios_base::out | std::ios_base::app);
        timef.open("../output/time.txt", std::ios_base::out | std::ios_base::app);
    }
    int p[number + 1];
    int m[number][number];
    int s[number][number]; 
    //int** m = new int* [number];
    //int** s = new int* [number];
    for (int i = 0; i < number; i++) {
        //m[i] = new int [number];
        m[i][i] = 0;
        f >> p[i];
    } 
    f >> p[number];
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    
    for (int l = 2; l <= number; l++) {
        for (int i = 0; i <= number - l; i++) {
            int j = i + l - 1;
            m[i][j] = INT32_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::nanoseconds::period::num;
    timef << number << "\t: " << time_cost << std::endl;
    outf << number << "\t: ";
    print(outf, s);
    outf << std::endl;
    f.close();
    outf.close();
    timef.close();
    return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
int lenstr(char* s) {
    int i = 0;
    for (; i < 33 && s[i]; i++);
    return i;
}
int cmpstr(char* s1, char* s2) {
    int i = 0;
    int l1 = lenstr(s1), l2 = lenstr(s2);
    if (l1 > l2) return 1;
    if (l1 < l2) return -1;
    for (i = 0; s1[i] == s2[i] && s1[i] != '\0'; i++);
    if (s1[i] < s2[i]) return -1;
    if (s1[i] > s2[i]) return 1;
    return 0;
}

int partition(char**A, int p, int r) {
    int i = p;
    for (int j = p; j < r; j++) {
        if (cmpstr(A[j], A[r]) <= 0) {
            char* tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            i++;
        }
    }
    char* tmp = A[i];
    A[i] = A[r];
    A[r] = tmp;
    return i;
}

void quick_sort(char** A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}


int main() {
    std::fstream f;
    f.open("../input/input_string.txt");
    char s[number][33];
    char* result[number];
    // get string from file and set a pointer array to avoid too many strcpy
    for (int i = 0; i < number; i++) {
        f >> s[i];
        result[i] = &s[i][0];
    }
    f.close();

    auto start = std::chrono::system_clock::now();
    /*======================== sort body ============================*/
    quick_sort(result, 0, number - 1);    
    /*======================== sort end ============================*/
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    // print result to output file
    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/quick_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << result[i] << '\n';
    }
    f.close();
    return 0;
}
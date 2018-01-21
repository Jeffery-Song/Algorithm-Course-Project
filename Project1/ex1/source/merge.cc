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
void merge(char** A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    char** L = (char**)malloc(sizeof(char*) * n1);
    char** R = (char**)malloc(sizeof(char*) * n2);
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = A[q + i + 1];
    }
    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        // if one in L R reaches its end, then fill rest of A directly 
        if (i >= n1) {
            for (; j < n2; j++) {
                A[k] = R[j];
                k++;
            }
            break;
        } else if (j >= n2) {
            for (; i < n1; i++) {
                A[k] = L[i];
                k++;
            }
            break;
        } else if (cmpstr(L[i], R[j]) <= 0) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
    free(L);
    free(R);
}
void merge_sort(char** A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
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
    /* =========================== sort body ==================== */
    merge_sort(result, 0, number - 1);
    /* =========================== sort end ==================== */
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    // print result to output file
    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/merge_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << result[i] << '\n';
    }
    f.close();
    return 0;
}
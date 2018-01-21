#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#define parent(i) ((i - 1) / 2)
#define left(i) (2 * i + 1)
#define right(i) (2 * (i + 1))

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
// directly write from false C
void max_heapify(char** A, int i, int heapsize) {
    // move down ith element till it becomes leaf
    while (i < heapsize / 2) {
        int l = left(i), r = right(i);
        int largest = i;
        if (l < heapsize && cmpstr(A[l], A[i]) > 0) {
            largest = l;
        }
        if (r < heapsize && cmpstr(A[r], A[largest]) > 0) {
            largest = r;
        }
        if (largest != i) {
            char* tmp = A[i];
            A[i] = A[largest];
            A[largest] = tmp;
            i = largest;
        } else {
            break;
        }
    }
}

void build_max_heap(char** A, int heapsize) {
    // from the last non-leaf element to top, make A a heap
    for (int i = heapsize / 2 - 1; i >= 0; i--) {
        max_heapify(A, i, heapsize);
    }
}

void heapsort(char** A, int heapsize) {
    build_max_heap(A, heapsize);
    for (int i = heapsize - 1; i > 0; i--) {
        char* tmp = A[i];
        A[i] = A[0];
        A[0] = tmp;
        heapsize--;
        max_heapify(A, 0, heapsize);
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
    heapsort(result, number);
    /* =========================== sort end ==================== */
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    // print result to output file
    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/heap_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << result[i] << '\n';
    }
    f.close();
    return 0;
}
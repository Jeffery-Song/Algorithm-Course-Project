#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
int lenstr(char* s) {
    int i = 0;
    for (; i < 32 && s[i]; i++);
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
int main() {
    std::fstream f;
    f.open("../input/input_string.txt");
    char s[number][33];
    char* result[number];
    // get string from file and set a pointer array to avoid too many strcpy
    for (int i = 0; i < number; i++) {
        f >> s[i];
    }
    f.close();

    auto start = std::chrono::system_clock::now();
    /*======================== sort body ============================*/
    result[0] = &s[0][0];
    for (int i = 1; i < number; i++) {
        int j = i - 1;
        for (j = i - 1; j >= 0 && cmpstr(result[j], s[i]) > 0; j--) result[j + 1] = result[j];
        result[j + 1] = &s[i][0];
    }
    /*======================== sort end =============================*/
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
    std::cout << "time:" << time_cost << std::endl;

    std::stringstream tmp;
    tmp << number;
    std::string filename = "../output/insert_sort/result_" + tmp.str() + ".txt";
    f.open(filename, std::ios::out);
    for (int i = 0; i < number; i++) {
        f << result[i] << '\n';
    }
    f.close();
    return 0;
}
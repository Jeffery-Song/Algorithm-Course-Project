#include <iostream>
#include <fstream>
#include <array>
template <typename V>
int random_partition(V* A, int p, int r) {
    srand((unsigned)time(NULL));
    int i = rand() % (r - p);
    V tmp = A[p + i];
    A[p + i] = A[r];
    A[r] = tmp;
    i = p - 1;
    V t;
    for (int j = p; j < r; j++) {
        if (A[j] <= tmp) {
            i++;
            t = A[i];
            A[i] = A[j];
            A[j] = t;
        }
    }
    tmp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tmp;
    return i + 1;
}
template<typename V>
V random_select(V* A, int p, int r, int i) {
    if (p == r) {
        return A[p];
    }
    int q = random_partition(A, p, r);
    int k = q - p + 1;
    if (i == k) {
        return A[q];
    } else if (i < k) {
        return random_select(A, p, q - 1, i);
    } else {
        return random_select(A, q + 1, r, i - k);
    }
}
int main() {
    int A[number];
    std::fstream f, delete_data;
    f.open("../input/input.txt", std::ios_base::in);
    delete_data.open("../output/size" + std::to_string(number) + "/delete_data_select.txt", std::ios_base::out);
    for (int i = 0; i < number; i++) {
        f >> A[i];
    }
    delete_data << "A[number / 3] = A[" << number << " / 3] = A[" << number / 3 << "] = " << random_select(A, 0, number - 1, number / 3) << std::endl;
    A[number / 3] = INT32_MAX;
    delete_data << "set number / 3 to INT32_MAX, so when search for i-th small value, it acts like the number has been deleted\n";
    delete_data << "A[number / 4] = A[" << number - 1 << " / 4] = A[" << (number - 1) / 4 << "] = " << random_select(A, 0, number - 1, (number - 1) / 4) << std::endl;
    f.close();
}
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#define PI 3.1415926535898
typedef struct cmplx {
    double r, v;
    cmplx() {
        r = 0;
        v = 0;
    }
    cmplx(double a) {
        r = a;
        v = 0;
    }
    cmplx(double r, double v) {
        this->r = r;
        this->v = v;
    }
    cmplx(const cmplx &x) {
        this->r = x.r;
        this->v = x.v;
    }
    cmplx(cmplx &&x) {
        this->r = x.r; 
        this->v = x.v;
    }
    friend cmplx operator*(const cmplx &x, const cmplx &y) {
        cmplx r;
        r.r = x.r * y.r - x.v * y.v;
        r.v = x.r * y.v + x.v * y.r;
        return r;
    }
    friend cmplx operator+(const cmplx &x, const cmplx &y) {
        cmplx r(x.r + y.r, x.v + y.v);
        return r;
    }
    friend cmplx operator-(const cmplx &x, const cmplx &y) {
        cmplx r(x.r - y.r, x.v - y.v);
        return r;
    }
    cmplx& operator=(const cmplx &x) {
        this->r = x.r;
        this->v = x.v;
        return *this;
    }
    cmplx& operator=(cmplx &&x) {
        this->r = x.r;
        this->v = x.v;
        return *this;
    }
} cmplx;

cmplx* recursive_fft(cmplx* a, int size) {
    if (size == 1) {
        cmplx* ret = new cmplx;
        ret->r = a->r;
        ret->v = a->v;
        return ret;
    }
    cmplx wn(cos(2 * PI / size), sin(2 * PI / size)), w(1);
    cmplx* a0 = new cmplx [size / 2];
    cmplx* a1 = new cmplx [size / 2];
    int j = 0;
    for (int i = 0; i < size; i += 2) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
        j++;
    }
    cmplx* y0 = recursive_fft(a0, j);
    cmplx* y1 = recursive_fft(a1, j);
    cmplx* y = new cmplx [size];
    for (int k = 0; k < j; k++) {
        y[k] = y0[k] + w * y1[k];
        y[k + j] = y0[k] - w * y1[k];
        w = w * wn;
    }
    delete [] y0;
    delete [] y1;
    delete [] a0;
    delete [] a1;
    return y;
}

cmplx* de_fft(cmplx* y, int size) {
    if (size == 1) {
        cmplx* ret = new cmplx;
        ret->r = y->r;
        ret->v = y->v;
        return ret;
    }
    cmplx wn(cos(-2 * PI / size), sin(-2 * PI / size)), w(1);
    cmplx* y0 = new cmplx [size / 2];
    cmplx* y1 = new cmplx [size / 2];
    int j = 0;
    for (int i = 0; i < size; i += 2) {
        y0[j] = y[i];
        y1[j] = y[i + 1];
        j++;
    }
    cmplx* a0 = de_fft(y0, j);
    cmplx* a1 = de_fft(y1, j);
    cmplx* a = new cmplx [size];
    for (int k = 0; k < j; k++) {
        a[k] = a0[k] + w * a1[k];
        a[k + j] = a0[k] - w * a1[k];
        w = w * wn;
    }
    delete [] y0;
    delete [] y1;
    delete [] a0;
    delete [] a1;
    return a;
}

int main() {
    std::ifstream inputf;
    std::ofstream outf;
    std::ofstream outf_orig;
    std::ofstream timef;
    std::ofstream timef_orig;
    inputf.open( "../input/input.txt", std::ios_base::in);
    if (number == 4) {
        outf.open("../output/result.txt", std::ios_base::out);
        timef.open("../output/time.txt", std::ios_base::out);
        outf_orig.open("../output/result_orig.txt", std::ios_base::out);
        timef_orig.open("../output/time_orig.txt", std::ios_base::out);
    } else {
        outf.open("../output/result.txt", std::ios_base::out | std::ios_base::app);
        timef.open("../output/time.txt", std::ios_base::out | std::ios_base::app);
        outf_orig.open("../output/result_orig.txt", std::ios_base::out | std::ios_base::app);
        timef_orig.open("../output/time_orig.txt", std::ios_base::out | std::ios_base::app);
    }
    cmplx a[128], b[128];
    for (int i = 0; i < number; i++) {
        inputf >> a[i].r >> b[i].r;
        a[i].v = 0;
        b[i].v = 0;
    }
    int n = 1;
    while (n < number) n = n << 1;
    n = n << 1;
    for (int i = number; i < n; i++) {
        a[i].v = 0;
        a[i].r = 0;
        b[i].v = 0;
        b[i].r = 0;
    }


    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    cmplx* A = recursive_fft(a, n);
    cmplx* B = recursive_fft(b, n);
    for (int i = 0; i < n; i++) {
        A[i] = A[i] * B[i];
    }
    delete [] B;
    cmplx* rst = de_fft(A, n);


    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto time_cost = double(duration.count()) * std::chrono::nanoseconds::period::num;
    timef << number << "\t: " << time_cost << std::endl;

    double orig[128] = {0};

    start = std::chrono::system_clock::now();

    for (int i = 0; i < 2 * number; i++) {
        for (int j = 0; j <= i; j++) {
            orig[i] += a[j].r * b[i - j].r;
        }
    }

    end = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    time_cost = double(duration.count()) * std::chrono::nanoseconds::period::num;
    timef_orig << number << "\t: " << time_cost << std::endl;


    outf << number << "\t: (";
    outf_orig << number << "\t: (";
    for (int i = 0; i < n; i++) {
        rst[i].r = rst[i].r / n;
        rst[i].v = rst[i].v / n;
        if (i) {
            outf << ", ";
            outf_orig << ", ";
        }
        outf << rst[i].r;
        outf_orig << orig[i];
        //std::cout << "+(" << rst[i].r << '+' << rst[i].v << "i)*x^" << i;
    }
    //std::cout << std::endl;
    outf << ')' << std::endl;
    outf_orig << ')' << std::endl;
    delete [] A;
    delete [] rst;
    return 0;
}
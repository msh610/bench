#include <iostream>
#include <chrono>
#include <random>
#include "func.hpp"

using namespace std;

#define N (1024*512)
#define ALPHA (4)
uint16_t A[N];
uint16_t B[N];
uint16_t C[N];
uint16_t C_V[N];
volatile uint16_t clear[N];

int cache_clean() {
    int ret = 0; 
    for (size_t i = 0; i < N; i++) {
        ret+=clear[i];
    }
    return ret;
}

void init_mat(uint16_t a[], uint16_t b[], uint16_t c[], const size_t n){
    std::mt19937 mt(0);
    std::uniform_int_distribution<> rand10(0, 9);
     for (size_t i = 0; i < n; i++) {
        a[i] = rand10(mt);
        b[i] = rand10(mt);
     }
}

template <typename T>
size_t check(T a[], T b[], size_t n) {
    int unmatch_counter = 0;
    for (size_t i = 0; i < n; i++) {
        unmatch_counter += (a[i] != b[i]) ? 1:0;
    }
    return unmatch_counter;
}

void print_time ( const std::chrono::system_clock::time_point start, const  std::chrono::system_clock::time_point end, const size_t n, const char* const proc_name){
    const double elapsed_m = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    const double elapsed_u = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count(); //処理に要した時間をマイクロ秒に変換
    const double elapsed_n = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); //処理に要した時間をナノ秒に変換

    std::cout << proc_name << " " << n << " elems" << std::endl;
    std::cout << "\t" << elapsed_m << " msec" << std::endl;
    std::cout << "\t" << elapsed_u << " usec" << std::endl;
    std::cout << "\t" << elapsed_n << " nsec" << std::endl;   
}

int main (int argc, char *argv[]) {

    size_t n;
    if (argc < 2) {
        n = N;
    } else {
        n = stoi(argv[1]);
        if (n > N) {
            n = N;
        }
    }
    // init 
    init_mat(A, B, C, n);
    //cache_clean();
    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間
    // 処理
    u16axpy(C, A, B, ALPHA, n);

    end = std::chrono::system_clock::now();  // 計測終了時間
    print_time(start, end, n, "u16axpy");
    //cache_clean();
    start = std::chrono::system_clock::now(); // 計測開始時間
    // 処理
    u16axpy_neon(C_V, A, B, ALPHA, n);

    end = std::chrono::system_clock::now();  // 計測終了時間
    print_time(start, end, n, "u16axpy_neon");
    //std::cout << "Finish!" << std::endl;

    std::cout << "Check: unmatch " << check<uint16_t>(C, C_V, n) << std::endl;

}
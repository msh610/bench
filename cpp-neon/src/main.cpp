#include <iostream>
#include <chrono>
#include <random>
#include "func.hpp"

using namespace std;

#define N (1024*1024*10)
#define ALPHA (4)
uint16_t A[N];
uint16_t B[N];
uint16_t C[N];

void init_mat(uint16_t a[], uint16_t b[], uint16_t c[], const size_t n){
    std::mt19937 mt(0);
    std::uniform_int_distribution<> rand10(0, 9);
     for (size_t i = 0; i < n; i++) {
        a[i] = rand10(mt);
        b[i] = rand10(mt);
     }
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

    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間
    // 処理
    u8axpy(A, B, C, ALPHA, n);

    end = std::chrono::system_clock::now();  // 計測終了時間
    double elapsed_m = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    double elapsed_u = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count(); //処理に要した時間をマイクロ秒に変換
    double elapsed_n = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count(); //処理に要した時間をナノ秒に変換

    std::cout << n << " elems" << std::endl;
    std::cout << "\t" << elapsed_m << " msec" << std::endl;
    std::cout << "\t" << elapsed_u << " usec" << std::endl;
    std::cout << "\t" << elapsed_n << " nsec" << std::endl;    
    //std::cout << "Finish!" << std::endl;
}
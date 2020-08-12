use std::time::{Instant, Duration};
mod xaxpy;
use xaxpy::{u16axpy};
use rand::Rng;

fn init_mat(a : &mut [u16], b : &mut [u16], n : usize) {
    let mut rng = rand::thread_rng(); // デフォルトの乱数生成器を初期化します
    for i in 0..n {
        a[i] = rng.gen_range(0, 9);
        b[i] = rng.gen_range(0, 9);
    }

}

fn check(a : &[u16], b : &[u16], n : usize) -> usize {
    let mut unmatch_count : usize = 0;
    for i in 0..n {
       unmatch_count += if a[i] != b[i] {
           1
       } else {
           0
       };
    } 
    unmatch_count
}

fn main() {
    const LEN: usize = 1024*512;
    let mut a : [u16; LEN] = [0; LEN];
    let mut b : [u16; LEN] = [0; LEN];
    let mut c : [u16; LEN] = [0; LEN];
    let mut c_v : [u16; LEN] = [0; LEN];
    let alpha : u16 = 4;
    init_mat(&mut a, &mut b, LEN);

    let start = Instant::now();   // 開始時刻
    u16axpy(&mut c, &a, &b, alpha, LEN);
    let end : Duration = start.elapsed();    // 経過時間
    println!("{} usec",end.as_micros());

    let start2 = Instant::now();   // 開始時刻
    u16axpy(&mut c_v, &a, &b, alpha, LEN);
    let end2 : Duration = start2.elapsed();    // 経過時間
    println!("{} usec",end2.as_micros());

    println!("Check unmatch {}", check(&c, &c_v, LEN));
}

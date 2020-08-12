pub fn u16axpy(c : &mut [u16], a : &[u16], b : &[u16], alpha : u16, n : usize) {
    for i in 0..n {
        c[i] = alpha * a[i] + b[i];
    }
}
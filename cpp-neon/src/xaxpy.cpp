#include "func.hpp"

void u8axpy (uint16_t c[], const uint16_t a[], const uint16_t b[], const uint16_t alpha, const size_t n) 
{
    for (size_t i = 0; i < n; i++) {
        c[i] = alpha* a[i] + b[i];
    }
}
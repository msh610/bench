#include "func.hpp"
#include <arm_neon.h>

void u16axpy (uint16_t c[], const uint16_t a[], const uint16_t b[], const uint16_t alpha, const size_t n) 
{
    for (size_t i = 0; i < n; i++) {
        c[i] = alpha* a[i] + b[i];
    }
}

void u16axpy_neon (uint16_t c[], const uint16_t a[], const uint16_t b[], const uint16_t alpha, const size_t n) 
{
    size_t i;
    for (i = 0; i < n-8; i+=8) {
        uint16x8_t a_v = vld1q_u16(&a[i]);
        uint16x8_t b_v = vld1q_u16(&b[i]);
        uint16x8_t alpha_v = vdupq_n_u16(alpha);
        uint16x8_t c_v = vmlaq_u16(b_v, a_v, alpha_v);
        vst1q_u16 (&c[i], c_v);
    }
    for (; i < n; i++) {
        c[i] = alpha* a[i] + b[i];
    }
}
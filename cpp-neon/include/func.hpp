
#include <cstdint>
using std::uint16_t;
using std::size_t;

void u16axpy (uint16_t c[], const uint16_t a[], const uint16_t b[], const uint16_t alpha, const size_t n);
void u16axpy_neon (uint16_t c[], const uint16_t a[], const uint16_t b[], const uint16_t alpha, const size_t n);

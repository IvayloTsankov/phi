#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <emmintrin.h>

#define THREAD_NUM 4
#define N 1000000

int main()
{
    int buff[4];

    int* ptr = buff;
    __m128i x = _mm_set_epi32(1, 2, 3, 4);
    __m128i y = _mm_set_epi32(*ptr++, *ptr++, *ptr++, *ptr++);

    __m128i r = _mm_add_epi32(x, y);
    _mm_storeu_si32((__m128i*)buff, r);

    printf("%d %d %d %d\n", buff[0], buff[1], buff[2], buff[3]);
    return (0);
}

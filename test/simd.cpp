#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define THREAD_NUM 4
#define N 1000000

int main()
{
    int i = 0;
    int buff[N];

    omp_set_num_threads(THREAD_NUM);

    // init data
    for(int i = 0; i < N; ++i)
    {
        buff[i] = i;
    }

    //#pragma omp parallel for
    for(int i = 0; i < N; ++i)
    {
        buff[i] = buff[i] + pow(sin(i), cos(i));
        buff[i] /= 2;
        buff[i] *= tan(buff[i]);
    }

    return (0);
}

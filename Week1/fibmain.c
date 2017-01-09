#include <stdio.h>

#include "fib.h"

long fiba[] = {1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765};

int main()
{
    int n, t = 1;
    for(n = 0; n < 20; n++)
    t = t && (fib(n) == fiba[n]);
    if(t)
        printf("Yay. Test passed.\n");
    else
        printf("Grr. Test failed.\n");

    printf("Testing retrieval of cached items:\n");
    long t1 = fib(3);
    long t2 = fib(6);
}

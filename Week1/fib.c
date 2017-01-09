#include <stdio.h>

// NAIVE IMPLEMENTATION
// long fib(long n) {
//     long n1 = 1;
//     long n2 = 1;
//
//     for (long i = 0; i < n; i++) {}
//         long oldn1 = n1;
//         n1 = n2;
//         n2 = n2 + oldn1;
//     }
//     return n1;
// }

long fibvals[1000];

long fib(long n) {
    long fibn = fibvals[n];
    if (fibn != 0) {
        printf("retrieve cached %ld at index %ld\n", fibn, n);
        return fibn;
    } else {
        long n1 = 1;
        long n2 = 1;

        for (int i = 0; i < n; i++) {
            long oldn1 = n1;
            n1 = n2;
            n2 = n2 + oldn1;
        }
        fibvals[n] = n1;
        printf("not cached - put into cache fibvals[%ld] = %ld\n", n, n1);
        return n1;
    }
}

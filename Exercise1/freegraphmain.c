// test file for exercise

#include <stdio.h>
#include <stdlib.h>

#include "freegraph.h"

struct N *mknode(struct N *xp, struct N *yp, struct N *zp, long n)
{
    struct N *p = malloc(sizeof(struct N));
    p->x = xp;
    p->y = yp;
    p->z = zp;
    p->data = n;
    return p;
}

int main(int argc, const char *argv[])
{
  struct N *p1, *p2, *p3, *p4, *p5, *p6;
    
    // construct a tree for testing: 
    
    p1 = mknode(NULL, NULL, NULL, 1);
    p2 = mknode(NULL, NULL, NULL, 10);
    p3 = mknode(NULL, NULL, NULL, 100);
    p4 = mknode(p1, p2, p3, 3000);
    p1 = mknode(NULL, NULL, NULL, 1);
    p2 = mknode(NULL, NULL, NULL, 10);
    p3 = mknode(NULL, NULL, NULL, 100);
    p5 = mknode(p1, p2, p3, 4000);
    p5 = mknode(p4, p5, NULL, 50000);
    p6 = mknode(p5, NULL, NULL, 100000);

    // to test only on trees, remove the following
    // assignments that turn the tree into a graph
    p1->x = p5;
    p2->y = p4;
    p2->z = p2;
    p6->y = p5;
    p6->z = p6; 

    if(sum(p6) == 157222)
        printf("Yay. Test passed.\n");
    else
        printf("Grr. Test failed.\n");
    
    // valgrind should report no leaks after this:
    deallocate(p6);

    return 0;
}



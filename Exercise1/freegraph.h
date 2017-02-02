// freegraph interface

struct N {
  struct N *x;
  struct N *y;
  struct N *z;
  long data;
};

long sum(struct N *ap);

void deallocate(struct N *ap);

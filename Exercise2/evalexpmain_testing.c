// main function for evaluation expression exercise

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evalexp.h"

// tree construction functions

struct exp *mkvar(char *cp)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isvar;
  strncpy(ep->var, cp, 8);
  return ep;
}

struct exp *mkconstant(int n)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isconstant;
  ep->constant = n;
  return ep;
}

struct exp *mkopapp(enum op op, struct explist *el)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = isopapp;
  ep->op =  op;
  ep->exps =  el;
  return ep;
}

struct exp *mklet(char *cp, struct exp *e1, struct exp *e2)
{
  struct exp *ep = malloc(sizeof(struct exp));
  ep->tag = islet;
  strncpy(ep->bvar, cp, 8);
  ep->bexp = e1;
  ep->body = e2;
  return ep;
}

struct explist *cons(struct exp *e, struct explist *l)
{
  struct explist *l2 = malloc(sizeof(struct explist));
  l2->head = e;
  l2->tail = l;
  return l2;
}

// main for testing
int main(int argc, const char *argv[])
{
  struct exp *e1, *e2;
  struct explist *l;

  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(2), l);
  e1 = mkopapp(isplus, l);
  // e1 = (+ 2 3 5)
  // e1 = 10

  l = NULL;
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  e2 = mkopapp(ismult, l);
  // e2 = (* x x x)

  e1 = mklet("x", e1, e2);
  // e1 = (= x e1 e2)
  // e1 = (= x (+ 2 3 5) (* x x x))
  // e1 = 1000

  printf("%d\n", evalexp(e1)); // should print 1000

  // TODO remove
  // My tests - from the ex sheet
  struct exp *em1a, *em1b, *em1c, *em1d;

  l = NULL;
  l = cons(mkconstant(5), l);
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(2), l);
  em1a = mkopapp(isplus, l);

  l = NULL;
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  em1c = mkopapp(isplus, l);

  l = NULL;
  l = cons(em1c, l);
  l = cons(mkvar("x"), l);
  l = cons(mkvar("x"), l);
  em1b = mkopapp(ismult, l);

  em1d = mklet("x", em1a, em1b);
  printf("test em1: %d\n", evalexp(em1d)); // should be 2000

  struct exp *em2a, *em2b, *em2c, *em2d, *em2e;

  l = NULL;
  l = cons(mkconstant(3), l);
  l = cons(mkconstant(6), l);
  em2a = mkopapp(ismult, l); // (* 6 3)

  l = NULL;
  l = cons(mkvar("y"), l);
  l = cons(mkvar("x"), l);
  em2b = mkopapp(ismult, l); // (* x y)

  l = NULL;
  l = cons(mkconstant(2), l);
  l = cons(mkconstant(4), l);
  em2c = mkopapp(isplus, l); // (+ 4 2)

  em2d = mklet("x", em2a, em2b); // (= x (* 6 3) (* x y))
  em2e = mklet("y", em2c, em2d); // (= y (+ 4 2) (= x (* 6 3) (* x y)))
  printf("test em2: %d\n", evalexp(em2e)); // should be 108

  return 0;
}

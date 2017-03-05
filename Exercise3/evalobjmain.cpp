
#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[])
{
  ExpList *l = nullptr;
  l = new ExpList(new Constant(23), l);
  l = new ExpList(new Constant(42), l);
  l = new ExpList(new Constant(666), l);

  Exp *e = new OpApp(plusop, l);
  cout << e->eval(nullptr) << endl;

  // return 0;

  // OWN TESTS
  Exp *e2 = new Let("y", new Constant(10), new Var("y"));

  ExpList *l2 = nullptr;
  l2 = new ExpList(new Var("y"), l2);
  l2 = new ExpList(e2, l2);
  l2 = new ExpList(new Var("y"), l2);
  Exp *e3 = new OpApp(plusop, l2);

  Exp *e4 = new Let("y", new Constant(2) , e3);

  cout << e4->eval(nullptr) << endl; //should print 14

  return 0;
}

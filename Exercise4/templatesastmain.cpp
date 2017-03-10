#include <iostream>
#include <functional>

using namespace std;

#include "templatesast.h"

#include "templatesast.cpp" // this is where the eval functions should be

// instantiate the AST template and try it

int add(int x, int y) { return x + y; }

float mult(float x, float y) { return x * y; }

int main(int argc, const char *argv[])
{
  operators<int> intops = { add, 0 };

  ExpList<int> *l = nullptr;
  l = new ExpList<int>(new Constant<int>(30), l);
  l = new ExpList<int>(new Constant<int>(12), l);
  Exp<int> *e = new OpApp<int>(intops, l);
  cout << e->eval(nullptr) << endl; // should print 0 + 12 + 30 = 42

  Exp<int> *e1 = new OpApp<int>(intops, nullptr);
  cout << e1->eval(nullptr) << endl; // should print 0

  operators<float> floatops = { mult, 1.0 };

  ExpList<float> *l2 = nullptr;
  l2 = new ExpList<float>(new Constant<float>(.222), l2);
  l2 = new ExpList<float>(new Constant<float>(3.0), l2);
  Exp<float> *e2 = new OpApp<float>(floatops, l2);
  cout << e2->eval(nullptr) << endl; // should print 0.666 = 1.0 * 3.0 * .222
  return 0;
}

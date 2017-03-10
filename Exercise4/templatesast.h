// Lisp-style ASTs
// parametric in the value type
// eval operations are NOT implemented

#pragma once

template<typename V>
struct env {
  string var;
  V value;
  env<V> *next;
};

template<typename V>
class Exp {
 public:
  virtual V eval(env<V>*) = 0;
};

template<typename V>
class Let : public Exp<V> {
  string bvar;
  Exp<V> *bexp;
  Exp<V> *body;
 public:
  Let(string x, Exp<V> *e, Exp<V> *b)
    {
      bvar = x; bexp = e; body = b;
    }

  V eval(env<V>*);
};

template<typename V>
class Constant : public Exp<V> {
  V c;
 public:
  Constant(V c) { this->c = c; }

  V eval(env<V>*);
};

template<typename V>
class Var : public Exp<V> {
  string name;
 public:
  Var(string x) { this->name = x; }

  V eval(env<V>*);
};

template<typename V>
struct ExpList {
  Exp<V> *head;
  ExpList<V> *tail;
  ExpList(Exp<V> *h, ExpList<V> *t)
    {
      head = h; tail = t;
    }
};

template<typename V>
struct operators {
  std::function<V(V,V)> binop;
  V unit;
};

template<typename V>
class OpApp : public Exp<V> {
  operators<V> ops;
  ExpList<V> *args;
 public:
  OpApp(operators<V> o, ExpList<V> *a)
    {
      ops = o; args = a;
    }

  V eval(env<V>*);
};

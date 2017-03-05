
struct env {
  string var;
  int value;
  env *next;
};

class Exp {
 public:
  virtual int eval(env*) = 0;
};

class Constant : public Exp {
  int n;
 public:
  Constant(int n) {this->n = n; }
  int eval(env*);
};

class Var : public Exp {
  string name;
 public:
  Var(string s) { this->name = s; }
  int eval(env*);
};

class Let : public Exp {
  string bvar;
  Exp *bexp;
  Exp *body;
 public:
  Let(string v, Exp *e, Exp *b)
    {
      bvar = v; bexp = e; body = b;
    }
  int eval(env*);
};

class ExpList {
 public:
  Exp *head;
  ExpList *tail;
  ExpList(Exp *h, ExpList *t) { head = h; tail = t; }
};

enum op { plusop, timesop };

class OpApp : public Exp {
  enum op op;
  ExpList *args;
 public:
  OpApp(enum op o, ExpList *a) { op = o; args = a; }
  int eval(env*);
};

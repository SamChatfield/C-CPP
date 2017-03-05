#include <string>
using namespace std;
#include "evalobj.h"
#include <stdlib.h>
#include <string.h>

#include <iostream>

// Environment structure as a stack where each node has the variable name and
// its corresponding value

struct env *envadd(struct env *en, string var, int value);
int evalplus(ExpList *l, struct env *en);
int evalmult(ExpList *l, struct env *en);

int lookup(struct env *en, string var) {
    while (en) {
        // if (strncmp(en->var, var, 8) == 0) {
        if (var.compare(en->var) == 0) {
            return en->value;
        } else {
            en = en->next;
        }
    }
    exit(1);
}

struct env *envadd(struct env *en, string var, int value) {
    // struct env *current = malloc(sizeof(struct env));
    struct env *current = new struct env;
    // strncpy(current->var, var, 8);
    current->var = var;
    current->value = value;
    current->next = en;
    return current;
}

int Constant::eval(struct env *en) {
    cout << "const";
    return this->n;
}

int Var::eval(struct env *en) {
    cout << "var";
    return lookup(en, this->name);
}

int Let::eval(struct env *en) {
    cout << "let";
    struct env *newen = envadd(en, this->bvar, this->bexp->eval(en));
    return this->body->eval(newen);
}

int OpApp::eval(struct env *en) {
    cout << "opapp";
    switch (this->op) {
        case plusop:
            return evalplus(this->args, en);
        case timesop:
            return evalmult(this->args, en);
    }
}

int evalplus(ExpList *l, struct env *en) {
    int result = 0;
    while (l) {
        // result += evalexpenv(l->head, en);
        result += l->head->eval(en);
        l = l->tail;
    }
    return result;
}

int evalmult(ExpList *l, struct env *en) {
    int result = 1;
    while (l) {
        // result *= evalexpenv(l->head, en);
        result *= l->head->eval(en);
        l = l->tail;
    }
    return result;
}

#include <string>
using namespace std;
#include "templatesast.h"
#include <stdlib.h>
#include<functional>

template<typename V>
V lookup(struct env<V> *en, string var) {
    while (en) {
        if (var.compare(en->var) == 0) {
            return en->value;
        } else {
            en = en->next;
        }
    }
    exit(1);
}

template<typename V>
struct env<V> *envadd(struct env<V> *en, string var, V value) {
    struct env<V> *current = new struct env<V>;
    current->var = var;
    current->value = value;
    current->next = en;
    return current;
}

template<typename V>
V Constant<V>::eval(struct env<V> *en) {
    // cout << "c=" << this->c << endl;
    return this->c;
}

template<typename V>
V Var<V>::eval(struct env<V> *en) {
    // cout << "var" << endl;
    return lookup(en, this->name);
}

template<typename V>
V Let<V>::eval(struct env<V> *en) {
    // cout << "let" << endl;
    struct env<V> *newen = envadd(en, this->bvar, this->bexp->eval(en));
    return this->body->eval(newen);
}

template<typename V>
V OpApp<V>::eval(struct env<V> *en) {
    // cout << "opapp" << endl;
    V result = this->ops.unit;
    ExpList<V> *l = this->args;
    while (l) {
        result = this->ops.binop(result, l->head->eval(en));
        // cout << "res: " << result << endl;
        l = l->tail;
    }
    return result;
}

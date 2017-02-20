#include "evalexp.h"
#include <stdlib.h>
#include <string.h>

// Environment structure as a stack where each node has the variable name and
// its corresponding value
struct env {
    char var[8];
    int val;
    struct env *next;
};

int evalplus(struct explist *l, struct env *en);
int evalmult(struct explist *l, struct env *en);
int evalexpenv(struct exp *e, struct env *en);
struct env *envadd(struct env *en, char *var, int val);

int lookup(struct env *en, char *var) {
    while (en) {
        if (strncmp(en->var, var, 8) == 0) {
            return en->val;
        } else {
            en = en->next;
        }
    }
    exit(1);
}

struct env *envadd(struct env *en, char *var, int val) {
    struct env *this = malloc(sizeof(struct env));
    strncpy(this->var, var, 8);
    this->val = val;
    this->next = en;
    return this;
}

int evalexp(struct exp *e) {
    return evalexpenv(e, NULL);
}

int evalexpenv(struct exp *e, struct env *en) {
    switch (e->tag) {
        case isconstant:
            return e->constant;
        case isopapp:
            switch (e->op) {
                case isplus:
                    return evalplus(e->exps, en);
                case ismult:
                    return evalmult(e->exps, en);
            }
        case isvar:
            return lookup(en, e->var);
        case islet: {
            struct env *newen = envadd(en, e->bvar, evalexpenv(e->bexp, en));
            return evalexpenv(e->body, newen);
        }
    }
}

int evalplus(struct explist *l, struct env *en) {
    int result = 0;
    while (l) {
        result += evalexpenv(l->head, en);
        l = l->tail;
    }
    return result;
}

int evalmult(struct explist *l, struct env *en) {
    int result = 1;
    while (l) {
        result *= evalexpenv(l->head, en);
        l = l->tail;
    }
    return result;
}

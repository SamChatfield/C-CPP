#include "evalexp.h"
#include <stdlib.h>
#include <string.h>

// TODO remove
#include <stdio.h>

struct env;
int evalplus(struct explist *l);
int evalmult(struct explist *l);

// Environment structure as a list where each node has the variable name and
// its corresponding value
struct env {
    char var[8];
    int val;
    struct env *next;
};

int lookup(struct env *env, char var[8]) {
    while (env) {
        if (strcmp(env->var, var) == 0) {
            return env->val;
        } else {
            env = env->next;
        }
    }
    printf("Error: variable not found\n");
    exit(1);
}

int evalexp(struct exp *e) {
    switch (e->tag) {
        case isconstant:
            return e->constant;
        case isopapp:
            switch (e->op) {
                case isplus:
                    return evalplus(e->exps);
                case ismult:
                    return evalmult(e->exps);
            }
        case isvar:
            // Not implemented
            return -1;
        case islet:
            // Not implemented
            return -1;
    }
}

int evalplus(struct explist *l) {
    int result = 0;
    while (l) {
        result += evalexp(l->head);
        l = l->tail;
    }
    return result;
}

int evalmult(struct explist *l) {
    int result = 1;
    while (l) {
        result *= evalexp(l->head);
        l = l->tail;
    }
    return result;
}

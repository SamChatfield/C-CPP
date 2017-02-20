x // Solutions file

#include "freegraph.h"
#include <stdlib.h>

struct List {
    struct ListNode *head;
    struct ListNode *last;
};

struct ListNode {
    struct ListNode *next;
    struct N *data;
};

void listadd(struct List *list, struct N *data);
int listcontains(struct List *list, struct N *data);
long sumrec(struct N *p, struct List *visited);
void deallocrec(struct N *p, struct List *visited);
void dealloclist(struct List *list);

void listadd(struct List *list, struct N * data) {
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->next = NULL;
    new->data = data;

    if (!(list->head) && !(list->last)) {
        list->head = new;
        list->last = new;
    } else {
        list->last->next = new;
        list->last = new;
    }
}

// Return 0 if list starting at head doesn't contain graph node pointer data
// and 1 if it does
int listcontains(struct List *list, struct N *data) {
    struct ListNode *p = list->head;
    while (p) {
        if (p->data == data) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

// Create the linked list of visited graph nodes and begin the recursive sum function
long sum(struct N *p) {
    struct List *visited = malloc(sizeof(struct List));
    visited->head = NULL;
    visited->last = NULL;
    long result = sumrec(p, visited);
    dealloclist(visited);
    return result;
}

// Recurse over the graph and the list of visited nodes
long sumrec(struct N *p, struct List *visited) {
    // If the graph node isn't null and hasn't been visited then move to it
    if (p && !listcontains(visited, p)) {
        listadd(visited, p);
        return
            p->data +
            sumrec(p->x, visited) +
            sumrec(p->y, visited) +
            sumrec(p->z, visited);
    }
    return 0L;
}

void deallocate(struct N *p) {
    struct List *visited = malloc(sizeof(struct List));
    visited->head = NULL;
    visited->last = NULL;
    deallocrec(p, visited);
    dealloclist(visited);
}

void deallocrec(struct N *p, struct List *visited) {
    if (p && !listcontains(visited, p)) {
        listadd(visited, p);
        deallocrec(p->x, visited);
        deallocrec(p->y, visited);
        deallocrec(p->z, visited);
        free(p);
    }
}

void dealloclist(struct List *list) {
    struct ListNode *head = list->head;
    struct ListNode *current;
    while (head) {
        current = head;
        head = head->next;
        free(current);
    }
    free(list);
}

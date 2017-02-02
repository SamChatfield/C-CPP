// Solutions file

#include "freegraph.h"
#include <stdlib.h>

// Testing purposes TODO remove this
#include <stdio.h>

struct List {
    struct ListNode *head;
    struct ListNode *last;
};

struct ListNode {
    struct ListNode *next;
    struct N *data;
};

struct List *listadd(struct List *list, struct N *data);
int listcontains(struct List *list, struct N *data);
long sumrec(struct N *p, struct List *visited);

struct List *listadd(struct List *list, struct N *data) {
    // Create the new node that will go on the end
    struct ListNode *new = malloc(sizeof(struct ListNode));
    new->next = NULL;
    new->data = data;

    // If the list is empty then create it with the new node
    // Else just link the new one to the end and move the last pointer along
    if (!(list->head) && !(list->last)) {
        list->head = new;
        list->last = new;
    } else {
        // Link the current last node to the new one
        list->last->next = new;
        // Make the pointer to the last node point to the new last (the new node)
        list->last = new;
    }
    return list;
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
    return sumrec(p, visited);
}

// Recurse over the graph and the list of visited nodes
long sumrec(struct N *p, struct List *visited) {
    // If the graph node isn't null and hasn't been visited then move to it
    if (p && !listcontains(visited, p)) {
        visited = listadd(visited, p);
        return
            p->data +
            sumrec(p->x, visited) +
            sumrec(p->y, visited) +
            sumrec(p->z, visited);
    }
    return 0L;
}

void deallocate(struct N *ap) {

}

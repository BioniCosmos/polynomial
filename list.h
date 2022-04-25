#ifndef POLYNOMIAL_LIST_H
#define POLYNOMIAL_LIST_H


#include "polynomial.h"

typedef enum {
    TERM,
} NodeType;

typedef struct Node {
    NodeType type;
    union {
        Term term;
    };
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

typedef bool (*cmpFunc)(Node *, Node *);

Node *newNode(NodeType);

void appendToList(List *, Node *);

void sortList(List *, bool (*)(Node *, Node *));

Node *getMidNode(List);

List mergeList(List, List, bool (*)(Node *, Node *));

List copyList(List);


#endif // POLYNOMIAL_LIST_H

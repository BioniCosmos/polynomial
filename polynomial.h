#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H


#include <stdbool.h>

typedef struct Term {
    int coef;
    int exp;
} Term;

typedef struct Node Node;

typedef struct List List;

void getPolynomial(List *);

bool cmpExp(Node *, Node *);

void printPolynomial(List);

void printCoef(int, bool);

void printExp(int);

int calcPolynomial(List, int);

List addPolynomial(List, List);

List subPolynomial(List, List);

void combineLikeTerms(List);

void removeZeroTerms(List *);


#endif // POLYNOMIAL_POLYNOMIAL_H

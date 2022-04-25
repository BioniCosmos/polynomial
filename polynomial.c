#include <math.h>
#include <stdio.h>
#include "list.h"

void getPolynomial(List *listPtr) {
    int terms;
    scanf("%d", &terms);
    for (int i = 0; i < terms; i++) {
        Node *node = newNode(TERM);
        scanf("%d%d", &node->term.coef, &node->term.exp);
        if (node->term.coef) {
            appendToList(listPtr, node);
        }
    }
}

bool cmpExp(Node *a, Node *b) {
    return a->term.exp > b->term.exp;
}

void printPolynomial(List list) {
    if (list.head) {
        printCoef(list.head->term.coef, false);
        printExp(list.head->term.exp);
        while ((list.head = list.head->next)) {
            printCoef(list.head->term.coef, true);
            printExp(list.head->term.exp);
        }
        putchar('\n');
        return;
    }
    puts("0");
}

void printCoef(int coef, bool sign) {
    if (coef == 1) {
        return;
    }
    printf(sign ? "%+d" : "%d", coef);
}

void printExp(int exp) {
    if (exp == 0) {
        return;
    }
    if (exp == 1) {
        putchar('x');
        return;
    }
    printf("x^%d", exp);
}

int calcPolynomial(List list, int x) {
    int result = 0;
    do {
        result += list.head->term.coef * (int) pow(x, list.head->term.exp);
    } while ((list.head = list.head->next));
    return result;
}

List addPolynomial(List p, List q) {
    List pClone = copyList(p),
            qClone = copyList(q),
            mergedList = mergeList(pClone, qClone, cmpExp);
    combineLikeTerms(mergedList);
    removeZeroTerms(&mergedList);
    return mergedList;
}

List subPolynomial(List p, List q) {
    List pClone = copyList(p),
            qClone = copyList(q);

    for (Node *tmp = qClone.head; tmp; tmp = tmp->next) {
        tmp->term.coef *= -1;
    }

    List mergedList = mergeList(pClone, qClone, cmpExp);
    combineLikeTerms(mergedList);
    removeZeroTerms(&mergedList);
    return mergedList;
}

void combineLikeTerms(List list) {
    while (list.head && list.head->next) {
        if (list.head->term.exp == list.head->next->term.exp) {
            list.head->term.coef += list.head->next->term.coef;
            list.head->next = list.head->next->next;
        } else {
            list.head = list.head->next;
        }
    }
}

void removeZeroTerms(List *listPtr) {
    while (listPtr->head) {
        if (listPtr->head->term.coef == 0) {
            if (listPtr->head->next) {
                listPtr->head = listPtr->head->next;
            } else {
                listPtr->head = NULL;
                return;
            }
        } else {
            break;
        }
    }

    Node *tmp = listPtr->head;
    while (tmp && tmp->next) {
        if (tmp->next->term.coef == 0) {
            tmp->next = tmp->next->next;
        } else {
            tmp = tmp->next;
        }
    }
}

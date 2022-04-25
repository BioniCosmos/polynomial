#include <stdio.h>
#include "gc.h"
#include "list.h"
#include "polynomial.h"

int main(void) {
    initVM();

    List p = {.head = NULL, .tail = NULL}, q = {.head = NULL, .tail = NULL};

    getPolynomial(&p);
    getPolynomial(&q);

    sortList(&p, cmpExp);
    sortList(&q, cmpExp);

    printf("P(x) = ");
    printPolynomial(p);
    printf("Q(x) = ");
    printPolynomial(q);

    int x;
    printf("x = ");
    scanf("%d", &x);
    printf("P(%d) = %d\n", x, calcPolynomial(p, x));
    printf("Q(%d) = %d\n", x, calcPolynomial(q, x));

    printf("R(x) = ");
    printPolynomial(addPolynomial(p, q));
    printf("T(x) = ");
    printPolynomial(subPolynomial(p, q));

    freeVM();
    return 0;
}

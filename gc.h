#ifndef POLYNOMIAL_GC_H
#define POLYNOMIAL_GC_H


#include <stdbool.h>
#include "list.h"

#define STACK_MAX 256
#define INIT_MAX_OBJ 8

typedef enum {
    NODE,
} ObjectType;

typedef struct Object {
    ObjectType type;
    bool marked;
    union {
        Node *node;
    };
    struct Object *next;
} Object;

typedef struct VirtualMachine {
    Object *stack[STACK_MAX];
    int stackSize;
    Object *lastObject;
    int allocatedObjects;
    int maxObjects;
} VirtualMachine;

VirtualMachine *VM;

void initVM(void);

Object *newObject(ObjectType);

void pushObject(Object *);

void freeVM(void);

void GC(void);

void markAll(void);

void sweep(void);


#endif // POLYNOMIAL_GC_H

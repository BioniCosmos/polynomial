#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gc.h"

void initVM(void) {
    VM = malloc(sizeof(VirtualMachine));
    if (!VM) {
        perror("failed to create VM");
        exit(errno);
    }

    VM->stackSize = 0;
    VM->lastObject = NULL;
    VM->allocatedObjects = 0;
    VM->maxObjects = INIT_MAX_OBJ;
}

Object *newObject(ObjectType type) {
    if (VM->allocatedObjects == VM->maxObjects) {
        GC();
    }
    Object *object = malloc(sizeof(Object));
    if (!object) {
        freeVM();
        perror("failed to allocate object");
        exit(errno);
    }

    object->type = type;
    object->marked = false;
    object->next = VM->lastObject;
    VM->lastObject = object;
    VM->allocatedObjects++;
    return object;
}

void pushObject(Object *object) {
    if (VM->stackSize >= STACK_MAX) {
        freeVM();
        fputs("VM stack overflow", stderr);
        exit(EXIT_FAILURE);
    }

    VM->stack[VM->stackSize++] = object;
}

void freeVM(void) {
    VM->stackSize = 0;
    GC();
    free(VM);
}

void GC(void) {
    markAll();
    sweep();
    VM->maxObjects = VM->allocatedObjects == 0 ? INIT_MAX_OBJ : VM->allocatedObjects * 2;
}

void markAll(void) {
    for (int i = 0; i < VM->stackSize; i++) {
        VM->stack[i]->marked = true;
    }
}

void sweep(void) {
    Object **objectPtr = &VM->lastObject;
    while (*objectPtr) {
        if ((*objectPtr)->marked) {
            (*objectPtr)->marked = false;
            objectPtr = &(*objectPtr)->next;
        } else {
            Object *unmarked = *objectPtr;
            *objectPtr = unmarked->next;
            if (unmarked->type == NODE) {
                free(unmarked->node);
            }
            free(unmarked);
            VM->allocatedObjects--;
        }
    }
}

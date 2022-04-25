#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "list.h"

Node *newNode(NodeType type) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("failed to allocate a new node");
        freeVM();
        exit(errno);
    }

    node->type = type;
    node->next = NULL;

    Object *object = newObject(NODE);
    object->node = node;
    pushObject(object);
    return node;
}

void appendToList(List *listPtr, Node *node) {
    if (listPtr->head) {
        listPtr->tail->next = node;
    } else {
        listPtr->head = node;
    }
    listPtr->tail = node;
}

void sortList(List *listPtr, cmpFunc compare) {
    if (!listPtr->head || !listPtr->head->next) {
        return;
    }

    Node *mid = getMidNode(*listPtr);
    List left = *listPtr, right = {.head = mid->next, .tail = NULL};
    mid->next = NULL;

    sortList(&left, compare);
    sortList(&right, compare);

    *listPtr = mergeList(left, right, compare);
}

Node *getMidNode(List list) {
    Node *fast = list.head, *slow = list.head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

List mergeList(List left, List right, cmpFunc compare) {
    List list = {.head = NULL, .tail = NULL};
    Node *leftIdx = left.head, *rightIdx = right.head;

    while (leftIdx && rightIdx) {
        if (compare(leftIdx, rightIdx)) {
            appendToList(&list, leftIdx);
            leftIdx = leftIdx->next;
        } else {
            appendToList(&list, rightIdx);
            rightIdx = rightIdx->next;
        }
    }

    if (list.tail) {
        list.tail->next = leftIdx ? leftIdx : rightIdx;
    }
    return list;
}


List copyList(List srcList) {
    List dstList = {.head = NULL, .tail = NULL};
    if (srcList.head->type == TERM) {
        while (srcList.head) {
            Node *node = newNode(srcList.head->type);
            node->term = srcList.head->term;
            appendToList(&dstList, node);
            srcList.head = srcList.head->next;
        }
    }
    return dstList;
}

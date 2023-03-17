#include <stdio.h>
#include <stdlib.h>
#define KEYLEN 2

typedef int KeyType;
typedef int DataType;

struct RadixNode {
    KeyType key[KEYLEN];
    DataType info;
    struct RadixNode* next;
};

typedef struct RadixNode* PRNode;
typedef struct RadixNode* RadixList;

typedef struct {
    PRNode f;
    PRNode r;
} Queue;

void radixSort();
#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct Heap {
    int MAXNUM;
    int n;
    DataType* heap;
};

typedef struct Heap* PHeap;

int isEmpty_heap(PHeap pheap) {
    return (pheap->n == 0);
}

DataType getMin_heap(PHeap pheap) {
    return pheap->heap[0];
}

void add_heap(PHeap pheap, DataType x) {

    int i;
    if (pheap->n >= pheap->MAXNUM) {
        printf("Full heap!\n");
        return;
    }

    // 首先将新的数据放到堆的最后，即 pheap->n 序号的位置
    for (i = pheap->n; i > 0; i = (i - 1) / 2){
        // 当前结点 i 的父结点的值与 x 比较
        if (pheap->heap[(i - 1) / 2] > x){
            // 若小于父结点的值，则将结点 i 的父结点的值交换
            // 只需将结点 i 的值覆盖为父结点的值即可
            pheap->heap[i] = pheap->heap[(i - 1) / 2];
        } else
            break;
    }        

    // 结点 i 的父结点要小于 x，所以 x 的正确位置就是结点 i
    pheap->heap[i] = x;
    pheap->n++;
}

void removeMin_heap(PHeap pheap) {
    int s, i, child;
    DataType last;

    if (isEmpty_heap(pheap)) {
        printf("Empty heap!\n");
        return;
    }

    s = pheap->n - 1; // 长度减少 1
    pheap->n--;

    last = pheap->heap[s]; // 获取最后一个结点的值，相当于将此结点放到第一个结点的位置
    i = 0;
    child = 1;
    while (child < s) {
        // 当前结点要与此结点的左右子结点中较小的结点交换位置
        // 如果左子结点的值大于右子结点的值，则 child 从左结点变为右结点
        if (child < s - 1 && pheap->heap[child] > pheap->heap[child + 1])
            child++;
        
        // 如果较小的子结点比最后的结点的值小，则交换位置
        if (last > pheap->heap[child]) {
            // 只需将当前结点的值覆盖为子结点的值即可
            pheap->heap[i] = pheap->heap[child];
            // 当前结点的序号变为子结点的序号
            i = child;
            // 子结点序号变为 新的当前结点 的左子结点
            child = 2 * i + 1;
        } else
            break;
    }

    // 放到正确的位置上
    pheap->heap[i] = last;
}

int main(int argc, char const* argv[]) {

    PHeap pheap = (struct Heap*)malloc(sizeof(struct Heap));
    pheap->MAXNUM = 11;
    pheap->n = 0;
    pheap->heap = (DataType *)malloc(pheap->MAXNUM * sizeof(DataType));

    add_heap(pheap, 3);
    add_heap(pheap, 9);
    add_heap(pheap, 10);
    add_heap(pheap, 11);
    add_heap(pheap, 7);
    add_heap(pheap, 8);
    add_heap(pheap, 14);
    add_heap(pheap, 12);
    add_heap(pheap, 5);
    add_heap(pheap, 16);
    add_heap(pheap, 2);

    for (int i = 0; i < pheap->MAXNUM; i++) {
        printf("%d ", getMin_heap(pheap));
        removeMin_heap(pheap);
    }

    return 0;
}

// 2 3 8 7 5 10 14 12 11 16 9
// 0 1 2 3 4 5  6  7  8  9  10
//                 2
//            3         8
//        7      5   10   14
//     12  11  16  9

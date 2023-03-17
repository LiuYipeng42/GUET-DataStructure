#include "../heads/heap_sort.h"
#include "../heads/structs.h"

void sift(SortObject* pvector, int size, int p) {
    // 对 p 结点进行下沉的操作，
    // 相当于对以 p 结点为根节点的子树进行出堆的操作

    RecordNode temp = pvector->record[p];

    int child = 2 * p + 1;
    while (child < size) {
        if (child < size - 1)
            if (pvector->record[child].key < pvector->record[child + 1].key)
                child++;

        if (temp.key < pvector->record[child].key) {
            pvector->record[p] = pvector->record[child];
            p = child;
            child = 2 * p + 1;
        } else
            break;
    }

    pvector->record[p] = temp;
}

void heapSort(SortObject* pvector) {
    int i, n;
    RecordNode temp;
    n = pvector->n;
    // 从后往前，建立初始堆（大根堆）
    // 最小子树在 从下往上数的第二层
    for (i = n / 2 - 1; i >= 0; i--)
        sift(pvector, n, i);
    
    for (i = n - 1; i > 0; i--) {
        temp = pvector->record[0]; // 因为是大根堆，所以堆的根是最大值 
        pvector->record[0] = pvector->record[i]; // 将堆的最后一个结点放到根节点的位置
        pvector->record[i] = temp; // 将获取的最大值结点放到数组的位置 i 
        sift(pvector, i, 0);
    }
    
}

#include "./merge_sort.h"
#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;
    DataType info;
} RecordNode;

typedef struct {
    int n;
    RecordNode* record;
} SortObject;

// 归并两个数组（ low到m 和 m到high ），对两个数组中的数进行排序
void merge(RecordNode* r, RecordNode* r1, int low, int m, int high) {
    int i, j, k;
    i = low;
    j = m + 1;
    k = low;
    while ((i <= m) && (j <= high)) {
        if (r[i].key <= r[j].key) {
            r1[k] = r[i];
            i++;
        } else {
            r1[k] = r[j];
            j++;
        }
        k++;
    }
    while (i <= m) {
        r1[k] = r[i];
        k++;
        i++;
    }
    while (j <= high) {
        r1[k] = r[j];
        k++;
        j++;
    }
}

// 对 r 进行一次归并，结果放到 r1 中
void mergePass(RecordNode* r, RecordNode* r1, int n, int length) {
    // length 为归并的两个数组的长度
    int j, i = 0;
    while (i + 2 * length - 1 < n) {
        // 归并长度为 length 的两个数组
        merge(r, r1, i, i + length - 1, i + 2 * length - 1);
        i += 2 * length;
    }

    // 剩下的两个数组，后一个的长度小于 length
    if (i + length - 1 < n - 1) {
        merge(r, r1, i, i + length - 1, n - 1);
    } else {
        // 将最后剩下的数都复制到 r1 中
        for (j = i; j < n; j++)
            r1[j] = r[j];
    }
}

void mergeSort(SortObject* pvector) {
    RecordNode record[pvector->n];
    int length = 1;

    while (length < pvector->n) {
        // 进行一次归并，将结果放到 record 中
        mergePass(pvector->record, record, pvector->n, length);
        length *= 2;

        // 进行一次归并，将结果放回 pvector->record 中
        mergePass(record, pvector->record, pvector->n, length);
        length *= 2;
    }
}
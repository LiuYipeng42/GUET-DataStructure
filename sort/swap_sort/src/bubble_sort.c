#include "../heads/structs.h"
#include "../heads/bubble_sort.h"

void bubbleSort(SortObject* pvector) {
    int i, j, noswap;
    RecordNode temp, *data = pvector->record;

    for (i = 0; i < pvector->n - 1; i++) {
        noswap = 1;
        // 每次排序都会从未排序的部分选出一个最大值，放到最后
        for (j = 0; j < pvector->n - i - 1; j++) {
            if (data[j + 1].key < data[j].key) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                noswap = 0;
            }
        }
        if (noswap)
            break;
    }
}
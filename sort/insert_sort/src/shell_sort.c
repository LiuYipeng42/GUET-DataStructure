#include "../heads/shell_sort.h"
#include "../heads/structs.h"

void shellSort(SortObject* pvector, int d) {
    int i, j, inc;

    RecordNode temp;
    RecordNode* data = pvector->record;

    for (inc = d; inc > 0; inc /= 2) {
        // 直接插入排序的第一个元素不需要处理
        for (i = inc; i < pvector->n; i++) {
            temp = data[i];
            for (j = i - inc; j >= 0; j -= inc) {
                if (temp.key < data[j].key)
                    data[j + inc] = data[j];
                else
                    break;
            }
            data[j + inc] = temp;
        }
    }
}
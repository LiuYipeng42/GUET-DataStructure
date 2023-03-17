#include "../heads/insert_sort.h"
#include "../heads/structs.h"

void insertSort(SortObject* pvector) {
    int i, j;
    RecordNode temp;
    RecordNode* data = pvector->record;

    // 第一个元素不需要排序，所以从 1 开始
    for (int i = 1; i < pvector->n; i++) {
        temp = data[i];

        for (j = i - 1; j >= 0; j--) {

            // 将元素向后移动一位
            if (temp.key < data[j].key)
                data[j + 1] = data[j];
            else
                break;
        }

        data[j + 1] = temp;
    }
}
#include "../heads/select_sort.h"
#include "../heads/structs.h"

void selectSort(SortObject* pvector) {
    int i, j, min;

    RecordNode temp;
    RecordNode* data = pvector->record;

    for (i = 0; i < pvector->n - 1; i++) {
        min = i;
        for (j = i + 1; j < pvector->n; j++) {
            if (data[j].key < data[min].key)
                min = j;
        }
        if (min != i) {
            temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
    }
}
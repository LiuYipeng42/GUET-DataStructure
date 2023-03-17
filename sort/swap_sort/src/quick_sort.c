#include "../heads/quick_sort.h"
#include "../heads/structs.h"

void quickSort(SortObject* pvector, int l, int r) {
    int i, j;
    RecordNode temp, *data = pvector->record;

    if (l >= r)
        return;

    i = l;
    j = r;
    // 以第一个元素为比较的基准，最后可以找到此元素的正确位置
    temp = data[i]; 
    while (i != j) {
        // 从后向前遍历，找到一个比基准小的数
        while (i < j && data[j].key >= temp.key)
            j--;
        
        // 将较小的数与基准数字交换位置
        if (i < j) {
            data[i] = data[j];
            i++;
        }

        // 从前向后遍历，，找到一个比基准大的数
        while (i < j && data[i].key <= temp.key)
            i++;
        
        // 将较大的数与基准数字交换位置
        if (i < j) {
            data[j] = data[i];
            j--;
        }
    }

    // 放到正确的位置上
    data[i] = temp;
    quickSort(pvector, l, i - 1);
    quickSort(pvector, i + 1, r);
}
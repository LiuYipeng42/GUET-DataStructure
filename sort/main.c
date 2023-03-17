#include "./distribution_sort/heads/radix_sort.h"
#include "./insert_sort/heads/bin_sort.h"
#include "./insert_sort/heads/insert_sort.h"
#include "./insert_sort/heads/list_sort.h"
#include "./insert_sort/heads/shell_sort.h"
#include "./insert_sort/heads/structs.h"
#include "./select_sort/heads/heap_sort.h"
#include "./select_sort/heads/select_sort.h"
#include "./swap_sort/heads/bubble_sort.h"
#include "./swap_sort/heads/quick_sort.h"
#include "./merge_sort/merge_sort.h"

void list_sort() {
    int nums[8] = {38, 49, 65, 97, 76, 13, 27, 49};

    ListNode* list = (ListNode*)malloc(sizeof(ListNode));
    ListNode* cursor = list;

    for (int i = 0; i < 8; i++) {
        cursor->next = (ListNode*)malloc(sizeof(ListNode));
        cursor->next->key = nums[i];
        cursor = cursor->next;
    }

    listSort(&list);

    cursor = list->next;
    while (cursor != NULL) {
        printf("%d ", cursor->key);
        cursor = cursor->next;
    }
}

void radix_sort() {
    int nums[8][2] = { {4, 9}, {3, 8}, {6, 5}, {7, 6}, {1, 3}, {2, 7}, {4, 9} };

    RadixList list = (RadixList)malloc(sizeof(struct RadixNode));

    PRNode cursor = list;

    for (int i = 0; i < 7; i++) {
        cursor->next = (PRNode)malloc(sizeof(struct RadixNode));
        for (int j = 0; j < 2; j++)
            cursor->next->key[j] = nums[i][j];
        cursor = cursor->next;
    }

    radixSort(list, 2, 10);

    cursor = list->next;
    while (cursor != NULL) {
        printf("%d%d ", cursor->key[0], cursor->key[1]);
        cursor = cursor->next;
    }
    printf("\n");
}

void sort() {
    int nums[8] = {49, 38, 65, 97, 76, 13, 27, 49};

    SortObject* sortObject = (SortObject*)malloc(sizeof(SortObject));
    sortObject->n = 8;
    sortObject->record =
        (RecordNode*)malloc(sizeof(RecordNode) * sortObject->n);

    for (int i = 0; i < 8; i++)
        sortObject->record[i].key = nums[i];

    // insertSort(sortObject);
    // binSort(sortObject);
    // shellSort(sortObject, sortObject->n / 2);
    // selectSort(sortObject);
    // heapSort(sortObject);
    // bubbleSort(sortObject);
    // quickSort(sortObject, 0, sortObject->n - 1);
    mergeSort(sortObject);

    for (int k = 0; k < 8; k++)
        printf("%d ", sortObject->record[k].key);
    printf("\n");
}

int main(int argc, char const* argv[]) {
    list_sort();

    return 0;
}

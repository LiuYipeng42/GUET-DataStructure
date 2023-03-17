#include "../heads/radix_sort.h"

void radixSort(RadixList plist, int d, int r) {
    int i, j, k;
    PRNode cursor;
    PRNode head = plist->next; // 链表的第一个结点
    Queue queue[r];

    // 从个位开始排序
    for (j = d - 1; j >= 0; j--) {
        for (i = 0; i < r; i++) {
            queue[i].f = NULL;
            queue[i].r = NULL;
        }
        
        // 遍历链表，按照数字的第 j 位进行分配
        for (cursor = head; cursor != NULL; cursor = cursor->next) {
            k = cursor->key[j];
            if (queue[k].f == NULL)
                queue[k].f = cursor;
            else
                queue[k].r->next = cursor;
            queue[k].r = cursor;
        }

        // 找到第一个非空队列
        for (i = 0; queue[i].f == NULL; i++);
        // 将第一个非空队列的第一个结点作为排序列表的第一个结点
        head = queue[i].f;
        // 游标指向队列的最后，表明其他队列要添加在其后
        cursor = queue[i].r;
        // 添加剩余的队列
        for (i = i + 1; i < r; i++) {
            if (queue[i].f != NULL) {
                cursor->next = queue[i].f;
                cursor = queue[i].r;
            }
            // 队列中的结点除原链表的最后一个结点外的 next 都不为空，
            // 如不将排序好的链表最后结点的 next 变为 NULL，会出现循环
            cursor->next = NULL;
        }
        plist->next = head;
    }
}
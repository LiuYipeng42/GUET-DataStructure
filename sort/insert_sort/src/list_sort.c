#include "../heads/list_sort.h"
#include "../heads/structs.h"

void listSort(LinkList* plist) {
    ListNode *now, *pre, *p, *q, *head;

    // LinkList 是结点的指针
    // LinkList* plist 是头结点指针的指针
    head = *plist;

    // 链表中第一个结点（head）是头结点
    pre = head->next;
    if (pre == NULL)  // 空链表
        return;

    now = pre->next;
    if (now == NULL)  // 链表中只有一个结点
        return;

    while (now != NULL) {
        q = head; // 上一个结点 
        p = head->next; // 当前结点
        while (p != now && p->key <= now->key) {
            q = p;
            p = p->next;
        }

        // 说明 now 之前的结点都小于 now->key ，
        // now 在正确的位置上
        if (p == now) {
            pre = pre->next;
            now = pre->next;
            continue;
        }

        // p 是第一个大于 now->key 的结点
        // q 是最后一个小于 now->key 的结点
        // now 结点要插入到 q 之后
        // 删除 now 结点
        pre->next = now->next;
        // 将 now 放到 q 之后
        q->next = now;
        now->next = p;
        // 更新 now，删除原来的 now 结点后，新的 now 就是 pre 的下一个结点
        // pre 并不需要更新
        now = pre->next;
    }
}

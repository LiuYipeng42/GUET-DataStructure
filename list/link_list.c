#include <stdio.h>
#include <stdlib.h>

#define DataType int

struct Node;
typedef struct Node* PNode;

struct Node {
    DataType info;
    PNode link;
};

typedef struct Node* LinkList;

LinkList createNullList_link() {
    LinkList llist = (LinkList)malloc(sizeof(struct Node));

    if (llist != NULL)
        llist->link = NULL;
    else
        printf("Out of space!\n");

    return llist;
}

int isNullList_link(LinkList llist) {
    return (llist->link == NULL);
}

PNode locate_link(LinkList llist, DataType x) {
    // 查找数据 x 所在结点的指针

    PNode p;
    if (llist == NULL)
        return NULL;

    p = llist->link;
    while (p != NULL && p->info != x)
        p = p->link;

    return p;
}

int insertPost_link(LinkList llist, PNode p, DataType x) {
    // 在带头结点的单链表 llist 中，p 所指结点后面插入元素 x
    PNode q = (PNode)malloc(sizeof(struct Node));
    if (q == NULL) {
        printf("Out of Space!!!\n");
        return 0;
    } else {
        q->info = x;
        q->link = p->link;
        p->link = q;
        return 1;
    }
}

PNode locatePre_Link(LinkList llist, PNode p) {
    // 查找结点 p 的前驱结点
    PNode p1;
    if (llist == NULL)
        return NULL;

    p1 = llist;
    while (p1 != NULL && p1->link != p)
        p1 = p1->link;

    return p1;
}

int deleteV_link(LinkList llist, DataType x) {
    PNode p, q;
    p = llist;

    if (p == NULL)
        return 0;

    while (p->link != NULL && p->link->info != x)
        p = p->link;

    if (p->link == NULL) {
        printf("Not exist!\n");
        return 0;
    } else {
        q = p->link;
        p->link = q->link;
        free(q);
        return 1;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataType char

#define pop top--
#define push(s, data) s[++top] = data

struct BinTreeNode;
typedef struct BinTreeNode* PBinTreeNode;
struct BinTreeNode {
    DataType info;
    PBinTreeNode llink;
    PBinTreeNode rlink;
};

struct ThrTreeNode;
typedef struct ThrTreeNode* PThrTreeNode;
struct ThrTreeNode {
    DataType info;
    PThrTreeNode llink, rlink;
    // ltag：为 1 表明 llink 是前驱结点，为 0 表明 llink 是左子结点
    // rtag：为 1 表明 rlink 是后继结点，为 0 表明 rlink 是右子结点
    int ltag, rtag;
};
typedef struct ThrTreeNode* ThrTree;
typedef ThrTree* PThrTree;

PBinTreeNode leftChild_link(PBinTreeNode p) {
    if (p == NULL)
        return NULL;
    return p->llink;
}

PBinTreeNode rightChild_link(PBinTreeNode p) {
    if (p == NULL)
        return NULL;
    return p->rlink;
}

void visit(PBinTreeNode t) {
    printf("%c\n", t->info);
}

void preOrder(PBinTreeNode t) {
    if (t == NULL)
        return;
    visit(t);
    preOrder(t->llink);
    preOrder(t->rlink);
}

void inOrder(PBinTreeNode t) {
    if (t == NULL)
        return;
    preOrder(t->llink);
    visit(t);
    preOrder(t->rlink);
}

void postOrder(PBinTreeNode t) {
    if (t == NULL)
        return;
    preOrder(t->llink);
    preOrder(t->rlink);
    visit(t);
}

void nPreOrder(PBinTreeNode t) {
    PBinTreeNode stack[10];
    int top = -1;
    PBinTreeNode c;

    if (t == NULL)
        return;
    push(stack, t);
    while (top != -1) {
        c = stack[top];
        pop;
        if (c != NULL) {
            visit(c);
            push(stack, c->rlink);
            push(stack, c->llink);
        }
    }
}

void nInOrder(PBinTreeNode t) {
    PBinTreeNode stack[10];
    int top = -1;
    PBinTreeNode c = t;

    // 对于一颗树，依次将每一个节点左子结点放入栈中，
    // 到最左边的结点后，再依次将结点出栈，访问每一个结点，并找到右子结点
    // 对右子树重复以上操作
    if (t == NULL)
        return;
    do {
        while (c != NULL) {
            push(stack, c);
            c = c->llink;
        }
        c = stack[top];
        pop;
        visit(c);
        c = c->rlink;
    } while (c != NULL || top != -1);
}

void nPostOrder(PBinTreeNode t) {
    PBinTreeNode stack[10];
    int top = -1;
    PBinTreeNode p = t;
    while (p != NULL || top != -1) {

        // 找到一棵树后序遍历的第一个结点
        while (p != NULL) {
            push(stack, p);
            if (p->llink != NULL)
                p = p->llink;
            else
                p = p->rlink;
        }
        // 访问并将结点出栈
        p = stack[top];
        visit(p);
        pop;
        // 如果当前结点为父结点（栈顶结点）的左子结点，则将父结点的右子结点作为当前结点
        // 即后序遍历的先遍历子结点，再遍历父结点
        if (top != -1 && stack[top]->llink == p)
            p = stack[top]->rlink;
        else
            p = NULL;
    }
}

void levelOrder(PBinTreeNode t) {
    PBinTreeNode c, cc;
    PBinTreeNode queue[20];
    int font = 0, rear = 0;
    if (t == NULL)
        return;
    c = t;
    queue[rear++] = c;
    while (font != rear) {
        c = queue[font];
        font++;
        visit(c);
        cc = c->llink;
        if (cc != NULL) {
            queue[rear++] = cc;
        }
        cc = c->rlink;
        if (cc != NULL) {
            queue[rear++] = cc;
        }
    }
}

// 构造中序线索二叉树
// 以中序遍历的方式遍历二叉树，在过程中记录每一个结点的前驱结点
void thread(ThrTree t) {
    ThrTree stack[20];
    int top = -1;
    ThrTree p, pr;

    if (t == NULL)
        return;
    p = t;
    pr = NULL;
    do {
        while (p != NULL) {
            push(stack, p);
            p = p->llink;
        }
        p = stack[top];
        pop;
        if (pr != NULL) {
            // p 是 pr 的后继结点
            if (pr->rlink == NULL) {
                pr->rlink = p;
                pr->rtag = 1;
            }
            // pr 是 p 的前驱结点
            if (p->llink == NULL) {
                p->llink = pr;
                p->ltag = 1;
            }
        }
        pr = p;        // 记录当前访问的结点
        p = p->rlink;  // 进入右子树
    } while (top != -1 || p != NULL);
}

// 找到一个树的中序序列的第一个结点
ThrTree firstInOrderNode(ThrTree t){
    while (t->llink != NULL && t->ltag == 0)
        t = t->llink;
    return t;
}

// 遍历中序线索二叉树
void nThrInOrder(ThrTree t) {
    ThrTree p = t;
    if (t == NULL)
        return;
    p = firstInOrderNode(p);
    while (p != NULL) {
        printf("%c\n", p->info);
        if (p->rlink != NULL && p->rtag == 0) {
            // 右指针存放的是右子树指针
            p = p->rlink; // 找到右子树
            p = firstInOrderNode(p);
        } else
            // 右指针存放的是后继结点指针
            p = p->rlink; 
    }
}

PBinTreeNode create_node(DataType info) {
    PBinTreeNode node = (PBinTreeNode)malloc(sizeof(struct BinTreeNode));
    node->info = info;
    return node;
}

PBinTreeNode build(char input[]) {
    PBinTreeNode stack[10];
    int top = -1;  // 栈顶指向的是当前的父结点
    PBinTreeNode temp;

    int flag = -1;
    // 广义表按照出现顺序访问是前序遍历，所以是以前序遍历的方式构建，
    // 所以每次出栈后的栈顶就是父结点
    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (c == '(') {
            flag = 0;
            // 将 '(' 入栈，在左子结点为空且遇到 ',' 时起到占位的作用，
            push(stack, create_node(c));
        } else if (c == ',') {
            flag = 1;
        } else if (c == ')') {
            // 每次遇到 ')'，就表明当前结点的父结点的子结点都找到，
            // 出栈，找到当前结点的父结点
            pop;
        } else {
            temp = create_node(c);
            if (flag == -1) {
                push(stack, temp);
            } else if (flag == 0) {
                // 弹出栈中的 '('
                pop;
                stack[top]->llink = temp;
                push(stack, temp);
            } else if (flag == 1) {
                // 每次遇到 ','，表明当前结点的父结点的左子结点都找到，
                // 出栈，找到当前结点的父结点
                pop;
                stack[top]->rlink = temp;
                push(stack, temp);
            }
        }
    }
    return stack[top];
}

int main() {
    nPostOrder(build("a(b(d(,h)),c(e,f(g,i(k))))"));

    // ThrTree t = build("a(b(d(,h)),c(e,f(g,i(k))))");
    // thread(t);
    // nThrInOrder(t);
}

// a(b(d(,h)),c(e,f(g,i(k))))

// -1  a
// (   a (
// 0   a b
// (   a b (
// 0   a b d
// (   a b d (
// 1   a b d h
// )   a b d
// )   a b
// 1   a c
// (   a c (
// 0   a c e
// 1   a c f
// (   a c f (
// 0   a c f g
// 1   a c f i
// (   a c f i (
// 0   a c f i k
// )   a c f i
// )   a c f
// )   a c
// )   a
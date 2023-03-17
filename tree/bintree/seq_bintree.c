#include <stdio.h>
#include <stdlib.h>

#define DataType int

#define Placeholder -1

struct SeqBinTree {
    int MAXNUM;
    int n;  // 结点的实际个数
    DataType* nodelist;
};

typedef struct SeqBinTree* PSeqBinTree;


PSeqBinTree createNullTree_seq(int m) {
    PSeqBinTree patree = (PSeqBinTree)malloc(sizeof(struct SeqBinTree));
    if (patree != NULL) {
        patree->nodelist = (DataType*)malloc(sizeof(DataType) * m);

        for (int i = 0; i < m; i++)
            patree->nodelist[i] = Placeholder;    

        if (patree->nodelist) {
            patree->MAXNUM = m;
            patree->n = 0;
            return patree;
        } else
            free(patree);
    }
    printf("Out of space!!\n");
    return NULL;
}

int parent_seq(PSeqBinTree t, int p) {
    if (p < 0 || p >= t->n)
        return -1;
    return (p - 1) / 2;
}

int leftChild_seq(PSeqBinTree t, int p) {
    if (p < 0 || p >= t->n)
        return -1;
    return 2 * p + 1;
}

int rightChild_seq(PSeqBinTree t, int p) {
    if (p < 0 || p >= t->n)
        return -1;
    return 2 * p + 2;
}

int visit(PSeqBinTree t, int p){
    printf("%d\n", t->nodelist[p]);
}

void preOrder(PSeqBinTree t, int p){
    
}

int main(){
    createNullTree_seq(10);
}
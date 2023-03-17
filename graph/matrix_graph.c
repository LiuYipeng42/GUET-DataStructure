#include <stdio.h>
#include <stdlib.h>

#define VN 6  // vetex num

#define MAX 999999

typedef char VexType;

typedef int AdjType;

struct Vertex {
    VexType data;
    int mark;
};

typedef struct Vertex* PVertex;

struct GraphMatrix {
    PVertex vexs[VN];      // 全部顶点
    AdjType arcs[VN][VN];  // 边权值
};

typedef struct GraphMatrix* PGraph;

// 最小生成树的边类型
struct Edge {
    int start_vex, stop_vex;
    int weight;
};

typedef struct Edge* PEdge;

struct DPath {
    AdjType length;
    int prevex;
};

typedef struct DPath* PDPath;

struct FPath {
    AdjType a[VN][VN];
    int nextvex[VN][VN];
};

typedef struct FPath* PFPath;

// 获取顶点表的第一个顶点
PVertex firstVertex(PGraph g) {
    return g->vexs[0];
}

// 获取顶点表中 vi 顶点的后一个顶点
PVertex nextVertex(PGraph g, PVertex vi) {
    for (int i = 0; i < VN - 1; i++) {
        if (g->vexs[i]->data == vi->data)
            return g->vexs[i + 1];
    }
    return NULL;
}

// 找到顶点 v 的第一条边上的另一端顶点
PVertex firstAdjacent(PGraph g, PVertex v) {
    for (int i = 0; i < VN; i++) {
        if (g->vexs[i]->data == v->data) {
            for (int j = 0; j < VN; j++) {
                if (g->arcs[i][j] != MAX && g->arcs[i][j] != 0)
                    return g->vexs[j];
            }
        }
    }
}

// 找到顶点 vi 与顶点 vj 为端点的边，以顶点 vi 为端点的下一条边
PVertex nextAdjacent(PGraph g, PVertex vi, PVertex vj) {
    for (int i = 0; i < VN; i++) {
        if (g->vexs[i]->data == vi->data) {
            for (int j = 0; j < VN; j++) {
                if (g->vexs[j]->data == vj->data) {
                    // 找到了顶点 vi 与顶点 vj 在顶点表中的坐标
                    // 找下一条边
                    for (int offset = 1; j + offset < VN; offset++) {
                        if (g->arcs[i][j + offset] != MAX &&
                            g->arcs[i][j + offset] != 0)
                            return g->vexs[j + offset];
                    }
                }
            }
        }
    }
    return NULL;
}

void dfs(PGraph g, PVertex v) {
    PVertex v1;
    v->mark = 1;
    printf("%c\n", v->data);
    for (v1 = firstAdjacent(g, v); v1 != NULL; v1 = nextAdjacent(g, v, v1)) {
        if (v1->mark == 0) {
            dfs(g, v1);
        }
    }
}

void dft(PGraph g) {
    PVertex v;
    for (v = firstVertex(g); v != NULL; v = nextVertex(g, v)) {
        if (v->mark == 0) {
            dfs(g, v);
        }
    }
}

#define en_queue(v)  \
    queue[rear] = v; \
    rear = (rear + 1) % VN;
#define de_queue front = (front + 1) % VN;

void bfs(PGraph g, PVertex v) {
    PVertex v1, v2;
    PVertex queue[VN];
    int front = 0;
    int rear = 0;

    en_queue(v);
    while (front != rear) {
        v1 = queue[front];
        de_queue;
        printf("%c\n", v1->data);

        if (v1->mark == 1)
            continue;
        v1->mark = 1;

        v2 = firstAdjacent(g, v1);
        while (v2 != NULL) {
            if (v2->mark == 0)
                en_queue(v2);
            v2 = nextAdjacent(g, v1, v2);
        }
    }
}

void bft(PGraph g) {
    PVertex v;
    for (v = firstVertex(g); v != NULL; v = nextVertex(g, v)) {
        if (v->mark == 0) {
            bfs(g, v);
        }
    }
}

void prim(PGraph g, PEdge mst[]) {
    int i, j, min, vx, vy;
    int weight;
    PEdge edge;

    // 初始化顶点 0 到其余顶点的边
    // 0 到 0 的边不需要，所以长度为 VN - 1
    for (i = 0; i < VN - 1; i++) {
        mst[i] = (PEdge)malloc(sizeof(struct Edge));
        mst[i]->start_vex = 0;
        mst[i]->stop_vex = i + 1;
        mst[i]->weight = g->arcs[0][i + 1];
    }

    // mst[] 的前 i 项为已经确定的最小生成树的边，每一项的 stop_vex
    // 最小生成树的顶点 i 之后的都是已经放入最小生成树的顶点到此顶点的最短距离
    for (i = 0; i < VN - 1; i++) {
        // 找到 i 之后的最小的距离，
        // 这个最小距离就是已放入最小生生成树的全部顶点到其余顶点的最短
        // 要把此最短距离的顶点放入最小生生成树
        weight = MAX;
        min = i;
        for (j = i; j < VN - 1; j++) {
            if (mst[j]->weight < weight) {
                weight = mst[j]->weight;
                min = j;
            }
        }

        // 将最短的边放入第 i 个位置
        edge = mst[min];
        mst[min] = mst[i];
        mst[i] = edge;

        // 更新 i 之后顶点的最小距离
        vx = mst[i]->stop_vex;  // 新加入的顶点序号
        for (j = i + 1; j < VN - 1; j++) {
            vy = mst[j]->stop_vex;
            weight = g->arcs[vx][vy]; // 新加入顶点与 vy 顶点的权值
            if (weight < mst[j]->weight) {
                mst[j]->weight = weight;
                mst[j]->start_vex = vx;
            }
        }
    }

    for (int i = 0; i < VN - 1; i++)
        printf("%d %d %d\n", mst[i]->start_vex, mst[i]->stop_vex,
               mst[i]->weight);
}

int kruskal(PGraph g, PEdge mst[]) {
    int i, j, num = 0, start, stop;
    int minweight;

    // status[i] = j 表明，顶点 i 属于以顶点 j 为代表的连通子图
    int status[VN];
    // 每个顶点都属于以自己代表的连通子图
    for (i = 0; i < VN; i++)
        status[i] = i;

    while (num < VN - 1) {
        minweight = MAX;
        // 找到最短的边
        // 因为是无向图，所以只需要遍历矩阵的右上半，且不包含主对角线
        for (i = 0; i < VN - 1; i++) {
            for (j = i + 1; j < VN; j++) {
                if (g->arcs[i][j] < minweight) {
                    start = i;
                    stop = j;
                    minweight = g->arcs[i][j];
                }
            }
        }

        // while 循环结束前得到最短的边是 MAX，则表明没有最小生成树
        if (minweight == MAX)
            return 0;

        // 两者不相等表明不属于同一个连通子图
        // 就将得到的边放入 mst 中
        if (status[start] != status[stop]) {
            mst[num] = (PEdge)malloc(sizeof(struct Edge));
            mst[num]->start_vex = start;
            mst[num]->stop_vex = stop;
            mst[num]->weight = g->arcs[start][stop];
            num++;

            // 将 stop 顶点所在的连通子图变为 start 顶点所在的连通子图
            j = status[stop];  // 保存 stop 顶点所在的连通子图序号
            for (i = 0; i < VN; i++)
                if (status[i] == j)
                    status[i] = status[start];
        }

        // 在图中删除已加入最小生成树的边，
        // 或此最短边的顶点在同一个连通子图中，要将此边删除
        g->arcs[start][stop] = MAX;
    }

    for (int i = 0; i < VN - 1; i++)
        printf("%d %d %d\n", mst[i]->start_vex, mst[i]->stop_vex,
               mst[i]->weight);

    return 1;
}

void init(PGraph g, PDPath dist[]) {
    int i;
    dist[0] = (PDPath)malloc(sizeof(struct DPath));
    dist[0]->length = 0;
    dist[0]->prevex = 0;
    g->arcs[0][0] = 1;
    for (i = 1; i < VN; i++) {
        dist[i] = (PDPath)malloc(sizeof(struct DPath));
        dist[i]->length = g->arcs[0][i];
        if (dist[i]->length != MAX)
            dist[i]->prevex = 0;
        else
            dist[i]->prevex = -1;
    }
}

int dijkstra(PGraph g, PDPath dist[]) {
    // g->arcs[i][i] 是对角线元素，因为对角线元素恒为 0 ，
    // 所以将对角线元素作为是否已经找到到达 i 顶点最短距离的标记
    // 若为 1 。表明已经找到最短距离

    // dist[i] 为从顶点 0 到顶点 i 的最短距离和前驱顶点

    int i, j, mv;
    AdjType minw;
    // 在 dist 数组中初始化顶点 0 到其余顶点的距离与前驱顶点
    init(g, dist);
    // 每一次得到一个顶点 0 到另一个顶点，共需 VN - 1 次
    for (i = 1; i < VN; i++) {
        // 找到顶点 0 到 U-V 集合（未找到最短距离的顶点集合）中的顶点的距离
        // 的最短距离
        minw = MAX;
        mv = 0;
        for (j = 1; j < VN; j++) {
            // 没有找到到达顶点 j 的最短距离，且距离小于当前最短距离
            if (g->arcs[j][j] == 0 && dist[j]->length < minw) {
                mv = j;
                minw = dist[j]->length;
            }
        }

        // 顶点 0 与 U-V 集合中的顶点不连通
        if (mv == 0)
            break;

        // 标记 mv 顶点，表明已经找到顶点 0 到顶点 mv 的最短距离
        g->arcs[mv][mv] = 1;
        // 更新顶点 0 到 U-V 集合中的顶点 的距离
        for (j = 1; j < VN; j++) {
            if (g->arcs[j][j] == 0 && dist[j]->length > dist[mv]->length + g->arcs[mv][j]) {
                dist[j]->prevex = mv;
                dist[j]->length = dist[mv]->length + g->arcs[mv][j];
            }
        }
    }

    for (int k = 0; k < VN; k++) {
        if (dist[k]->length != MAX)
            printf("(%d %d) ", dist[k]->length, dist[k]->prevex);
        else
            printf("(-, %d) ", dist[k]->prevex);
    }
    printf("\n");
}

void floyd(PGraph g, PFPath pfpath) {
    int i, j, k;

    // 初始化最短距离矩阵 a，与路由矩阵 nextvex
    // nextvex[i][j] 表明从顶点 i 到顶点 j 的顶点 i 的后继顶点
    for (i = 0; i < VN; i++) {
        for (j = 0; j < VN; j++) {
            if (g->arcs[i][j] != MAX)
                pfpath->nextvex[i][j] = j;
            else
                pfpath->nextvex[i][j] = -1;
            pfpath->a[i][j] = g->arcs[i][j];
        }
    }

    for (k = 0; k < VN; k++) {
        // 经过中间顶点 k ，更新最短距离矩阵 a
        // a[i][j] 表示从顶点 i 到顶点 j 的路径上经过的顶点序号不大于 k
        // 的最短路径长度
        for (i = 0; i < VN; i++) {
            for (j = 0; j < VN; j++) {
                if ((pfpath->a[i][k] >= MAX) || (pfpath->a[k][j] >= MAX))
                    continue;
                if (pfpath->a[i][j] > (pfpath->a[i][k] + pfpath->a[k][j])) {
                    pfpath->a[i][j] = pfpath->a[i][k] + pfpath->a[k][j];
                    // 因为要先经过顶点 k ，再到达顶点 j ，nextvex[i][k] 的意义就是到达顶点 k 要到达的下一个顶点
                    // 所以 nextvex[i][j] 的值要变为 nextvex[i][k]
                    pfpath->nextvex[i][j] = pfpath->nextvex[i][k];
                }
            }
        }
    }

    for (i = 0; i < VN; i++) {
        for (j = 0; j < VN; j++) {
            if (pfpath->a[i][j] != MAX)
                printf("%d ", pfpath->a[i][j]);
            else
                printf("- ");
        }

        printf("\n");
    }
}

int main() {
    // 带权图
    // 两个顶点之间不存在边，则为 MAX
    // 两个顶点之间存在边，为边的权值
    int arcs[VN][VN] = {
        {0, 50, 10, MAX, 45, MAX},   {MAX, 0, 15, MAX, 5, MAX},
        {20, MAX, 0, 15, MAX, MAX},  {MAX, 20, MAX, 0, 35, MAX},
        {MAX, MAX, MAX, 30, 0, MAX}, {MAX, MAX, MAX, 3, MAX, 0}};

    // 非带权图
    // int arcs[VN][VN] = {{0, 1, 0, 0, 0},
    //                   {1, 0, 0, 0, 1},
    //                   {0, 1, 0, 1, 0},
    //                   {1, 0, 0, 0, 0},
    //                   {0, 0, 0, 1, 0}};

    PVertex vexs[VN];
    VexType vexData[VN] = {'0', '1', '2', '3', '4', '5'};

    for (int i = 0; i < VN; i++) {
        vexs[i] = (PVertex)malloc(sizeof(struct Vertex));
        vexs[i]->data = vexData[i];
        vexs[i]->mark = 0;
    }

    PGraph g = (PGraph)malloc(sizeof(struct GraphMatrix));

    for (int i = 0; i < VN; i++) {
        for (int j = 0; j < VN; j++)
            g->arcs[i][j] = arcs[i][j];
        g->vexs[i] = vexs[i];
    }

    // bft(g);

    // PEdge mst[VN - 1];
    // kruskal(g, mst);

    // PDPath dist[VN];
    // dijkstra(g, dist);

    PFPath pfpath = (PFPath)malloc(sizeof(struct FPath));

    floyd(g, pfpath);
}

// (0 0) (45 3) (10 0) (25 2) (45 0) (-, -1)
/* 题目
            最短路
*   描述
            给定一张 n 个点的无向带权图，节点的编号从 1 至 n，
     求从 S 到 T 的最短路径长度。
*   输入格式
            第一行 4 个数 n,m,S,T，分别表示点数、边数、起点、终点。
            接下来 m 行，每行 3 个正整数 u,v,w，描述一条 u 到 v 的双向边，边权为 w。
            保证 1<=u,v<=n。
*   输出格式
            输出一行一个整数，表示 S 到 T 的最短路。
*   输入样例
            7 11 5 4
            2 4 2
            1 4 3
            7 2 2
            3 4 3
            5 7 5
            7 3 3
            6 1 1
            6 3 4
            2 4 3
            5 6 3
            7 2 1
*   输出样例
            7
*   限制
            本题共设置 12 个测试点。
            对于前 10 个测试点，保证 n<=2500，m<=6200，
     对于每条边有 w<=1000。这部分数据有梯度。
            对于所有的 12 个测试点，保证 n<=100,000，m<=250,000。
            时间：4 sec
            空间：256 MB
*   提示
            [本题是 Dijkstra 算法的模板练习题。]
            [使用朴素的 Dijkstra 算法可以通过前 10 个测试点。]
            [使用堆或__std::priority_queue__优化的 Dijkstra 算法可以通过所有测试点。]
*   我的思路
            这道题比原本的dijkstra 算法要简单，因为原始的dijkstra 算法用于解决
     单源最短路径问题，图是有向的，而这道题要求用dijkstra 算法计算一个
     无向图中两个点的最短路径，而且从题意看，一定会找到最短路径，
     即图肯定是连通的，所以本题非常简单。
            唯一的难点是，从示例可以看出，给定的图是有重边的。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

#define INFINITY 0x7fffffff

typedef struct adjoining_point
{
    int id;         // 邻接点的内存索引
    int weight;     // 与邻接点相连的边权
    struct adjoining_point *next;
}adjoining_point_s;

typedef struct point
{
    bool in_heap;
    int dad;
    int weight;  // 可以表示为相邻两点的权重，也可以是最短路径中的权重
    int heap_loc; // 记录该点在堆中的位置，方便做上滤
    adjoining_point_s *ap; // 挂与该点相邻的所有点
}point_s;

typedef struct edge
{
    int pa;
    int pb;
    int weight;
}edge_s;

int g_point_cnt;
int g_edge_cnt;
int g_src_point;
int g_dst_point;

edge_s* g_edge_mem;
point_s* g_adjoining_table; // 按序保存所有点以及每个点自己的所有邻接点
int* g_heap; // 只记录点在内存中的索引

int g_idx; // 与g_ap_mem 配合使用，相当于分配内存
adjoining_point_s* g_ap_mem; // 存储所有需要挂链的邻接点

/* 小根堆
*   要更新沿途挪动过的点各自在堆中的位置
*   更新是否在堆中的标记
*/
int delete_heap_peak()
{
    int i, child, peak, tmp, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_adjoining_table[peak].in_heap = false;
    g_heap[1] = g_heap[heap_size];
    g_adjoining_table[g_heap[heap_size]].heap_loc = 1;
    g_heap[0] = --heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_adjoining_table[g_heap[child]].weight >= g_adjoining_table[g_heap[child+1]].weight) {
            child++;
        }
        if (g_adjoining_table[g_heap[i]].weight <= g_adjoining_table[g_heap[child]].weight) {
            break;
        }

        tmp = g_heap[child];
        g_heap[child] = g_heap[i];
        g_heap[i] = tmp;

        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[child]].heap_loc = child;
    }

    return peak;
}

/* 小根堆
*   针对某个点的上滤
*   还要更新沿途挪动过的点各自在堆中的位置
*/
void percolate_up(int heap_loc)
{
    int i, dad, tmp;

    for (i = heap_loc; (i>>1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_adjoining_table[g_heap[i]].weight >= g_adjoining_table[g_heap[dad]].weight) {
            break;
        }

        tmp = g_heap[i];
        g_heap[i] = g_heap[dad];
        g_heap[dad] = tmp;

        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[dad]].heap_loc = dad;
    }

    return;
}

void shortest_path_process()
{
    int tmp_idx, tmp_weight;
    adjoining_point_s *cur, *next;

    if (g_src_point == g_dst_point) {
        printf("0\n");
        return;
    }

    // 初始化起点
    g_adjoining_table[g_src_point].weight = 0;
    percolate_up(g_adjoining_table[g_src_point].heap_loc);

    while (1) {
        tmp_idx = delete_heap_peak();
        if (-1 == tmp_idx) {
            printf("Over!\n");
            return;
        }
        if (tmp_idx == g_dst_point) {
            printf("%d\n", g_adjoining_table[tmp_idx].weight);
            return;
        }

        // 更新邻近点(如果没有任何邻近点，那就是非连通图)
        cur = g_adjoining_table[tmp_idx].ap;
        while (NULL != cur) {
            next = cur->next;
            if (!g_adjoining_table[cur->id].in_heap) {
                cur = next;
                continue;
            }
            /* tips: cur->weight 表示这条边本身的权重
                    *   g_adjoining_table[cur->id].weight 表示该邻近点当前的权重
                    */
            tmp_weight = g_adjoining_table[tmp_idx].weight + cur->weight;
            if (tmp_weight < g_adjoining_table[cur->id].weight) {
                g_adjoining_table[cur->id].weight = tmp_weight;
                g_adjoining_table[cur->id].dad = tmp_idx;
                percolate_up(g_adjoining_table[cur->id].heap_loc);
            }

            cur = next;
        }
    }

    return;
}

void config_adjoining_point(int tmp_point, int tmp_ap, int weight)
{
    adjoining_point_s *next;

    next = g_adjoining_table[tmp_point].ap;
    g_adjoining_table[tmp_point].ap = g_ap_mem + g_idx;
    g_idx++;

    g_adjoining_table[tmp_point].ap->id = tmp_ap;
    g_adjoining_table[tmp_point].ap->weight = weight;
    g_adjoining_table[tmp_point].ap->next = next;

    return;
}

void create_adjoining_table()
{
    int i;
    int tmp_a, tmp_b, tmp_w;

    // 遍历所有的边，用于生成邻接表
    for (i = 0; i < g_edge_cnt; i++) {
        tmp_a = g_edge_mem[i].pa;
        tmp_b = g_edge_mem[i].pb;
        tmp_w = g_edge_mem[i].weight;

        // 因为是无向图，所以两个点都要配置
        config_adjoining_point(tmp_a, tmp_b, tmp_w);
        config_adjoining_point(tmp_b, tmp_a, tmp_w);
    }

    return;
}

void init()
{
    int i;

    scanf("%d %d %d %d", &g_point_cnt, &g_edge_cnt, &g_src_point, &g_dst_point);
    getchar();

    g_edge_mem = new edge_s[g_edge_cnt];
    for (i = 0; i < g_edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].pa, &g_edge_mem[i].pb, &g_edge_mem[i].weight);
        getchar();
    }

    // 点的序号从1 开始
    g_adjoining_table = new point_s[g_point_cnt+1];
    g_heap = new int[g_point_cnt+1];
    for (i = 1; i <= g_point_cnt; i++) {
        g_heap[i] = i;

        g_adjoining_table[i].in_heap = true;
        g_adjoining_table[i].dad = i;
        g_adjoining_table[i].weight = INFINITY;
        g_adjoining_table[i].heap_loc = i;
        g_adjoining_table[i].ap = NULL;
    }
    g_heap[0] = g_point_cnt;

    // 每条边两个点，且为无向图，所以准备2*g_edge_cnt 个点来配置邻接表
    g_idx = 0;
    g_ap_mem = new adjoining_point_s[2*g_edge_cnt];
    create_adjoining_table();
    
    return;
}

void end()
{
    delete[] g_edge_mem;
    delete[] g_adjoining_table;
    delete[] g_heap;
    delete[] g_ap_mem;

    return;
}

int main() 
{
    init();

    shortest_path_process();

    end();

    return 0;
}

/* MST kruskal算法实现
*     二叉堆
*     并查集
*  要求能够判断出所给的边是否可以组成连通图
*  未来改进
*     使用斐波那契堆选边
*  输入
*     N  表示有多少条边
*     45 0 1    权重 点序号 点序号
*     ...（一共N行表示具体的边的权重以及组成边的点的序号）
*  点序号范围： [0, 2*N)
*  注意
*     输入的数据不保证一定是连通图，代码需要自己检查出是否连通
*     本例只告诉有哪些边，没直接告诉有哪些点，不同的边可能有部分点是重复的
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct point
{
    int rank;       // 秩，用于并查集
    int dad_index;  // 父节点内存索引，也是父节点的点序号，用于并查集 
}point_s;

typedef struct edge
{
    int pa_index;  // 该边所连接的两个点的内存索引，也是点的点序号
    int pb_index;
    int weight;    // 边的权重
    bool chose;    // 是否选中作为mst的一条边
}edge_s;

static int g_edge_cnt;
static int g_point_max_cnt; // 给定边的情况下，所拥有的最多点的个数为：g_point_max_cnt = 2 * g_edge_cnt
static edge_s* g_edge_mem;
static point_s* g_point_mem;

// g_heap[0]记录堆中节点数量
static int* g_heap;

static int find_set(int point_idx)
{
    // 递归基
    if (-1 == g_point_mem[point_idx].dad_index) {
        return point_idx;
    }

    // 路径压缩
    g_point_mem[point_idx].dad_index = find_set(g_point_mem[point_idx].dad_index);
    return g_point_mem[point_idx].dad_index;
}

static void set_union(int seta_root_idx, int setb_root_idx)
{
    if (g_point_mem[setb_root_idx].rank < g_point_mem[seta_root_idx].rank) {
        g_point_mem[setb_root_idx].dad_index = seta_root_idx;
        return;
    }

    g_point_mem[seta_root_idx].dad_index = setb_root_idx;
    if (g_point_mem[seta_root_idx].rank == g_point_mem[setb_root_idx].rank) {
        g_point_mem[setb_root_idx].rank++;
    }

    return;
}

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp_mem_idx;

    tmp_mem_idx = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp_mem_idx;

    return;
}

// 小根堆：返回边的内存索引
static int delete_heap_peak()
{
    int i, child, peak, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    // 下滤
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child+1]].weight) {
            child++;
        }
        if (g_edge_mem[g_heap[i]].weight <= g_edge_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// 小根堆（最小生成树）
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child+1]].weight) {
                child++;
            }
            if (g_edge_mem[g_heap[j]].weight <= g_edge_mem[g_heap[child]].weight) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

// 要考虑非连通图的情况
static void create_mst()
{
    int i;
    int tmp_edge_idx;
    int seta_rt_idx, setb_rt_idx;
    int point_cnt, accepted_edge_cnt;

    // 统计当前整个图中所拥有的点的个数
    point_cnt = 0;
    for (i = 0; i < g_point_max_cnt; i++) {
        if (-2 != g_point_mem[i].dad_index) {
            point_cnt++;
        }
    }

    accepted_edge_cnt = 0;

    // 最小生成树的边数和图中所有点的个数对应公式： edge_cnt = point_cnt - 1
    while (accepted_edge_cnt < point_cnt - 1) {
        tmp_edge_idx = delete_heap_peak();
        if (-1 == tmp_edge_idx) {
            break;
        }

        seta_rt_idx = find_set(g_edge_mem[tmp_edge_idx].pa_index);
        setb_rt_idx = find_set(g_edge_mem[tmp_edge_idx].pb_index);

        if (seta_rt_idx != setb_rt_idx) {
            set_union(seta_rt_idx, setb_rt_idx);
            g_edge_mem[tmp_edge_idx].chose = true;
            accepted_edge_cnt++;
        }
    }

    // 非连通图
    if (accepted_edge_cnt < point_cnt - 1) {
        printf("非连通图，无法获取最小生成树\n");
        return;
    }

    // 连通图，并且计算出了最小生成树
    for (i = 0; i < g_edge_cnt; i++) {
        if (!g_edge_mem[i].chose) {
            continue;
        }
        printf("edge: %d, pa: %d, pb: %d, weight: %d\n", 
            i, g_edge_mem[i].pa_index, g_edge_mem[i].pb_index, g_edge_mem[i].weight);
    }

    return;
}

static void init()
{
    int i;

    scanf("%d", &g_edge_cnt);
    getchar();

    g_edge_mem = new edge_s[g_edge_cnt];
    g_heap = new int[g_edge_cnt + 1];

    g_point_max_cnt = 2 * g_edge_cnt;
    g_point_mem = new point_s[g_point_max_cnt];
    for (i = 0; i < g_point_max_cnt; i++) {
        g_point_mem[i].dad_index = -2;
    }

    g_heap[0] = g_edge_cnt;
    for (i = 0; i < g_edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].weight, &g_edge_mem[i].pa_index, &g_edge_mem[i].pb_index);
        getchar();
        g_edge_mem[i].chose = false;

        // g_heap[0]记录堆中总节点个数，堆中其他位置记录的是每条边在内存中的索引
        // 这个循环中的i从0开始，但堆中元素从1开始
        g_heap[i + 1] = i;

        g_point_mem[g_edge_mem[i].pa_index].rank = 0;
        g_point_mem[g_edge_mem[i].pa_index].dad_index = -1;
        
        g_point_mem[g_edge_mem[i].pb_index].rank = 0;
        g_point_mem[g_edge_mem[i].pb_index].dad_index = -1;
    }

    return;
}

static void end()
{
    delete[] g_edge_mem;
    delete[] g_heap;
    delete[] g_point_mem;

    return;
}

void mst_kruskal()
{
    init();

    create_heap();
    create_mst();

    end();

    return;
}
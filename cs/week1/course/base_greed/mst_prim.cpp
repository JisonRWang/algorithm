/* MST prim算法实现
*    prim算法的效率不如kruskal算法
*    代码基本仿照《算法导论》中进行
*    与其他代码使用堆的方式不同，prim中使用堆时，每次执行deletePeak操作之前都要重新恢复一下堆序，因为
每次更新跨边都会影响已有的堆序结构
*    设，构建生成树时，树所在的集合为A
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

#define INFINITY 0x7fffffff

typedef struct edge
{
    int weight;
    int pa_idx;
    int pb_idx;
}edge_s;

typedef struct point
{
    bool in_heap;   // 记录当前点是否在堆中
    int  weight;    // 记录该点（在堆中）与集合A中的点组成的跨边中，权重最小的跨边的权重
    int  dad_idx;   // 能与该点组成权重最小的跨边的点的内存索引，这个点在A中
}point_s;

// 统计当前图中点的个数。由于输入没有直接告诉点的个数，所以需要自己计算有多少个点
static int g_point_cnt;

// 一维数组当二维数组使用，记录各个点之间的邻接关系，元素值为边的权重
static int* g_point_rel;

// 存储各个点的内存
static point_s* g_point_mem;

// 小根堆，记录各个点在内存中的索引，第0个元素记录堆中节点个数
static int* g_heap;

static void swap_heap(int heap_dad_idx, int heap_child_idx) 
{
    int tmp_mem_idx;

    tmp_mem_idx = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp_mem_idx;

    return;
}

// 小根堆
static void recover_heap_order()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = (heap_size >> 1); i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_point_mem[g_heap[child]].weight >= g_point_mem[g_heap[child + 1]].weight) {
                child++;
            }
            if (g_point_mem[g_heap[j]].weight <= g_point_mem[g_heap[child]].weight) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

static int delete_heap_peak()
{
    int peak;
    int i, child, heap_size;

    // 堆中节点的数据会被修改，因此每次delete_peak之前，都先重新恢复堆序
    recover_heap_order();

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;
    g_point_mem[peak].in_heap = false;

    // 下滤（小根堆）
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_point_mem[g_heap[child]].weight >= g_point_mem[g_heap[child + 1]].weight) {
            child++;
        }
        if (g_point_mem[g_heap[i]].weight <= g_point_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// By prim
static void create_mst()
{
    int i, offset;
    int tmp_mem_idx;
    int tmp_heap_idx;

    // 偷懒，将从堆中取出的点再依次放到堆数组的末尾，以便最后输出。g_heap[0]此时等于g_point_cnt
    tmp_heap_idx = g_heap[0]; 

    // 随便选取一个点作为起始
    tmp_mem_idx = g_heap[1];
    g_point_mem[tmp_mem_idx].weight = 0;

    // 堆中存的是所有点
    while (g_heap[0] > 0) {
        tmp_mem_idx = delete_heap_peak();

        // 判断是否为连通图
        // 每次从堆中取出一个点之后，都会更新堆中其余可以与集合A形成跨边的点的最小权重。所以如果是连通图，
        // 那么堆中肯定要有点的权重不为无穷大；如果出现了从堆中取出的点的权重为无穷大，就说明这个点与A中
        // 任何一个点都没有边连接，即无连通，因此无法生成最小生成树
        if (INFINITY == g_point_mem[tmp_mem_idx].weight) {
            printf("非连通图\n");
            return;
        }

        g_heap[tmp_heap_idx--] = tmp_mem_idx;

        // 从堆中取出一个点加入到A后，更新堆中与该点相邻点的最小权重
        offset = tmp_mem_idx * g_point_cnt;
        for (i = 0; i < g_point_cnt; i++) {
            // 找与tmp_mem_idx点有边相连并且在堆中的点
            // tips: 只有堆中的点才能与A中的点形成跨边，如果都是A中的点，会成环
            if (0 == g_point_rel[offset + i] ||
                false == g_point_mem[i].in_heap) {
                continue;
            }

            // 在堆中找到合适的点，更新该点与A的跨边的最小权重
            if (g_point_mem[i].weight > g_point_rel[offset + i]) {
                g_point_mem[i].weight = g_point_rel[offset + i];
                g_point_mem[i].dad_idx = tmp_mem_idx;
            }
        }
    }

    // 输出
    for (i = g_point_cnt; i > 0; i--) {
        // 起始点没有权重也没有父节点，没必要输出
        if (-1 == g_point_mem[g_heap[i]].dad_idx) {
            continue;
        }
        printf("weight: %d, pa: %d, pb: %d\n", 
            g_point_mem[g_heap[i]].weight, g_heap[i], g_point_mem[g_heap[i]].dad_idx);
    }

    return;
}

// 统计点的个数
static int count_points(edge_s* edge_arr, int edge_cnt)
{
    int* point_arr;
    int i, point_cnt, tmp_cnt;

    tmp_cnt = edge_cnt << 1;
    point_arr = new int[tmp_cnt];
    for (i = 0; i < tmp_cnt; i++) {
        point_arr[i] = 0;
    }

    for (i = 0; i < edge_cnt; i++) {
        point_arr[edge_arr[i].pa_idx]++;
        point_arr[edge_arr[i].pb_idx]++;
    }

    point_cnt = 0;
    for (i = 0; i < tmp_cnt; i++) {
        if (0 == point_arr[i]) {
            continue;
        }
        point_cnt++;
    }

    delete[] point_arr;

    return point_cnt;
}

static void init()
{
    int tmp;
    edge_s* edge_arr;
    int i, edge_cnt, tmp_pa, tmp_pb;

    scanf("%d", &edge_cnt);
    getchar();

    edge_arr = new edge_s[edge_cnt];
    for (i = 0; i < edge_cnt; i++) {
        scanf("%d %d %d", &edge_arr[i].weight, &edge_arr[i].pa_idx, &edge_arr[i].pb_idx);
        getchar();
    }

    g_point_cnt = count_points(edge_arr, edge_cnt);

    tmp = g_point_cnt * g_point_cnt;
    g_point_rel = new int[tmp];
    for (i = 0; i < tmp; i++) {
        g_point_rel[i] = 0;
    }
    for (i = 0; i < edge_cnt; i++) {
        tmp_pa = edge_arr[i].pa_idx;
        tmp_pb = edge_arr[i].pb_idx;

        // 无向图，需要双向设置
        g_point_rel[tmp_pa * g_point_cnt + tmp_pb] = edge_arr[i].weight;
        g_point_rel[tmp_pb * g_point_cnt + tmp_pa] = edge_arr[i].weight;
    }

    g_heap = new int[g_point_cnt + 1];
    g_point_mem = new point_s[g_point_cnt];
    for (i = 0; i < g_point_cnt; i++) {
        g_heap[i + 1] = i;

        g_point_mem[i].in_heap = true;        // 初始状态直接在堆中
        g_point_mem[i].weight = INFINITY;     // 相当于无穷大
        g_point_mem[i].dad_idx = -1;          // 没有父节点（A中没有可以与该节点组成最小权重跨边的节点）
    }
    g_heap[0] = g_point_cnt;

    delete[] edge_arr;

    return;
}

static void end()
{
    delete[] g_point_rel;
    delete[] g_point_mem;
    delete[] g_heap;

    return;
}

void mst_prim()
{
    init();

    create_mst();

    end();

    return;
}
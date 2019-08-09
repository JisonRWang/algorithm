/* 题目
*     道路升级
*  描述
*     Z国有 n 个城市和 m 条双向道路，每条道路连接了两个不同的城市，保证所有城市之间都可以
通过这些道路互达。每条道路都有一个载重量限制，这限制了通过这条道路的货车最大的载重量。道路
的编号从 1 至 m 。巧合的是，所有道路的载重量限制恰好都与其编号相同。
*     现在，要挑选出若干条道路，将它们升级成高速公路，并满足如下要求：
*        所有城市之间都可以通过高速公路互达。
*        对于任意两个城市 u,v 和足够聪明的货车司机：只经过“高速公路”从 u 到达 v 能够装载货物
的最大重量，与经过“任意道路”从 u 到达 v 能够装载货物的“最大”重量相等。（足够聪明的司机只关注载重
量，并不在意绕路）
*     在上面的前提下，要求选出的道路数目尽可能少。
*     求需要挑选出哪些道路升级成高速公路（如果有多种方案请任意输出一种）。
*  输入
*     第一行 2 个用空格隔开的整数 n,m ，分别表示城市数目、道路数目。
*     第 2 行到第 m+1 行，每行 2 个用空格隔开的整数 u,v 描述一条从 u 到 v 的双向道路，第 i+1 行的道路的编号为 i 。
*     注意
*        数据只保证不存在连接的城市相同的道路（自环），并不保证不存在两条完全相同的边（重边）
*  输出
*     第一行一个整数 k ，表示升级成高速公路的道路数。
*     接下来 k 行每行一个整数，从小到大输出所有选出的道路的编号。
*  输入样例
*     3 3
*     1 2
*     2 3
*     1 3
*  输出样例
*     2
*     2
*     3
*  数据范围
*     对于 20% 的数据，保证 n≤5，m≤10。
*     对于 60% 的数据，保证 n≤1,000，m≤5,000。
*     对于 100% 的数据，保证 n≤200,000，m≤400,000。
*     时间限制：10 sec
*     空间限制：256 MB
*  提示
*     [提示1：真的可能有多种方案吗？]
*     [提示2：k 是否一定为 n-1 呢？（也就是说，选出的道路是否恰好构成了一棵树？）]
*     [提示3：这道题和最小生成树有什么关系呢？]
*  我的疑问
*     自环（从一个城市出发不经过另一座城市然后又回到这座城市？）和重边是什么意思？
*     第二个要求是什么意思，想说明什么（我的理解是，首先，道路在升级成高速公路前后的
载重量是不变的，假设uv之间有直接通路和绕路，而直接通路的载重量小于绕路，那么就不能将这条直接通路升级为高速公路。
而应该将uv最大载重量沿途的道路都升级为高速公路。即，题目要求应该抽象为：选出任意两个城市之间能够组成最大载重量
的道路，此时生成的树正好是最小生成树的反面，即最大生成树，组成最大生成树的道路要升级成高速公路）？
*     输入数据能否保证一定有足够数量的边连通两个城市？即是否会出现没有一条路连通某个城市的情况？看题目描述，应
该不会出现这种输入。
*  我的思路
*     uv之间的路沿途虽然每条路都是最大载重，但货车的实际载重由这条路径上的最小载重决定。
*     初步感觉，如果既要保证每座城市之间都可以通过高速公路互达，那就说明一定要由高速公路连通所有的这些城市，
而能够做到这点的只有生成树，所以我认为，选出的道路一定会构成一棵生成树。
*     题干中已经说明了，是连通图，所以一定有生成树
*     每条边的权重都不同，所以肯定只有一种方案
*     就是最大生成树
*     直接用kruskal算法求最大生成树即可
*     n个点，m条边，保证是连通图，这题比我自己出的题要简单
*        开辟一块内存，放所有的边
*        开辟一块内存，放所有的点
*        开辟一块内存，作为堆，堆中存边
*        使用并查集，查看点是否在同一个集合
*        使用大根堆，弹出的合理的边放到堆末尾
*        用一个变量记录符合条件的边的数量
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct point
{
    int dad_idx;
    int rank;
}point_s;

// 边的权重就是边在内存中的索引
typedef struct edge
{
    int pa_idx;   // 点在内存中的索引
    int pb_idx;
}edge_s;

static point_s* g_point_mem;
static edge_s* g_edge_mem;
static int* g_heap; // 第0个元素记录堆中节点个数

static int g_edge_cnt;
static int g_point_cnt;

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

//TODO 解决函数栈溢出问题
static int set_find(int point_idx)
{
    // 递归基
    if (point_idx == g_point_mem[point_idx].dad_idx) {
        return point_idx;
    }

    g_point_mem[point_idx].dad_idx = set_find(g_point_mem[point_idx].dad_idx);
    return g_point_mem[point_idx].dad_idx;
}

// 按秩合并
static void set_union(int set_root_a, int set_root_b)
{
    if (g_point_mem[set_root_a].rank < g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_a].dad_idx = set_root_b;
        return;
    }

    g_point_mem[set_root_b].dad_idx = set_root_a;
    if (g_point_mem[set_root_a].rank == g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_a].rank++;
    }

    return;
}

// 大根堆
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

    // 下滤（大根堆）
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_heap[child] <= g_heap[child + 1]) {
            child++;
        }
        if (g_heap[i] >= g_heap[child]) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// 创建最大生成树，题目已经保证是连通图
static void create_mbt()
{
    int i, heap_idx;
    int ac_edge_cnt;
    int edge_mem_idx;
    int root_a, root_b;

    // 偷懒，将可用边依次放到堆所在内存的末尾，最大的边在最后
    heap_idx = g_edge_cnt;

    ac_edge_cnt = 0;
    while (ac_edge_cnt < g_point_cnt - 1) {
        // 连通图，肯定有支撑树，所以不用判断edge_mem_idx是否为-1
        edge_mem_idx = delete_heap_peak();
        root_a = set_find(g_edge_mem[edge_mem_idx].pa_idx);
        root_b = set_find(g_edge_mem[edge_mem_idx].pb_idx);

        if (root_a == root_b) {
            continue;
        }
        set_union(root_a, root_b);
        ac_edge_cnt++;
        g_heap[heap_idx--] = edge_mem_idx;
    }

    // 输出
    printf("%d\n", ac_edge_cnt);
    for (i = heap_idx + 1; i <= g_edge_cnt; i++) {
        printf("%d\n", g_heap[i]);
    }

    return;
}

// 大根堆
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // 边的权重就是边在内存中的索引，g_heap存的就是边的索引，所以直接比就好
            if (child < heap_size &&
                g_heap[child] <= g_heap[child + 1]) {
                child++;
            }
            if (g_heap[j] >= g_heap[child]) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

static void init()
{
    int i;

    scanf("%d %d", &g_point_cnt, &g_edge_cnt);
    getchar();

    g_point_mem = new point_s[g_point_cnt + 1]; // 从题中看出，点的序号从第1个开始算
    g_edge_mem = new edge_s[g_edge_cnt + 1];    // 从题中看出，边的序号从第1个开始算
    g_heap = new int[g_edge_cnt + 1];

    for (i = 0; i <= g_point_cnt; i++) {
        g_point_mem[i].dad_idx = i;
        g_point_mem[i].rank = 0;
    }

    g_heap[0] = g_edge_cnt;
    for (i = 1; i <= g_edge_cnt; i++) {
        scanf("%d %d", &g_edge_mem[i].pa_idx, &g_edge_mem[i].pb_idx);
        getchar();
        g_heap[i] = i;
    }

    return;
}

static void end()
{
    delete[] g_point_mem;
    delete[] g_edge_mem;
    delete[] g_heap;

    return;
}

void road_upgrade()
{
    init();

    create_heap();
    create_mbt();

    end();

    return;
}
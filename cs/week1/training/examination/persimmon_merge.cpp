/* 题目
*      柿子合并
*   描述
*      又到了吃柿饼的季节。小莉的果园共有n棵柿子树，编号为1到n。最开始，这些柿子树之间都没有道路相连。
小莉现在规划出了 m 对中间可能修建双向道路的柿子树，用 m  个三元组(u,v,w) 表示，表示在编号为u 和 编号为v
的柿子树之间修建道路需要花费 w 元。
*      小莉决定在修完道路后，将能够直接或间接通过道路连接的柿子树划分为一个子集。并且，对于划分出的每一个
子集，用这个子集中的所有柿子树上长出的柿子做出一个柿饼。
*      小莉最终一共想要得到 k 个柿饼，请你帮他计算最小的修路费用是多少。
*   输入
*      第 1 行有三个整数 n ，m ，k ，含义见题目描述。
*      接下来 m 行，每行三个整数u ，v ，w ，描述每条可能修建的道路，含义如题所述。
*   输出
*      输出一行一个整数，表示小莉修路的最小花费。
*      如果小莉无论如何都不能做出 k 个柿饼，请输出−1 。
*   输入样例1
*      4 4 2
*      1 2 3
*      2 3 1
*      4 2 1
*      3 4 2
*   输出样例1
*      2
*   样例1解释
*      在 2，3 与 2，4 之间修建道路。
*      这样我们就可以将所有柿子制作成 2 个柿饼。
*   限制
*      对于30%的数据，1≤n≤100,1≤m≤1000；
*      对于100%的数据，1≤n≤10000,1≤m≤100000,1≤k≤10,1≤u,v≤n,0≤w≤10000。
*   提示
*      [稍微改一下kruskal算法就行辣]
*   我的思路
*      题目翻译
*          有n个点，编号1~n，规划了m条边，每条边用三元组(u,v,w)表示，uv是点编号，w是边的权重。
*          没说是不是连通图，要考虑非连通的情况
*              如果要1个柿饼，但有一个点没有任何边连接，那此时就应该输出-1
*          n个点，m条边，划分为k个集合，每个集合都是一颗最小生成树，k个集合互相之间不能合并
*          最后求的是k个集合权值之和
*      两个集合合并，会减少一个集合，生成一个集合，即每次两个集合合并，集合个数都减一
*      最开始的时候，n个点，就是n片森林，每片森林里只有一棵树，一片森林就是一个集合
*      通过道路连接的不同的树，构成一片森林
*      k > n，就算每片森林只有一棵树，也无法构成k片森林，此时返回-1
*      k == n，每片森林只有一棵树，恰好构成所需的k片森林，不需要任何道路连接，此时返回0
*      k < n，此时仍有可能返回-1，比如k=1但不是全连通图，则返回-1
*            依然按照kruskal算法的方式去合并，只不过每次合并都统计一下当前的集合个数（即森林个数），
如果等于k，输出所有森林的权重即为答案。
*      其实在理解的时候，可以把整片森林看成由一棵树组成的森林，这个集合所有的跨边都视为这一棵树的跨边，
这个想法在prim算法中很有效，但是在kruskal算法中不完全适用，因为kruskal算法要考虑成环的问题，那就必须
考虑森林内所有点了。
*            因为每次合并两个集合，都会减少一个集合，所以当k<n时，通过逐步合并两个集合，即每次减少一个
集合来使总集合个数逐步趋近并最终等于k。既然要求最终所有集合的权重加起来总和最小，也就意味着每次合并两个
集合的时候，连接这两个集合的边最小，这样才能保证在减少总集合个数的同时，集合内部的权重最小。
*      总体来说，本题依然是实现kruskal算法，只不过每次合并集合，都要统计当前总集合个数。
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct point
{
    int rank;
    int dad_idx;
}point_s;

typedef struct edge
{
    int pa;
    int pb;
    int weight;
}edge_s;

// 总集合个数，初始值为全部的点的个数，因为初始时每个点各自算一个集合（森林）
static int g_set_cnt;

// 点在内存中的序号从1开始
static point_s* g_point_mem;

// 边在内存中的序号从1开始
static edge_s* g_edge_mem;

// 第0个元素记录堆中总节点个数
static int* g_heap;

static int g_k;

static void flush_input_data(int edge_cnt)
{
    int i, tmp_a, tmp_b, tmp_c;

    for (i = 0; i < edge_cnt; i++) {
        scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_c);
        getchar();
    }

    return;
}

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

static int set_find(int point_idx)
{
    // 递归基
    if (point_idx == g_point_mem[point_idx].dad_idx) {
        return point_idx;
    }

    g_point_mem[point_idx].dad_idx = set_find(g_point_mem[point_idx].dad_idx);
    return g_point_mem[point_idx].dad_idx;
}

static void set_union(int set_root_a, int set_root_b)
{
    if (g_point_mem[set_root_a].rank > g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_b].dad_idx = set_root_a;
        return;
    }

    g_point_mem[set_root_a].dad_idx = set_root_b;
    if (g_point_mem[set_root_a].rank == g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_b].rank++;
    }

    return;
}

// 小根堆
static int delete_heap_peak()
{
    int i, peak, child, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child + 1]].weight) {
            child++;
        }
        if (g_edge_mem[g_heap[i]].weight <= g_edge_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// 小根堆
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child + 1]].weight) {
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

static void process()
{
    int set_cnt;
    int edge_idx;
    int sum_weight;
    int root_a, root_b;

    sum_weight = 0;
    set_cnt = g_set_cnt;
    while (set_cnt > g_k) {
        edge_idx = delete_heap_peak();
        if (-1 == edge_idx) {
            break;
        }

        root_a = set_find(g_edge_mem[edge_idx].pa);
        root_b = set_find(g_edge_mem[edge_idx].pb);
        if (root_a == root_b) {
            continue;
        }

        // 每次两个集合合并，总集合个数都减少一个
        set_union(root_a, root_b);
        set_cnt--;
        sum_weight += g_edge_mem[edge_idx].weight;
    }

    if (set_cnt != g_k) {
        printf("-1\n");
        return;
    }

    printf("%d\n", sum_weight);
    return;
}

static int init()
{
    int i, edge_cnt;

    scanf("%d %d %d", &g_set_cnt, &edge_cnt, &g_k);
    getchar();

    if (g_set_cnt < g_k) {
        flush_input_data(edge_cnt);
        return -1;
    }
    if (g_set_cnt == g_k) {
        flush_input_data(edge_cnt);
        return 0;
    }

    g_point_mem = new point_s[g_set_cnt + 1];
    for (i = 1; i <= g_set_cnt; i++) {
        g_point_mem[i].dad_idx = i;
        g_point_mem[i].rank = 0;
    }

    g_edge_mem = new edge_s[edge_cnt + 1];
    g_heap = new int[edge_cnt + 1];
    for (i = 1; i <= edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].pa, &g_edge_mem[i].pb, &g_edge_mem[i].weight);
        getchar();

        g_heap[i] = i;
    }
    g_heap[0] = edge_cnt;

    return 1;
}

static void end()
{
    delete[] g_point_mem;
    delete[] g_edge_mem;
    delete[] g_heap;

    return;
}

void persimmon_merge()
{
    int tmp;

    tmp = init();
    if (1 != tmp) {
        printf("%d\n", tmp);
        return;
    }

    create_heap();
    process();

    end();

    return;
}
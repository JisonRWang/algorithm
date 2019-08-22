/* 题目
            考题2
*   描述
            最优贸易问题。
            粽子国是一个盛产粽子的国度，共有 n 座城市，编号为 1 到 n，
     城市之间存在 m 条单向道路。每座城市都有粽子的贸易渠道，但
     是价格不尽相同。一般来说，第 i 座城市的粽子的购买和出售价
     格都为 a[i]。
            小粽来到了粽子国旅游，她准备从 1 号城市出发，并前往 n 号
     城市。途中，小粽可能会先在某个城市购买一个粽子，然后再在
     某个城市将其出售。小粽最多会进行一次这样的交易，当然也可
     以不进行这样的交易。如果小粽发现，不存在从 1 号城市到 n 号城
     市的路径，那么小粽会取消她的旅行计划。
            现在，请你帮忙计算小粽在粽子贸易中可能获得的最大收益。
*   输入格式
            第一行两个正整数 n,m，表示粽子国的城市数目和单向道路的数目。
            第二行共 n 个整数，以空格隔开，第 i 个数表示第 i 座城市粽子的价值。
            接下来 m 行，每行两个整数 u,v，表示存在一条从城市 u 到城市 v
     的单向道路。
*   输出格式
            输出一行一个整数，表示最大获利。如果没有进行任何交
     易，则输出0。
*   输入样例1
            2 2
            19 20
            1 2
            2 1
*   输出样例
            1
*   样例1 解释
            可以在 1 号城市买了粽子后，去 2 号城市出售。
*   输入样例2
            5 7
            4 3 5 6 1 
            1 2
            1 4
            2 3
            3 2
            3 5
            4 5
            5 4
*   输出样例2
            5
*   限制
            对于 30% 的数据，保证 n≤100；
            对于 60% 的数据，保证 n≤5000；
            对于 100% 的数据，保证 n≤10^5,m≤6n；
            时间限制：2 s
            空间限制：256 MB
*   我的思路
            所谓最大收益，就是低买高卖。
            本题必须先满足可以从起点走到终点，然后才是求最大收益。
     也就是在从起点到终点的所有可能方案中，找出收益最大的那个
     方案。题中说最多进行一次这样的交易，说明不能成环。
            参考https://www.cnblogs.com/wxjor/p/7280759.html
            因为是有向图，所以邻接表要同时记录出边和入边。
            先用dijkstra 算法计算从起点到每一个点的最短路径，使用出边去
     计算。虽然本题和最短路径没关系，但却需要用到最短路径的思想，
     因为这样才能保证从起点到每个点的路径中，沿途每个点的价格都
     是从起点到该点的过程中最小的(这样才能以最快是速度找出从起点
     到该点的路径中，价格最小的点，从起点到该点的最小价格肯定就
     在这条路径中，因为组成该路径的点都是从起点到该点所经过的点
     中，有路存在并且价格最小的点)；
            再使用dijkstra 算法计算从终点n 到其他每一个点的最大路径(每条路
     只走一次，不考虑环的最大路径)，使用入边去计算。这样就可以知
     道每个点到终点的最大路径，并知道最大路径沿途价格最大的那个
     点。
            最后，用每个点到终点的最大值减去从起点到该点的最小值，就
     是收益，将所有点的收益排个序，找到最大收益就是最终结果。其中
     需要判断每个点是否可以从起点走到以及从改点是否可以走到终点。
            以上思路是有问题的，不能用dijkstra 算法，而应该用Bellman-Ford算法。
     其实本题和最短路径一点关系都没有，之前的想法是在没彻底想清楚
     的情况下被网上的一些说法误导了。
            本题需要先求出从起点出发到每一个点时，从起点到该点途径的
     价格最低点的价格；然后再从该点出发，计算从该点出发到终点途径
     的价格最高点的价格。每一个点都有自己的最高价格和最低价格，然
     后做差，遍历每个点的差值找到最大值就是所求最终的结果。
            环路对本题的结果有重大影响。以输入样例2 找最小值为例，从1
     号点可以直接走到4 号点，此时4 号点记录的最小值是4；如果从1 号点
     走到4 号点的路径是1->4->5->4，那么此时4 号点应该记录的最小值就是1。
     环路4->5->4 对结果的影响就体现在这里。
            整个过程没有计算最短路径，但却可以借用最短路径算法的思想去
     更新每个点的最小值或最大值。Dijkstra 算法的思想无法用在这里，因为
     dijksrta 算法不会再对已经出堆的点做松弛操作，比如输入样例2，如果用
     dijkstra 算法的思想，当4 号点先于5 号点出堆，那么当5 号点想要将4 号点
     的最小值从4 更新到1 时，就无法更新了，因此4 号点的最小值就不是实
     际的最小值。
            以1 号点到4 号点为例，本题真正的想法是，把从1 号点到4 号点的所
     有路径都找出来，然后分析在每条路径中，4 号点能取到的最小价格是
     多少。SPFA 算法是Bellman-Ford 算法的一个队列实现，虽然通常用于求最短路
     径，但因为该算法求最短路径的过程相当于是将起点到各个点的所有路
     径都列出来然后从中寻找最短路径，恰好可以用在本题，所以本题在所
     有路径中寻找最小价格点的算法就是用SPFA。
            再次说明，本题和最短路径没有任何关系，只是因为SPFA 算法本身的
     特性恰好能够满足本题，所以才使用了这种算法，核心思想还是BFS，而
     最短路径算法本身和BFS 就有千丝万缕的联系(<<算法导论>>374页)，所以用
     SPFA 做出BFS 相关的题，并不奇怪。
            Bellman-Ford 原始算法(<<算法导论>>提供的那种写法) 可能并不适用于本题，
     因为该算法一共遍历|v|-1 次所有的边，这个遍历次数与生成最短路径树的
     边的条数对应，但本题并不是求最短路径，以样例2 从1 号点到4 号点找最
     小价格为例，使4 号点找到最小价格的路径恰恰不是从1 号点到4 号点的最
     短路径，所以|v|-1 这个遍历次数可能不够。
            SPFA 由于使用队列来完成松弛动作，在本题中，一旦某个点的最小值被
     改变，那该点一定会入队，然后再出队并改变可能受该点影响的其他点的
     最小值。只要队列空，那就说明一定全更新完了，在本题中可以保证一定
     能找到每个点最恰当的那个最小值点。
*   启发     
            1) BFS 与最短路径的联系；
            2) dijkstra 算法是用贪心的方式直接把最短路径求出来，限制就是无法
     处理带有负权边的图。Bellman-Ford 和SPFA 算法相当于是将起点到每一个点
     的所有路径都择出来，然后从中选择最短的那条，相比dijkstra，这两个
     算法慢就慢在要考虑所有的路径，但也正因为考虑了所有的路径并且
     是从所有路径中找最短路径，因此可以处理带有负权边的图。
            3) 单目的地最短路径问题(<<算法导论>>374页)，书上说可以将目的地的
     边反向然后用单源最短路径算法求解，但我觉得在理解上不用专门反向，
     只要在求解的时候按照入边求解即可。平时我们求最短路径都是按照出
     边计算的。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

#if 0
typedef long long s64;

#define INFINITY 0x7fffffffffffffff
#define INFINITESIMAL -1

typedef struct adjoining_point
{
    int id;
    struct adjoining_point *next;
}adjoining_point_s;

typedef struct point
{
    s64 price;      // 该点自己的价格
    s64 min_price;  // 起点到该点的最小价格路径中，价格最小的点的价格
    s64 max_price;  // 该点到终点的最大价格路径中，价格最大的点的价格
    int heap_loc;   // 记录在堆中的位置，如果为-1，表示不在堆中
    s64 path_price; // 每条路径的总价格，建图的时候使用
    adjoining_point_s *ap_in;  // 入边邻接点
    adjoining_point_s *ap_out; // 出边邻接点
}point_s;

int g_n;
point_s *g_adjoining_table;
int *g_heap;
adjoining_point_s *g_ap_mem;

int bheap_delete_peak()
{
    int i, child, tmp, peak, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_adjoining_table[peak].heap_loc = -1;
    g_adjoining_table[heap_size].heap_loc = 1;
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_adjoining_table[g_heap[child]].path_price <= g_adjoining_table[g_heap[child+1]].path_price) {
            child++;
        }
        if (g_adjoining_table[g_heap[i]].path_price >= g_adjoining_table[g_heap[child]].path_price) {
            break;
        }
        tmp = g_heap[i];
        g_heap[i] = g_heap[child];
        g_heap[child] = tmp;
        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[child]].heap_loc = child;
    }

    return peak;
}

// 大根堆上滤
void bheap_percolate_up(int heap_loc)
{
    int i, dad, tmp;

    for (i = heap_loc; (i>>1) >= 1; i = dad) {
        dad = i >> 1;

        if (g_adjoining_table[g_heap[i]].path_price <= g_adjoining_table[g_heap[dad]].path_price) {
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

void dijkstra_biggest()
{
    int tmp;
    s64 tmp_pr;

    adjoining_point_s *cur, *next;

    g_adjoining_table[g_n].max_price = g_adjoining_table[g_n].price;
    g_adjoining_table[g_n].path_price = g_adjoining_table[g_n].price;
    bheap_percolate_up(g_adjoining_table[g_n].heap_loc);

    while (g_heap[0] > 0) {
        tmp = bheap_delete_peak();
        cur = g_adjoining_table[tmp].ap_in;

        while (NULL != cur) {
            next = cur->next;

            if (-1 == g_adjoining_table[cur->id].heap_loc) {
                cur = next;
                continue;
            }

            tmp_pr = g_adjoining_table[tmp].path_price + g_adjoining_table[cur->id].price;
            if (g_adjoining_table[cur->id].path_price >= tmp_pr) {
                cur = next;
                continue;
            }
            g_adjoining_table[cur->id].path_price = tmp_pr;
            g_adjoining_table[cur->id].max_price = (g_adjoining_table[cur->id].price > g_adjoining_table[tmp].max_price) ? g_adjoining_table[cur->id].price: g_adjoining_table[tmp].max_price;
            bheap_percolate_up(g_adjoining_table[cur->id].heap_loc);
            cur = next;
        }
    }

    return;
}

int sheap_delete_peak()
{
    int i, child, heap_size, peak, tmp;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }
    peak = g_heap[1];
    g_adjoining_table[peak].heap_loc = -1; // 表示该点出堆
    g_adjoining_table[g_heap[heap_size]].heap_loc = 1;
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_adjoining_table[g_heap[child]].path_price >= g_adjoining_table[g_heap[child+1]].path_price) {
            child++;
        }
        if (g_adjoining_table[g_heap[i]].path_price <= g_adjoining_table[g_heap[child]].path_price) {
            break;
        }
        tmp = g_heap[i];
        g_heap[i] = g_heap[child];
        g_heap[child] = tmp;
        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[child]].heap_loc = child;
    }

    return peak;
}

// 小根堆上滤
void sheap_percolate_up(int heap_loc)
{
    int i, dad, tmp;

    for (i = heap_loc; (i>>1) >= 1; i = dad) {
        dad = i >> 1;

        if (g_adjoining_table[g_heap[i]].path_price >= g_adjoining_table[g_heap[dad]].path_price) {
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

void dijkstra_shortest()
{
    int tmp;
    s64 tmp_pr;
    adjoining_point_s *cur, *next;

    g_adjoining_table[1].min_price = g_adjoining_table[1].price;
    g_adjoining_table[1].path_price = g_adjoining_table[1].price;
    sheap_percolate_up(g_adjoining_table[1].heap_loc);

    while (g_heap[0] > 0) {
        tmp = sheap_delete_peak();

        cur = g_adjoining_table[tmp].ap_out;
        while (NULL != cur) {
            next = cur->next;

            // 如果邻接点已经出堆
            if (-1 == g_adjoining_table[cur->id].heap_loc) {
                cur = next;
                continue;
            }

            tmp_pr = g_adjoining_table[tmp].path_price + g_adjoining_table[cur->id].price;
            if (g_adjoining_table[cur->id].path_price <= tmp_pr) {
                cur = next;
                continue;
            }

            g_adjoining_table[cur->id].path_price = tmp_pr;
            g_adjoining_table[cur->id].min_price = (g_adjoining_table[cur->id].price < g_adjoining_table[tmp].min_price) ? g_adjoining_table[cur->id].price : g_adjoining_table[tmp].min_price;
            sheap_percolate_up(g_adjoining_table[cur->id].heap_loc);
            cur = next;
        }
    }

    return;
}

void process()
{
    int i;
    s64 tmp, max_profit;

    dijkstra_shortest();

    // 更新点中各自的路径价格，重新入堆
    for (i = 1; i <= g_n; i++) {
        g_heap[i] = i;
        g_adjoining_table[i].heap_loc = i;
        g_adjoining_table[i].path_price = INFINITESIMAL;
    }
    g_heap[0] = g_n;
    
    dijkstra_biggest();

    max_profit = g_adjoining_table[1].max_price - g_adjoining_table[1].min_price;
    for (i = 2; i <= g_n; i++) {
        tmp = g_adjoining_table[i].max_price - g_adjoining_table[i].min_price;
        max_profit = (max_profit < tmp) ? tmp : max_profit;
    }

    (max_profit <= 0) ? printf("0\n"): printf("%lld\n", max_profit);

    return;
}

void create_adjoining_table(int edge_cnt)
{
    int i, pu, pv, ap_idx;
    adjoining_point_s *next;

    for (i = 0, ap_idx = 0; i < edge_cnt; i++) {
        scanf("%d %d", &pu, &pv);
        getchar();

        // pu -> pv ，pu 的出边
        next = g_adjoining_table[pu].ap_out;
        g_adjoining_table[pu].ap_out = &g_ap_mem[ap_idx++];
        g_adjoining_table[pu].ap_out->id = pv;
        g_adjoining_table[pu].ap_out->next = next;

        // pu -> pv ，pv 的入边
        next = g_adjoining_table[pv].ap_in;
        g_adjoining_table[pv].ap_in = &g_ap_mem[ap_idx++];
        g_adjoining_table[pv].ap_in->id = pu;
        g_adjoining_table[pv].ap_in->next = next;
    }

    return;
}

void init()
{
    int i, edge_cnt;

    scanf("%d %d", &g_n, &edge_cnt);
    getchar();

    // from 1
    g_adjoining_table = new point_s[g_n+1];
    g_heap = new int[g_n+1];
    for (i = 1; i <= g_n; i++) {
        scanf("%lld", &g_adjoining_table[i].price);
        getchar();
        g_heap[i] = i;

        /* 这样初始化，方便判断如方向和出方向非连通的情况
              *   只考虑出边，哪些点是非连通的；
              *   只考虑入边，哪些点是非连通的。
              *   对于非连通的点，无论在哪种情况下的非连通，其最后
              *   的收益都是负的。
              */
        g_adjoining_table[i].min_price = 0x7fffffff;
        g_adjoining_table[i].max_price = INFINITESIMAL;
        
        g_adjoining_table[i].heap_loc = i;

        // 先算从1 到其他点的最短路径
        g_adjoining_table[i].path_price = INFINITY;
        g_adjoining_table[i].ap_in = NULL;
        g_adjoining_table[i].ap_out = NULL;
    }
    g_heap[0] = g_n;

    g_ap_mem = new adjoining_point_s[edge_cnt*2];
    create_adjoining_table(edge_cnt);

    return;
}

void end()
{
    delete[] g_adjoining_table;
    delete[] g_heap;
    delete[] g_ap_mem;

    return;
}

int main()
{
    init();

    process();

    end();

    return 0;
}
#endif

#define INFINITY 0x7fffffff
#define INFINITESIMAL -1
#define MIN_OUT 0
#define MAX_IN  1

typedef struct adjoining_point
{
    int id;
    struct adjoining_point *next;
}adjoining_point_s;

typedef struct point
{
    int price;      // 该点自己的价格
    int price_arr[2];  // 记录从起点到该点的最小值以及从该点到终点的最大值
    bool in_queue;  // 判断是否在队列中
    adjoining_point_s *ap_arr[2]; // 出边邻接点和入边邻接点
}point_s;

int g_n;
point_s *g_adjoining_table;
adjoining_point_s *g_ap_mem;

int g_queue_size;
int g_queue_head;
int g_queue_tail;
int *g_queue;

bool queue_isempty()
{
    return (0 == g_queue_size) ? true : false;
}

int dequeue()
{
    int idx;

    if (0 == g_queue_size) {
        return -1;
    }

    idx = g_queue_head % g_n;
    g_queue_head = idx + 1;
    g_queue_size--;
    g_adjoining_table[g_queue[idx]].in_queue = false;
    
    return g_queue[idx];
}

bool enqueue(int point_id)
{
    int idx;

    if (g_queue_size == g_n) {
        return false;
    } 

    idx = g_queue_tail % g_n;
    g_queue_tail = idx + 1;
    g_queue[idx] = point_id;
    g_queue_size++;
    g_adjoining_table[point_id].in_queue = true;
    
    return true;
}

// 从题意知不存在负权边，所以不用探测负权环
void spfa_process(int src_id, int dir)
{
    int tmp_id, tmp_pr;
    adjoining_point_s *cur, *next;

    g_adjoining_table[src_id].price_arr[dir] = g_adjoining_table[src_id].price;
    enqueue(src_id);

    while (!queue_isempty()) {
        tmp_id= dequeue();

        cur = g_adjoining_table[tmp_id].ap_arr[dir];
        while (NULL != cur) {
            next = cur->next;

            if (MIN_OUT == dir) {
                tmp_pr = (g_adjoining_table[tmp_id].price_arr[dir] <= g_adjoining_table[cur->id].price) ? g_adjoining_table[tmp_id].price_arr[dir]: g_adjoining_table[cur->id].price;
                if (g_adjoining_table[cur->id].price_arr[dir] <= tmp_pr) {
                    cur = next;
                    continue;
                }
            }
            else {
                tmp_pr = (g_adjoining_table[tmp_id].price_arr[dir] >= g_adjoining_table[cur->id].price) ? g_adjoining_table[tmp_id].price_arr[dir]: g_adjoining_table[cur->id].price;
                if (g_adjoining_table[cur->id].price_arr[dir] >= tmp_pr) {
                    cur = next;
                    continue;
                }
            }
            g_adjoining_table[cur->id].price_arr[dir] = tmp_pr;
            
            if (!g_adjoining_table[cur->id].in_queue) {
                enqueue(cur->id);
            }
            cur = next;
        }
    }

    return;
}

void process()
{
    int i, tmp, max_profit;

    spfa_process(1, MIN_OUT);
    spfa_process(g_n, MAX_IN);

    max_profit = g_adjoining_table[1].price_arr[MAX_IN] - g_adjoining_table[1].price_arr[MIN_OUT];
    for (i = 2; i <= g_n; i++) {
        // 如果不存在从1 到n 能先低价买入然后高价卖出的点，则tmp 为负值
        tmp = g_adjoining_table[i].price_arr[MAX_IN] - g_adjoining_table[i].price_arr[MIN_OUT];
        if (max_profit < tmp) {
            max_profit = tmp;
        }
    }

    (max_profit <= 0) ? printf("0\n") : printf("%d\n", max_profit);

    return;
}

void create_adjoining_table(int edge_cnt)
{
    int i, pu, pv, ap_idx;
    adjoining_point_s *next;

    for (i = 0, ap_idx = 0; i < edge_cnt; i++) {
        scanf("%d %d", &pu, &pv);
        getchar();

        // pu -> pv ，pu 的出边
        next = g_adjoining_table[pu].ap_arr[MIN_OUT];
        g_adjoining_table[pu].ap_arr[MIN_OUT] = &g_ap_mem[ap_idx++];
        g_adjoining_table[pu].ap_arr[MIN_OUT]->id = pv;
        g_adjoining_table[pu].ap_arr[MIN_OUT]->next = next;

        // pu -> pv ，pv 的入边
        next = g_adjoining_table[pv].ap_arr[MAX_IN];
        g_adjoining_table[pv].ap_arr[MAX_IN] = &g_ap_mem[ap_idx++];
        g_adjoining_table[pv].ap_arr[MAX_IN]->id = pu;
        g_adjoining_table[pv].ap_arr[MAX_IN]->next = next;
    }

    return;
}

void init()
{
    int i, edge_cnt;

    scanf("%d %d", &g_n, &edge_cnt);
    getchar();

    g_queue = new int[g_n+1];
    g_queue_size = 0;
    g_queue_head = 0;
    g_queue_tail = 0;

    // from 1
    g_adjoining_table = new point_s[g_n+1];
    for (i = 1; i <= g_n; i++) {
        scanf("%d", &g_adjoining_table[i].price);
        getchar();

        // 遇上非连通的情况，这样初始化可以保证非连通点的最大收益为负
        g_adjoining_table[i].price_arr[MIN_OUT] = INFINITY;
        g_adjoining_table[i].price_arr[MAX_IN] = INFINITESIMAL;

        g_adjoining_table[i].in_queue = false;
        
        // 先算从1 到其他点的最短路径
        g_adjoining_table[i].ap_arr[MIN_OUT] = NULL;
        g_adjoining_table[i].ap_arr[MAX_IN] = NULL;
    }

    g_ap_mem = new adjoining_point_s[edge_cnt*2];
    create_adjoining_table(edge_cnt);

    return;
}

void end()
{
    delete[] g_adjoining_table;
    delete[] g_queue;
    delete[] g_ap_mem;

    return;
}

int main()
{
    init();

    process();

    end();

    return 0;
}


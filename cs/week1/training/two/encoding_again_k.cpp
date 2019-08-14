/* 题目
*      重编码-K
*   背景
*      小粽学习了哈夫曼树之后，自己设计了贪心算法，用两个队列就过掉了《重编码》这道题。
*      小粽想：那堆的算法有什么用呢？为了解决小粽的疑惑，邓老师委托小莉命制了这道题目……
*   描述
*      有一篇文章，文章包含n种单词，单词的编号从1至n，第i种单词的出现次数为w[i]，现在，
*我们要用一个k进制串（即只包含0,1,...,k−1的串）s[i]来替换第i种单词，使其满足如下要求,
*          对于任意的1≤i<j≤n，都有s[i]不是s[j]的前缀（这个要求是为了避免二义性）。
*      你的任务是对每个单词选择合适的s[j]，使得替换后的文章总长度（定义为所有单词出现次数与替换它的k
*进制串的长度乘积的总和）最小。求这个最小长度。
*      字符串S[1]（不妨假设长度为n）被称为字符串S[2]的前缀，当且仅当：S[2]的长度不小于 
*n，且S[1]与S[2]前n个字符组组成的字符串完全相同。
*   输入格式
*      第一行两个整数n和k。第2行到第n+1行，第i+1行包含一个正整数w[i]，表示第i种单词的出现次数。
*   输出格式
*      表示整篇文章重编码后的最短长度
*   输入样例1
*      5 3
*      1
*      3
*      5
*      10
*      3
*   输出样例1
*      29
*   限制
*      对于 100% 的数据，满足1≤n≤(3*(10^5)), 2≤k≤10, 1≤w[i]≤(10^9)
*      对于 40% 的数据，满足n≤3000
*      对于 35% 的数据，满足k=2
*   提示
*      贪心思路与重编码题目相同。需要思考的是：如何让最后构建的哈夫曼树为满k叉树呢？
*   解题思路
*      为了让k叉树成为满k叉树，必须补出现频率为0的叶子节点，使整棵树成为满k叉树（即除了叶子节点，其他
每个节点都有k个子节点）。
*      补0个数公式： r = [k - n % (k - 1)] % (k - 1)
*   我的思路
*      按题目要求，不用输出具体每个字符的编码，只要计算出每个字符在k叉树种的深度并乘以其出现频率再求和即可
*      按题目限制，极限情况下，k叉树会有300000~600000个节点，堆需要300000个点
*      原始的哈夫曼树是二叉树，所以最后的编码结果都是二进制码。现在要求k进制码，就是求k叉树。
*      必须在整个k叉树的最下面那层叶子节点那层补出现频率为0的叶子节点，而不能在其他层补0。例如，有6个出现
频率分别为123458的点，组成一棵三叉树，不补0的情况下，按哈夫曼编码的贪心原则，整个树应为：
            23
             |         \
a            8         15
                    /   |   \  
b                  4    5    6                       
                           / | \
c                         1  2  3
*      在a层补0，会浪费一个字符的编码，即本来有一个字符可以只用一个编码表示，但因为在这个位置补0，所以只能
将这个字符放到其他层，所以在这层补0是不合理的。最合理的方式就是在c层补0，这样可以充分利用每一层为需要编码的
字符进行编码。
*      每次合并都减少(k-1)个点，如果是满k叉树，到最后应该只剩下一个点
*      更好理解的补0公式： r = [k - 1 - n%(k-1) + 1]%(k-1)
*      公式解释：
*          (k-1)： 每次合并，都是取出最小的k个，然后再生成1个，所以每次合并，都减少(k-1)个
*        n%(k-1)： 当前总节点个数对(k-1)做除法，商表示做了多少次合并操作，余数表示剩下的节点数量
*  k-1 - n%(k-1)： 需要补多少个0才能达到(k-1)个节点
*k-1 - n%(k-1)+1： 满k叉树要求经过一定数量的合并后，最后要恰好剩下一个节点，这里加一就是补剩下的这个节点
*    [...]%(k-1)： 最后又对(k-1)取余，是为了处理当n%(k-1)恰好为0时，只补充最少的0的个数
*   我的补0方案
*       [n%(k-1) + r]%(k-1) = 1
*       解释：
*          因为“每次合并都减少(k-1)个点，如果是满k叉树，到最后应该只剩下一个点”，即满k叉树的性质是n%(k-1) = 1
*          按照这个公式，r从0开始逐次加1迭代，直到使等号左面的结果等于1，就说明这个r就是最小补0个数
*          说白了就是如果n%(k-1)不等于1，那么n%(k-1)再加多少再对(k-1)取余就是1
*   我的节点总数计算公式
*       满k叉树所拥有的总节点个数为 M = (n*k-1) / (k-1)，其中，n是已经补完0，满足n%(k-1)=1的值
*       对于原始哈夫曼树，k=2，那么由该公式推导出的满2叉树公式就是 M=2*n-1
*       推导过程：
*           满k叉树必须满足每次合并k个点并生成1个点，最后剩下1个点的性质。
*           满k叉树所有点=n+新生成的点
*           n-k+1-k+1-k+1-.....-k+1 = 1
*     n-(k-1)-(k-1)-(k-1)-...-(k-1) = 1
*                          n-t(k-1) = 1
*                                 t = (n-1)/(k-1)，t就是新生成点的个数
*           M = n+t 
*           M = (n*k-1)/(k-1)
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

// 1≤n≤(3*(10^5)), 2≤k≤10, 1≤w[i]≤(10^9)
typedef struct tree_node
{
    u32 leaf; // 实际的叶子节点，从1开始，非叶子节点或用于补0的叶子节点这里的值为0
    u64 freq; // 1≤w[i]≤(10^9)，后面需要对频率做累加，为防止翻转，所以这里使用u64
    //u32 high; // 每个点距离自己所在子树的叶子节点的高度，叶子节点的高度为0。叉多了以后不好弄，暂时不用了
    u32 child[10]; // 记录子节点的内存索引，最多60万个节点，故只能用u32。child[0~9]为具体的叉
}tree_node_s;

static u32* g_heap;
static u32 g_mem_index;
static tree_node_s* g_memory;

// 1≤n≤(3*(10^5)), 2≤k≤10, 1≤w[i]≤(10^9)
static int g_N;
static int g_K;

// 这里必须使用u64，不然最终的结果会翻转
static u64 g_len = 0;

static void swap_heap(int heap_dad, int heap_child)
{
    u32 tmp_mem_index;

    tmp_mem_index = g_heap[heap_child];
    g_heap[heap_child] = g_heap[heap_dad];
    g_heap[heap_dad] = tmp_mem_index;

    return;
}

// 有风险，如果k叉树层数太多，使用递归可能栈溢出（函数调用栈）
// 如果数据量大但是k也大，情况可能还好些
static void calculate(u32 mem_node_index, u32 code_len)
{
    int i, k;

    // 递归基（因为是满k叉树，且是前缀树，所以叶子节点只能是补0节点和实际的叶子节点）
    if (0 == g_memory[mem_node_index].freq) { // 用于补0的节点
        return;
    }
    if (0 != g_memory[mem_node_index].leaf) { // 实际的叶子节点
        g_len += g_memory[mem_node_index].freq * code_len;
        return;
    }

    // 因为是满k叉树，所以除叶子节点以外的每个节点都有k个子节点
    k = g_K;
    for (i = 0; i < k; i++) {
        calculate(g_memory[mem_node_index].child[i], code_len + 1);
    }

    return;
}

// tips: 小根堆
static void insert_heap(u32 mem_node_index)
{
    int i, dad;
    u32 heap_size;

    //TODO 最好检查一下是否越界
    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_node_index;
    g_heap[0] = heap_size;

    // 上滤
    for (i = heap_size; (i >> 1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_memory[g_heap[i]].freq >= g_memory[g_heap[dad]].freq) {
            break;
        }
        swap_heap(dad, i);
    }

    return;
}

// tips: 小根堆
// 返回挂在堆中的编码树节点索引（g_memory的索引）
static u32 delete_heap_peak()
{
    int i, child, heap_size;
    u32 mem_node_index;

    heap_size = g_heap[0];
    if (heap_size < 1) {
        printf("There is not any item in heap.\n");
        return 0xffffffff;
    }

    mem_node_index = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    // 下滤
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size && 
            g_memory[g_heap[child]].freq >= g_memory[g_heap[child+1]].freq) {
            child++;
        }
        if (g_memory[g_heap[i]].freq <= g_memory[g_heap[child]].freq) {
            break;
        }
        swap_heap(i, child);
    }

    return mem_node_index;
}

// 返回k叉树根节点的g_memory索引
static u32 build_k_tree()
{
    int i;
    int k;
    u32 tmp_mem_idx, new_node_idx = 0xffffffff; 

    k = g_K;
    if (g_heap[0] < k) {
        return new_node_idx;
    }

    // 因为已经补0了，所以在最后一次合并之前，一定能够从堆中取出k个点
    while (g_heap[0] >= k) {
        // 分配新节点
        new_node_idx = g_mem_index++;

        // 合并
        for (i = 0; i < k; i++) {
            tmp_mem_idx = delete_heap_peak();
            g_memory[new_node_idx].freq += g_memory[tmp_mem_idx].freq;
            g_memory[new_node_idx].child[i] = tmp_mem_idx;
        }

        // 合并完生成的节点即k叉树根节点
        if (0 == g_heap[0]) {
            break;
        }
        insert_heap(new_node_idx);
    }

    return new_node_idx;
}

// tips: 小根堆
static void create_heap()
{
    int i, j, child;
    u32 heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_memory[g_heap[child]].freq >= g_memory[g_heap[child + 1]].freq) {
                child++;
            }
            if (g_memory[g_heap[j]].freq <= g_memory[g_heap[child]].freq) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

static void init()
{
    int i, r, cnt;

    scanf("%d %d", &g_N, &g_K);
    getchar();

    // tips: 补0是指补出现频率为0的节点
    // 计算补0个数 r = [k - n % (k - 1)] % (k - 1)
    r = (g_K - g_N % (g_K - 1)) % (g_K - 1);

    // M = (n*k-1)/(k-1)
    cnt = ((g_N + r) * g_K - 1) / (g_K - 1);

    //TODO 内存分配失败检查
    g_mem_index = 0;
    g_memory = new tree_node_s[cnt];
    for (i = 0; i < cnt; i++) {
        g_memory[i].leaf = 0;
        g_memory[i].freq = 0;
    }

    g_heap = new u32[g_N + r + 1];
    g_heap[0] = g_N + r;
    
    // 将补0节点塞入堆中
    for (i = 1; i <= r; i++) {
        g_heap[i] = g_mem_index++;
    }

    // 分配节点并将实际的叶子节点塞入堆中
    for (i = 1; i <= g_N; i++) {
        scanf("%llu", &g_memory[g_mem_index].freq);
        getchar();
        g_memory[g_mem_index].leaf = i;

        // 堆中前r+1个点（第0个记录堆中节点个数，1~r个元素是补0节点）
        g_heap[r + i] = g_mem_index++;
    }

    return;
}

static void end()
{
    delete[] g_heap;
    delete[] g_memory;
    return;
}

void k_coding()
{
    int root_idx;

    init();

    create_heap();
    root_idx = build_k_tree();
    calculate(root_idx, 0);
    printf("%llu\n", g_len);

    end();
    return;
}
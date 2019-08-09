/* 题目
*     数字盒子
*  描述
*     你有一个盒子，你可以往里面放数，也可以从里面取出数。
*     初始时，盒子是空的，你会依次做 Q 个操作，操作分为两类：
*         插入操作：询问盒子中是否存在数 x，如果不存在则把数 x 丢到盒子里。
*         删除操作：询问盒子中是否存在数 x，如果存在则取出 x。
*     对于每个操作，你需要输出是否成功插入或删除。
*  输入
*     第一行一个正整数 Q，表示操作个数。
*     接下来 Q 行依次描述每个操作。每行 2 个用空格隔开的非负整数 op,x 
*         op 表示操作类型，op=1 则表示这是一个插入操作，op=2 则表示这是一个删除操作
*          x 的意义与操作类型有关，具体见题目描述。
*  输出
*     按顺序对所有操作输出，对于每个操作输出一行，
*     如果成功则输出“Succeeded”（不含引号），如果失败则输出“Failed”（不含引号）。
*  样例输入
*     6
*     1 100
*     1 100
*     2 100
*     1 200
*     2 100
*     2 200
*  样例输出
*     Succeeded
*     Failed
*     Succeeded
*     Succeeded
*     Failed
*     Succeeded
*  数据范围
*     对于 60% 的数据，保证 x<10^5。
*     对于 100% 的数据，保证 x<10^18，Q≤5*10^5。
*     对于所有数据，保证 op∈{1,2}。
*  时间限制：10 sec
*  空间限制：256 MB
*  提示
*     [对于 x 较小的情况，我们只需要用数组记录每个数是否在盒子里即可。]
*     [对于 x 较大的情况，我们可不可以用什么方法把它们“变小”呢？可以想想哈希表哦！]
*  我的思路
*     虽然用哈希可能会出现冲突的情况，但是会比直接用数组节省大量空间，极端情况下会和用数组使用的空间相同
*     大多情况下不会出现极端情况，那么用哈希是绝对可以接受的
*     关键在于如何设计哈希函数
*     Q的范围仅仅是500000，如果每个操作都对应不同的数据，那么最多也就500000个数，所以总空间哈希表的空间
开到500000就行，即500000个元素的指针数组
*     常用hash质数表 https://blog.csdn.net/shiyongyang/article/details/78079109
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct operation
{
    u32 opt;
    u64 val;
}operation_s;

typedef struct chain_node
{
    u64 val;
    struct chain_node* next;
}chain_node_s;

// 选择一个五十万左右的质数作为哈希质数
static u64 g_hash = 517619ULL;

static u32 g_opt_cnt;
static operation_s* g_opt_mem;
static chain_node_s** g_hash_table;

static void insert_opt(int opt_idx, u64 val) 
{
    int idx;
    bool output;
    chain_node_s *cur, *next;

    output = true;
    if (opt_idx == g_opt_cnt - 1) {
        output = false;
    }

    idx = val % g_hash;

    if (NULL == g_hash_table[idx]) {
        g_hash_table[idx] = new chain_node_s;
        g_hash_table[idx]->val = val;
        g_hash_table[idx]->next = NULL;

        printf("Succeeded");
        if (output) {
            printf("\n");
        }
        return;
    }

    cur = g_hash_table[idx];
    while (NULL != cur) {
        next = cur->next;

        if (val != cur->val) {
            cur = next;
            continue;
        }
        printf("Failed");
        if (output) {
            printf("\n");
        }

        return;
    }

    cur = new chain_node_s;
    cur->val = val;
    cur->next = g_hash_table[idx];
    g_hash_table[idx] = cur;
    printf("Succeeded");
    if (output) {
        printf("\n");
    }

    return;
}

static void delete_opt(int opt_idx, u64 val)
{
    int idx;
    bool output;
    chain_node_s* cur, * next, * prev;

    output = true;
    if (opt_idx == g_opt_cnt - 1) {
        output = false;
    }

    idx = val % g_hash;

    if (NULL == g_hash_table[idx]) {
        printf("Failed");
        if (output) {
            printf("\n");
        }

        return;
    }

    prev = g_hash_table[idx];
    cur = g_hash_table[idx];
    while (NULL != cur) {
        next = cur->next;

        if (val != cur->val) {
            prev = cur;
            cur = next;
            continue;
        }
        
        if (cur == g_hash_table[idx]) {
            g_hash_table[idx] = next;
        }
        else {
            prev->next = next;
        }
        cur->next = NULL;
        delete cur;
        printf("Succeeded");
        if (output) {
            printf("\n");
        }

        return;
    }

    printf("Failed");
    if (output) {
        printf("\n");
    }

    return;
}

static void process()
{
    int i;

    for (i = 0; i < g_opt_cnt; i++) {
        if (1 == g_opt_mem[i].opt) {
            insert_opt(i, g_opt_mem[i].val);
            continue;
        }
        delete_opt(i, g_opt_mem[i].val);
    }

    return;
}

static void init()
{
    int i;

    scanf("%u", &g_opt_cnt);
    getchar();

    g_opt_mem = new operation_s[g_opt_cnt];
    for (i = 0; i < g_opt_cnt; i++) {
        scanf("%u %llu", &g_opt_mem[i].opt, &g_opt_mem[i].val);
        getchar();
    }

    g_hash_table = new chain_node_s * [g_hash];
    for (i = 0; i < g_hash; i++) {
        g_hash_table[i] = NULL;
    }

    return;
}

static void free_chain_in_hash_table()
{
    int i;
    chain_node_s *next, *cur;

    for (i = 0; i < g_hash; i++) {
        cur = g_hash_table[i];
        while (NULL != cur) {
            next = cur->next;
            delete cur;
            cur = next;
        }
        g_hash_table[i] = NULL;
    }

    return;
}

static void end()
{
    delete[] g_opt_mem;

    free_chain_in_hash_table();

    delete[] g_hash_table;

    return;
}

void number_box()
{
    init();

    process();

    end();

    return;
}
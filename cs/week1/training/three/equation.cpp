/* 题目
*     等式
*  描述
*     有n个变量和m个“相等”或“不相等”的约束条件，请你判定是否存在一种赋值方案满足所有m个约束条件。
*  输入
*     第一行一个整数T，表示数据组数。
*     接下来会有T组数据，对于每组数据：
*         第一行是两个整数n,m，表示变量个数和约束条件的个数。
*         接下来m行，每行三个整数a,b,e，表示第a个变量和第b个变量的关系：
*             若e=0则表示 第a个变量 不等于 第b个变量 ；
*             若e=1则表示 第a个变量 等于   第b个变量
*  输出
*     输出T行，第i行表示第i组数据的答案。若第i组数据存在一种方案则输出"Yes"；否则输出"No"（不包括引号）。
*  输入样例1
*     2
*     5 5
*     1 2 1
*     2 3 1
*     3 4 1
*     1 4 1
*     2 5 0
*     3 3
*     1 2 1
*     2 3 1
*     1 3 0
*  输出样例1
*     Yes
*     No
*  样例1解释
*     一共有2组数据。
*     对于第一组数据，有5个约束：
*     变量1=变量2
*     变量2=变量3
*     变量3=变量4
*     变量1=变量4
*     变量2≠变量5
*     显然我们可以令：
*         变量1=变量2=变量3=变量4=任意一个数值
*         变量5=任意一个和变量2不同的数值
*         故第一组数据输出"Yes"。 
*     对于第二组数据，有3个约束：
*     变量1=变量2
*     变量2=变量3
*     变量1≠变量3
*         由前两个约束可推出变量1=变量3，但第三个约束表明变量1≠变量3，矛盾。
*         故第二组数据输出"No"。
*  限制
*     对于10%的数据，n,m ≤ 5，T ≤ 5；
*     对于50%的数据，n,m ≤ 1000，T ≤ 10；
*     对于100%的数据，1 ≤ n ≤ 300000, m ≤ 500000，1 ≤ a,b ≤ n，T ≤ 100。
*     保证所有数据的n总和与m总和不超过500000。
*     时间：2 sec
*     空间：256 MB
*   提示
*   [用并查集来维护相等的集合。]
*   [改编自 NOI 2015 day1 T1 程序自动分析]
*   我的思路
*       将相等的操作和不等的操作分开
*       先处理相等的操作：将相等的数放到同一个集合中
*       再处理不等的操作：检查不等的数是否在同一个集合中，如果发现在同一个集合，直接输出“No”；
                                                        所有不等操作都执行完都没问题，输出“Yes”
*       集合使用并查集，查询使用路径压缩
*       关键是如何读入数据，使内存占用最小，时间越短
*           每读入一组数据，随即处理一组数据
*           创建一个全局链表，记录当前数据组的“不等于”操作，每次读入数据的时候，表头统计当前数据组的“不等于”操作数量
*               全局链表中的节点不够时，创建新节点；
*               遍历当前组的“不等于”操作时，由链表头记录的当前组“不等于”操作个数确定查找个数
*               当处理新组数据时，将链表头中记录的“不等于”操作数更新为0，链表指针不用动
*           函数栈溢出风险
*               有可能在递归执行find操作时导致函数栈溢出，所以应考虑使用非递归的路径压缩
*               非递归的路径压缩
*                   提供一个由链表构成的全局栈，表头记录栈底与栈顶的节点指针，只有栈不够用的时候，才在表头下面添加新节点
*                   该链表构成的栈可以反复使用，每次只要更新表头中的栈顶指针即可
*                   程序结束时，删除该链表
*                   find时，如果当前节点的父节点就是该点所在集合的根节点，则直接返回集合名称即可
*                   ...                        不是...                ，则迭代查询其父节点，并将沿途各个节点压栈
*                     找到根节点后，弹栈，更新沿途每个节点的父节点，以实现路径压缩
*               递归的路径压缩
*                   为防止函数栈溢出，每组数据每执行一定数量的操作后，都对该组数据全部节点做一次路径压缩
*       数据结构设计
*           记录“不等于”操作的链表头
*           记录“不等于”操作的链表节点
*           可以记录300000个数的内存，初始值为索引值（表示节点自己），用于记录父节点，以实现并查集
*           一个由链表构成的全局栈
*           一块用于记录最后结果的内存
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

// 不算0
#define MAX_N 300000
#define EQUAL   1
#define UNEQUAL 0

enum output_result_idx
{
    YES = 0,
    NO
};

static const char* g_output_type[2] = { "Yes", "No" };
static int  g_output_cnt;
static char* g_output_result; // 指向记录最终结果的内存

typedef struct unequal_chain_node
{
    int num1;
    int num2;
    struct unequal_chain_node* next;
}unequal_chain_node_s;

typedef struct unequal_chain_head
{
    int opt_cnt;
    unequal_chain_node_s* tail;   // 指向尾节点，新节点挂在尾节点上
    unequal_chain_node_s* next;   // 将所有节点链起来
    unequal_chain_node_s* ranger; // 指向当前可以存储具体操作的节点
}unequal_chain_head_s;

// 指向全局内存，共MAX_N个节点
static int* g_node;

// 全局“不等于”操作链表头
static unequal_chain_head_s* g_unequal_chain_head;

static void set_union(int set_root_a, int set_root_b)
{
    g_node[set_root_b] = set_root_a;

    return;
}

static int set_find_by_recursion(int val)
{
    // 递归基
    if (val == g_node[val]) {
        return val;
    }
    g_node[val] = set_find_by_recursion(g_node[val]);
    return g_node[val];
}

static void opt_enchain(int tmp_a, int tmp_b, int opt)
{
    // 进入判断，说明当前链表上的节点不够了
    if (nullptr == g_unequal_chain_head->ranger) {
        g_unequal_chain_head->tail->next = new unequal_chain_node_s;
        g_unequal_chain_head->tail = g_unequal_chain_head->tail->next;
        g_unequal_chain_head->tail->next = nullptr;

        g_unequal_chain_head->ranger = g_unequal_chain_head->tail;
    }

    g_unequal_chain_head->opt_cnt++;
    g_unequal_chain_head->ranger->num1 = tmp_a;
    g_unequal_chain_head->ranger->num2 = tmp_b;
    g_unequal_chain_head->ranger = g_unequal_chain_head->ranger->next;
    
    return;
}

static void safe_recursion(int data_cnt)
{
    int j;

    for (j = 1; j <= data_cnt; j++) {
        set_find_by_recursion(j);
    }

    return;
}

static int process_group_data(int data_cnt, int opt_cnt)
{
    int i;
    int root_a, root_b;
    int tmp_a, tmp_b, tmp_opt;
    unequal_chain_node_s* ranger;

    for (i = 0; i < opt_cnt; i++) {
        scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_opt);
        getchar();

        root_a = set_find_by_recursion(tmp_a);
        root_b = set_find_by_recursion(tmp_b);

        if (root_a == root_b) {
            if (EQUAL == tmp_opt) {
                continue;
            }

            // 此时已经可以判定结果为NO，但还需要读完剩余的输入才能返回
            while (++i < opt_cnt) {
                scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_opt);
                getchar();
            }
            return NO;
        }

        // 处理 root_a != root_b
        if (EQUAL == tmp_opt) {
            set_union(root_a, root_b);

            // 防止数据量太大时，函数栈溢出，所以每执行1000次操作，都做一遍路径压缩
            if (i > 0 && 0 == i % 1000) {
                safe_recursion(data_cnt);
            }

            continue;
        }

        // 将操作挂链表，处理完“等于”操作后统一处理“不等于”操作
        opt_enchain(tmp_a, tmp_b, tmp_opt);
    }

    // 处理链表中的内容
    ranger = g_unequal_chain_head->next;
    for (i = 0; i < g_unequal_chain_head->opt_cnt && nullptr != ranger; i++) {
        root_a = set_find_by_recursion(ranger->num1);
        root_b = set_find_by_recursion(ranger->num2);
        if (root_a == root_b) {
            return NO;
        }
        ranger = ranger->next;
    }
    
    return YES;
}

static void process()
{
    int i, j;
    int data_cnt, opt_cnt;

    for (i = 0; i < g_output_cnt; i++) {
        scanf("%d %d", &data_cnt, &opt_cnt);
        getchar();

        // 将本组数据处理结果存入全局结果数组
        g_output_result[i] = (char)process_group_data(data_cnt, opt_cnt);
        
        // 清理g_node，准备处理下一组数据
        for (j = 1; j <= data_cnt; j++) {
            g_node[j] = j;
        }

        // 清理链表
        g_unequal_chain_head->opt_cnt = 0;
        g_unequal_chain_head->ranger = g_unequal_chain_head->next;
    }

    return;
}

static void free_unequal_chain()
{
    unequal_chain_node_s* cur, *next;

    if (nullptr == g_unequal_chain_head) {
        return;
    }

    if (nullptr == g_unequal_chain_head->next) {
        delete g_unequal_chain_head;
        g_unequal_chain_head = nullptr;
        return;
    }
    
    // 从头开始释放
    next = g_unequal_chain_head->next;
    delete g_unequal_chain_head;
    g_unequal_chain_head = nullptr;

    while (nullptr != next) {
        cur = next;
        next = next->next;
        delete cur;
    }

    return;
}

static void init()
{
    int i;

    // 第0个元素没用，数据范围是[1, 300000]
    g_node = new int[MAX_N + 1];
    for (i = 1; i <= MAX_N; i++) {
        g_node[i] = i;
    }

    g_unequal_chain_head = new unequal_chain_head_s;
    g_unequal_chain_head->opt_cnt = 0;
    g_unequal_chain_head->next = new unequal_chain_node_s;
    g_unequal_chain_head->next->next = nullptr;
    g_unequal_chain_head->tail = g_unequal_chain_head->next;
    g_unequal_chain_head->ranger = g_unequal_chain_head->next;

    scanf("%d", &g_output_cnt);
    getchar();
    g_output_result = new char[g_output_cnt];

    return;
}

static void end()
{
    delete[] g_node;

    // 释放“不等于”操作链表
    free_unequal_chain();

    delete[] g_output_result;

    return;
}

static void output()
{
    char i;

    for (i = 0; i < g_output_cnt; i++) {
        printf("%s\n", g_output_type[g_output_result[i]]);
    }

    return;
}

void equation()
{
    init();

    process();
    output();

    end();

    return;
}
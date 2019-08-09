/* 题目
*     周测1
*  描述
*     给定一个1到n的排列，依次从队尾插入到队列中，在任何时刻你都可以弹出队首或队尾。最终你需要把队列清空。
*     问：如何使得出队序列的字典序最大？请输出这个序列。
*  输入
*     输入的第一行包含一个正整数 n 。
*     接下来1行包含 n 个整数，一个1到 n 的排列。
*  输出
*     输出1行 n 个整数，即所求序列。
*  样例1输入
*     5
*     1 4 3 5 2
*  样例1输出
*     5 3 4 2 1
*  样例1解释
*     依次加入1、4、3、5、2到队列里，我们有这些个出队序列：
*         4 3 2 5 1
*         4 3 5 2 1
*         等等等，但字典序最大的是
*         5 3 4 2 1
*  样例2
*     请查看下发文件内的sample2_input.txt和sample2_output.txt。
*  限制
*     其中30%的数据， n = 200；
*     另外30%的数据， n = 2000；
*     另外20%的数据， n = 2 × 10^5；
*     剩下20%的数据， n = 2 × 10^6 。
*     时间：2 sec
*     空间：256 MB
*  我的思路
*     参考 https://www.cnblogs.com/GXZlegend/p/8300939.html
*     求最大字典序，考察的应该就是贪心。有n个数，即对应有n个位置，本题所求的最大字典序就是在满足题目要求
的情况下，让每个位置的数最大。
*     第0个位置肯定得是整个数列中最大的那个数才行
*     能弹出数的位置包括
*        队列头
*        队列尾
*        剩余没入队的数列中，最前面那个数可以被弹出（按题意，相当于刚入队马上又出队）
*     一个数只要入了队，要是再出去，就要算输出这个数了，而且只能从队列头或队列尾出去，所以一定要保证在入队前
在剩余数列中找到最大的数。例如，数列34125，当把5输出了之后，队列中有3412，要想输出4，只能先把队列头3弹出，而
弹出3的时候，3也就被输出了，所以这个例子的最大堆序是53421
*     剩余的数列要组成一个堆，队列头、队列尾、堆顶的数三个做比较，如果堆顶的数最大，且堆顶不是下一个可以入队
的数，那就把剩余数列中的数挨个入队，直到到了堆顶那个数，直接输出这个数，恢复堆序，继续这个过程。
*     如果队列头或队列尾最大，则直接输出即可，然后队列头、队列尾、堆顶继续比较
*     输出堆顶后，这个堆顶左面的数据已经全部入队，这个堆顶右面的数据要继续构成一个堆，选出新的堆顶，而旧堆顶
所在位置要被打标，记为已输出位置，不再参与比较（因为没有实际的队列，只是在原始序列上使用队列头尾两个指针而已）
*     队列头向右走，队列尾向左走，遇到被标记为已输出的点要跳过去
*     上面的想法总的没错，但是每次都构建一次堆会非常耗时，参看下面的process_new()处理过程，只需要建一次堆，
在使用插入法建堆过程中，每插入一次数据，都将这次的堆顶记录下来，由于是从数列尾部开始往前通过插入法构建堆的，
因此当从前往后开始入队出队处理数据时，能够知道从每个未入队的数据开始往后的最大值是谁。这种查表法解决了多次
重复计算最大值的问题。
*     体会
*        这道题不像参考链接中那个人说的那样水，反而很有启发性。
*     启发
*        插入式建堆的方法也是有用的，可以知道每次数据处理的即时最值
*        从前往后建堆，可以知道从当前数开始，往前所有的数中最大的数
*        从后往前建堆，可以知道从当前数开始，往后所有的数中最大的数
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

// 对应位置的数已经被输出的标记
#define MIN     -1

// 输入数据总个数
static int  g_cnt;

// 存储所有输入数据
static int* g_mem;

// 第0个元素记录堆中节点总数
static int* g_heap;

// 表，记录数列中，处理到每个数时，从该数往后的最大值的内存索引
static int* g_table;

// 队列
static int* g_queue;
static int g_queue_head;
static int g_queue_tail;

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

// 大根堆，入参为g_mem中的索引
static void create_heap(int start_idx)
{
    int i, j, child, heap_size;

    // 将需要使用堆的数据拷贝过来
    for (i = start_idx; i <= g_cnt; i++) {
        // g_heap从1开始
        g_heap[i - start_idx + 1] = i;
    }
    g_heap[0] = g_cnt - start_idx + 1;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_mem[g_heap[child]] <= g_mem[g_heap[child + 1]]) {
                child++;
            }
            if (g_mem[g_heap[j]] >= g_mem[g_heap[child]]) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

// 有题意限制可知，n最小等于200，所以不用考虑n小于3的边界情况
// 这种方式建堆，遇到如54321这种倒序数列，如果列很长，会非常耗时
static void process()
{
    int i;
    int output_cnt = 0;
    bool tag_update_heap;
    int peak_idx, start_idx, queue_idx;

    start_idx = 1;
    tag_update_heap = true;
    while (output_cnt < g_cnt) {
        queue_idx = g_queue_tail;

        // TODO这个地方有问题，队列的索引有问题
        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail]) {
            queue_idx = g_queue_head;
        }

        if (start_idx <= g_cnt) {
            if (tag_update_heap) {
                create_heap(start_idx);
            }
            peak_idx = g_heap[1];
            if (g_queue[queue_idx] < g_mem[peak_idx]) {
                // peak_idx左边的数据全部入队
                for (i = start_idx; i < peak_idx; i++) {
                    g_queue[++g_queue_tail] = g_mem[i];
                }

                printf("%d", g_mem[peak_idx]);
                output_cnt++;
                if (output_cnt < g_cnt) { printf(" "); }

                start_idx = peak_idx + 1;
                tag_update_heap = true;

                continue;
            }
            tag_update_heap = false;
        }

        // 弹出数据后，让g_queue[x] = MIN，就可以在g_queue_head == g_queue_tail时，后面的流
        // 程不会导致 g_queue_head < g_queue_tail
        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail]) {
            printf("%d", g_queue[g_queue_head + 1]);
            output_cnt++;
            g_queue[g_queue_head + 1] = MIN;
            g_queue_head++;
        }
        else {
            printf("%d", g_queue[g_queue_tail]);
            output_cnt++;
            g_queue[g_queue_tail] = MIN;
            g_queue_tail--;
        }
        if (g_queue_head == g_queue_tail) {
            g_queue_head = 0;
            g_queue_tail = 0;
        }
        if (output_cnt < g_cnt) {
            printf(" ");
        }
    }

    return;
}

// 大根堆
static void insert_heap(int mem_idx)
{
    int i, dad, heap_size;

    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_idx;
    g_heap[0] = heap_size;

    // 上滤
    for (i = heap_size; i > 1; i = dad) {
        dad = i >> 1;

        if (g_mem[g_heap[i]] <= g_mem[g_heap[dad]]) {
            break;
        }
        swap_heap(dad, i);
    }

    return;
}

/* 从整个数列的末尾开始，采用插入的方式建堆，并记录每个数对应的堆顶，这样当处理到第一个数时，
*  从第一个数往后的每一个数对应的各自后面的最大值就都有了。当查找最大值的时候，可以直接查表，
*  不用再做任何的排序相关的操作。为什么要从末尾开始采用插入的方式建堆？因为真正处理数据时是
*  从左往右依次处理的，每处理一个数，都要知道这个数往右的最大值是多少，如果当初从前往后插入，
*  那就只能知道这个数之前到这个数的最大值，所以必须从后往前插入，这样才能知道从这个数开始往后
*  的最大值是什么。
*/
static void record_max_value()
{
    int i;

    g_heap[0] = 0;
    for (i = g_cnt; i >= 1; i--) {
        insert_heap(i);
        g_table[i] = g_heap[1];
    }

    return;
}

static void process_new()
{
    int i;
    int out_cnt;
    int start_idx, queue_idx;

    record_max_value();

    out_cnt = 0;
    start_idx = 1;
    while (out_cnt < g_cnt) {
        queue_idx = 0;
        if (g_queue_head + 1 < g_queue_tail) { // 队列不为空
            queue_idx = g_queue_tail - 1;
            if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail - 1]) {
                queue_idx = g_queue_head + 1;
            }
        }

        if (start_idx <= g_cnt &&
            g_queue[queue_idx] < g_mem[g_table[start_idx]]) {
            // g_table[start_idx]左面的数据全部入队
            for (i = start_idx; i < g_table[start_idx]; i++) {
                g_queue[g_queue_tail++] = g_mem[i];
            }
            printf("%d", g_mem[g_table[start_idx]]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }

            start_idx = g_table[start_idx] + 1;

            continue;
        }

        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail - 1]) {
            printf("%d", g_queue[g_queue_head + 1]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }
            g_queue[g_queue_head + 1] = MIN;
            g_queue_head++;
        }
        else {
            printf("%d", g_queue[g_queue_tail - 1]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }
            g_queue[g_queue_tail - 1] = MIN;
            g_queue_tail--;
        }
    }

    return;
}

static void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    // 从1开始
    g_mem = new int[g_cnt + 1];
    g_heap = new int[g_cnt + 1];
    g_queue = new int[g_cnt + 2]; // 第0个和最后一个都是不存东西的
    g_table = new int[g_cnt + 1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }

    // 数字序列从1开始
    // g_queue_head + 1是实际的队列头元素
    // g_queue_tail - 1是实际的队列尾元素
    // g_queue_head + 1 == g_queue_tail，表示队列空
    g_queue_head = 0;
    g_queue_tail = 1;
    g_queue[g_queue_head] = MIN;
    g_queue[g_queue_tail] = MIN;

    return;
}

static void end()
{
    delete[] g_mem;
    delete[] g_heap;
    delete[] g_queue;

    return;
}

void test1()
{
    init();

    //process();
    process_new();

    end();

    return;
}
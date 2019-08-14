/* 题目
            中位数
*   描述
            小粽最近学习了中位数的相关知识，她知道了这样
     一个事实：对于任意2n-1 个数，将它们从小到大排序后，
     第n 个数就是这个2n-1 个数的中位数。
             现在，小粽想解决这样一个问题：对于一个长度为
     2n-1 的数列，前2k-1(k=1,2,3...n) 个数的中位数各是多少？
*   输入格式
            第一行一个正整数 n ，表示有一个长度为2n-1 的数列
            接下来一行2n-1 个正整数，描述这个数列，用空格隔开。
*   输出格式
            输出n 行，第i 行表示这个数列的前2n-1 个数的中位数
*   输入样例
            3
            8 7 6 9 9
*   输出样例
            8
            7
            8
*   限制
            对于100% 的数据，n<=3*10^5
            所有输入数据的数值都在 int 范围内。
*   提示
            [使用两个堆分别保存前一半和后一半大的数。]
*   我的思路
            从输出样例可以将题意翻译为，每次从原数列中找
     出前2k-1 个数，求这2k-1 个数的中位数。每次找出前2k-1 
     个数，都要先对这些做排序，然后才能找出对应的中位
     数，如果每次都排序，那时间复杂度就高了，关键就是
     想一种方法，能够在整个程序运行过程中只排一次序就
     可以把每次需要的中位数求出来。插入排序满足这种需
     求，因为每次做排序时，插入排序都可以利用2(k-1)-1 个数
     时已经排好的序。
             注意边界情况的处理，如果与中位数相同的数有多个，
     此时必须兼容这种情况。
            利用堆的方式:
                    思考中位数的性质，对于一个已经排序的数列来讲，
            中位数左面的(假设从左到右是从小到大的顺序) 数都一定
            小于中位数，中位数右面的数都大于中位数，由此可以建
            立两个堆，大根堆保存中位数左面小于中位数的数，堆顶
            就是这个中位数；小根堆保存中位数右面大于中位数的数。
            大根堆的节点数比小根堆多1，每次求中位数的时候，只要
            看大根堆的堆顶是谁就可以。当继续求下一个数列的中位数
            时，需要往当前数列新加入两个数，形成一个新的数列，并
            求这个新数列的中位数。关键就在于如何利用旧数列中已
            存在的两个堆。
                    其实根本不用关心中位数两边的数的排序情况，即，中位
            数左边和右边的具体排序情况根本用不着知道，只要知道谁在
            中位数的左边，谁在中位数的右边即可。根据中位数的性质，
            在每次新加入两个数形成新数列的时候，分别判断这两个数
            和旧数列中位数的关系，大于中位数的数放右边的小根堆，小
            于中位数的数放左面的大根堆，此时大根堆的堆顶就是新数
            列的中位数；如果两个数都大于中位数，则将两个数都放入
            右边小根堆，但此后应该从小根堆再弹出一个堆顶给左面的大
            根堆，以保证两个堆的节点个数差值为1(大根堆- 小根堆= 1，因
            为大根堆包含了中位数而小根堆不包含中位数)；如果两个数
            都小于中位数，则将两个数都放到左面大根堆中，然后再弹出
            一个堆顶给右面的小根堆，此时左面大根堆的堆顶就是新数列
            的中位数。
            关键点:
                    大根堆节点数- 小根堆节点数= 1；
                    配合堆的功能，利用好中位数的性质，在已知旧数列的
            中位数的前提下，利用好这个中位数，可以在不排序所有数
            据的情况下，求出新数列的中位数。
*   启发
            不完全排序的时间复杂度肯定低于完全排序，应多思考如何
     通过不完全排序就得出最终结果；
            列用各种数据结构的性质，尤其是堆的性质，结合题意所求
     问题的性质，思考不完全排序的方法。
            本题是二分处理的一个典型，二分+ 堆，应该成为今后处理问题
     的一个思路。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

int g_cnt;
int* g_mem;
int* g_sheap; // 小根堆
int* g_bheap; // 大根堆，要包含中位数

void swap_heap(int *heap, int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = heap[heap_child_idx];
    heap[heap_child_idx] = heap[heap_dad_idx];
    heap[heap_dad_idx] = tmp;

    return;
}

int delete_peak_from_small_heap()
{
    int *tmp_heap;
    int i, child, peak, heap_size;

    heap_size = g_sheap[0];
    if (heap_size <= 0) {
        return -1;
    }
    
    peak = g_sheap[1];
    g_sheap[1] = g_sheap[heap_size--];
    g_sheap[0] = heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_sheap[child] >= g_sheap[child+1]) {
            child++;
        }
        if (g_sheap[i] <= g_sheap[child]) {
            break;
        }
        tmp_heap = g_sheap;
        swap_heap(tmp_heap, i, child);
    }
    
    return peak;
}

void insert_small_heap(int val)
{
    int *tmp_heap;
    int i, dad, heap_size;

    heap_size = g_sheap[0];
    g_sheap[++heap_size] = val;
    g_sheap[0] = heap_size;

    for (i = heap_size; (i>>1) >= 1; i = dad) {
        dad = i >> 1;

        if (g_sheap[i] >= g_sheap[dad]) {
            break;
        }
        tmp_heap = g_sheap;
        swap_heap(tmp_heap, dad, i);
    }

    return;
}

int delete_peak_from_big_heap()
{
    int *tmp_heap;
    int i, child, peak, heap_size;

    heap_size = g_bheap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_bheap[1];
    g_bheap[1] = g_bheap[heap_size--];
    g_bheap[0] = heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_bheap[child] <= g_bheap[child+1]) {
            child++;
        }
        if (g_bheap[i] >= g_bheap[child]) {
            break;
        }
        tmp_heap = g_bheap;
        swap_heap(tmp_heap, i, child);
    }

    return peak;
} 

void insert_big_heap(int val)
{
    int *tmp_heap;
    int i, dad, heap_size;

    heap_size = g_bheap[0];
    g_bheap[++heap_size] = val;
    g_bheap[0] = heap_size;

    for (i = heap_size; (i>>1) >= 1; i = dad) {
        dad = i >> 1;
        
        if (g_bheap[i] <= g_bheap[dad]) {
            break;
        }
        tmp_heap = g_bheap;
        swap_heap(tmp_heap, dad, i);
    }

    return;
}

void process()
{
    int i, j, tmp, old_median;
    
    // 先处理一个数的情况
    i = 1;
    insert_big_heap(g_mem[i]);
    printf("%d\n", g_bheap[1]);

    // 2k-1, k = 1,2,3...，
    // 其实就是每次往旧数列中加两个数进去就是新数列
    while (i < g_cnt) {
        old_median = g_bheap[1];

        for (j = 0; j < 2; j++) {
            tmp = g_mem[++i];
            if (tmp <= old_median) {
                insert_big_heap(tmp);
                continue;
            }
            insert_small_heap(tmp);
        }

        /* 保证cnt(big_heap) - cnt(small_heap) = 1        
              *   他俩的差值只有如下几种情况: 3/1/-1
              *   分别对应: 两个都给左面/ 左右一家一个/ 两个都给右面
              */
        if (3 == g_bheap[0] - g_sheap[0]) {
            tmp = delete_peak_from_big_heap();
            insert_small_heap(tmp);

            printf("%d\n", g_bheap[1]);
            continue;
        }
        if (-1 == g_bheap[0] - g_sheap[0]) {
            tmp = delete_peak_from_small_heap();
            insert_big_heap(tmp);

            printf("%d\n", g_bheap[1]);
            continue;
        }

        printf("%d\n", g_bheap[1]);
    }

    return;
}

void init()
{
    int i, tmp;

    scanf("%d", &tmp);
    getchar();

    // 由此可知，总数据个数一定是个奇数
    g_cnt = tmp * 2 - 1;

    // 从1 开始
    g_mem = new int[g_cnt+1];

    /* 大根堆，保存中位数左边的全部数据
       *   如果不带上中位数，则该堆中有tmp-1 个数；
       *   带上中位数，有tmp 个数；又因为g_bheap[0] 用于
       *   存堆中节点个数，所以总个数为tmp+1
       */
    g_bheap = new int[tmp+1];

    /* 小根堆，保存中位数右边的全部数据
       *   因为不带中位数，所以堆中有tmp-1 个数；
       *   又因为g_sheap[0] 用于存堆中节点个数，所以
       *   总个数为tmp
       */
    g_sheap = new int[tmp];

    for (i = 1; i <= g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }
    g_bheap[0] = 0;
    g_sheap[0] = 0;

    return;
}

void end()
{
    delete[] g_mem;
    delete[] g_bheap;
    delete[] g_sheap;

    return;
}

int main()
{
    init();

    process();

    end();

    return 0;
}

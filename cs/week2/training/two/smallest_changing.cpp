/* 题目
            最小交换
*   描述
            给定一个 1 到 n 的排列（即一个序列，其中 [1,n] 之间的正整
     数每个都出现了恰好 1 次）。你可以花 1 元钱交换两个相邻的
     数。现在，你希望把它们升序排序。求你完成这个目标最少
     需要花费多少元钱。
*   输入格式
            第一行一个整数 n，表示排列长度。
            接下来一行 n 个用空格隔开的正整数，描述这个排列。
*   输出格式
            输出一行一个非负整数，表示完成目标最少需要花多少元钱。
*   输入样例1
            3
            3 2 1
*   输出样例
            3
*   样例1解释
            你可以：
            花 1 元交换 1,2，序列变成 3 1 2。
            花 1 元交换 1,3，序列变成 1 3 2。
            花 1 元交换 2,3，序列变成 1 2 3。
            总共需要花 3 元。
            可以证明不存在更优的解。
*   限制
            对于 20% 的数据，保证 n<=7。
            对于 60% 的数据，保证 n<=1,000。
            对于 100% 的数据，保证 n<=200,000。
            时间限制：4 sec
            空间限制：256 MB
*   提示
            [每次交换相邻的两个数都会使逆序对 +1 或 -1。]
            [逆序对数目不为零时，一定存在相邻的逆序对。]
            [因此最优策略显然是每次都让逆序对数目 -1。]
            [所以答案即为逆序对数目。]
            [朴素的算法时间复杂度是 O(n^2) 的。]
            [用归并排序求逆序对数可以通过本题。需要提醒的是，答案可能超过 32 位整数的范围哦。]
            [逆序对数目同样可以用树状数组优化朴素的 O(n^2) 算法，并获得和归并排序相同的时间复杂度。有兴趣的同学可以自行学习。]
*   我的思路
            就是用归并排序求解逆序对个数。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

typedef long long s64;

int g_cnt;
s64 g_inversions_cnt;
int* g_mem;
int* g_tmp;

void merge(int left_lo, int right_lo, int right_hi)
{
    int tmp_idx, start_idx, left_hi;

    left_hi = right_lo - 1;
    start_idx = left_lo;
    tmp_idx = start_idx;

    // 二路合并
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;
            continue;
        }

        // 左边大于右边，即存在逆序对
        // tips: 左右两边都已经排好序，所以如果g_mem[left_lo] 大于g_mem[right_lo]，
        // 也就意味着左边从left_lo~left_hi 都大于g_mem[right_lo]
        g_inversions_cnt += left_hi - left_lo + 1;
        g_tmp[tmp_idx++] = g_mem[right_lo];
        right_lo++;
    }

    while (left_lo <= left_hi) {
        g_mem[right_hi--] = g_mem[left_hi];
        left_hi--;
    }
    while (start_idx < tmp_idx) {
        g_mem[start_idx] = g_tmp[start_idx];
        start_idx++;
    }

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int median;

    // 递归基
    if (lo == hi) {
        return;
    }

    median = (lo + hi) / 2;
    merge_sort_by_recursion(lo, median);
    merge_sort_by_recursion(median+1, hi);
    merge(lo, median+1, hi);

    return;
}

void merge_sort()
{
    int lo, hi;

    lo = 0;
    hi = g_cnt - 1;

    merge_sort_by_recursion(lo, hi);
    printf("%lld\n", g_inversions_cnt);

    return;
}

void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    g_mem = new int[g_cnt];
    for (i = 0; i < g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }
    g_tmp = new int[g_cnt];
    g_inversions_cnt = 0;

    return;
}

void end()
{
    delete[] g_mem;
    delete[] g_tmp;

    return;
}

int main()
{
    init();

    merge_sort();

    end();
    return 0;
}


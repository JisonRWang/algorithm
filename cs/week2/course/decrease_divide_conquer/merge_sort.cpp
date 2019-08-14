/* 归并排序
*          归并排序是分而治之的绝佳体现
*   使用递归实现归并排序
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

int g_cnt;
int* g_mem;
int* g_tmp;

void merge(int left_lo, int right_lo, int right_hi)
{
    int tmp_start, left_hi, tmp_idx;

    left_hi = right_lo - 1;
    tmp_start = left_lo;
    tmp_idx = tmp_start;

    // 二路合并
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;
            continue;
        }
        g_tmp[tmp_idx++] = g_mem[right_lo];
        right_lo++;
    }

    // 此时，左右两边肯定有一个已经空了而另一个不空，不可能全空
    // 如果剩左面(说明右面肯定已经空了)，则先将左面的搬到右面
    while (left_lo <= left_hi) {
        g_mem[right_hi] = g_mem[left_hi];
        left_hi--;
        right_hi--;
    }
    // 将g_tmp 中的搬到g_mem
    while (tmp_start < tmp_idx) {
        g_mem[tmp_start] = g_tmp[tmp_start];
        tmp_start++;
    }

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int median;

    // 递归基
    // 其实数据量小的时候可以用插入排序解决
    if (lo == hi) {
        return;
    }

    median = (lo + hi) / 2;
    merge_sort_by_recursion(lo, median);
    merge_sort_by_recursion(median+1, hi);
    merge(lo, median+1, hi);

    return;
}

void print_result()
{
    int i;

    for (i = 0; i < g_cnt; i++) {
        printf("%d ", g_mem[i]);
    }
    printf("\n");

    return;
}

void merge_sort()
{
    int lo, hi;

    lo = 0;
    hi = g_cnt - 1;

    merge_sort_by_recursion(lo, hi);
    print_result();

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

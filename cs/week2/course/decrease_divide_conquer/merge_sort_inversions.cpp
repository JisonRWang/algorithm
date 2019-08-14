/* 使用归并排序的方法查找逆序对
*
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

int g_cnt;
int g_inversions_cnt;
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
    printf("%d\n", g_inversions_cnt);

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


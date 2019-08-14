/* �鲢����
*          �鲢�����Ƿֶ���֮�ľ�������
*   ʹ�õݹ�ʵ�ֹ鲢����
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

    // ��·�ϲ�
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;
            continue;
        }
        g_tmp[tmp_idx++] = g_mem[right_lo];
        right_lo++;
    }

    // ��ʱ���������߿϶���һ���Ѿ����˶���һ�����գ�������ȫ��
    // ���ʣ����(˵������϶��Ѿ�����)�����Ƚ�����İᵽ����
    while (left_lo <= left_hi) {
        g_mem[right_hi] = g_mem[left_hi];
        left_hi--;
        right_hi--;
    }
    // ��g_tmp �еİᵽg_mem
    while (tmp_start < tmp_idx) {
        g_mem[tmp_start] = g_tmp[tmp_start];
        tmp_start++;
    }

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int median;

    // �ݹ��
    // ��ʵ������С��ʱ������ò���������
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

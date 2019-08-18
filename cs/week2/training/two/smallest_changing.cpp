/* ��Ŀ
            ��С����
*   ����
            ����һ�� 1 �� n �����У���һ�����У����� [1,n] ֮�������
     ��ÿ����������ǡ�� 1 �Σ�������Ի� 1 ԪǮ�����������ڵ�
     �������ڣ���ϣ��������������������������Ŀ������
     ��Ҫ���Ѷ���ԪǮ��
*   �����ʽ
            ��һ��һ������ n����ʾ���г��ȡ�
            ������һ�� n ���ÿո������������������������С�
*   �����ʽ
            ���һ��һ���Ǹ���������ʾ���Ŀ��������Ҫ������ԪǮ��
*   ��������1
            3
            3 2 1
*   �������
            3
*   ����1����
            ����ԣ�
            �� 1 Ԫ���� 1,2�����б�� 3 1 2��
            �� 1 Ԫ���� 1,3�����б�� 1 3 2��
            �� 1 Ԫ���� 2,3�����б�� 1 2 3��
            �ܹ���Ҫ�� 3 Ԫ��
            ����֤�������ڸ��ŵĽ⡣
*   ����
            ���� 20% �����ݣ���֤ n<=7��
            ���� 60% �����ݣ���֤ n<=1,000��
            ���� 100% �����ݣ���֤ n<=200,000��
            ʱ�����ƣ�4 sec
            �ռ����ƣ�256 MB
*   ��ʾ
            [ÿ�ν������ڵ�����������ʹ����� +1 �� -1��]
            [�������Ŀ��Ϊ��ʱ��һ���������ڵ�����ԡ�]
            [������Ų�����Ȼ��ÿ�ζ����������Ŀ -1��]
            [���Դ𰸼�Ϊ�������Ŀ��]
            [���ص��㷨ʱ�临�Ӷ��� O(n^2) �ġ�]
            [�ù鲢�����������������ͨ�����⡣��Ҫ���ѵ��ǣ��𰸿��ܳ��� 32 λ�����ķ�ΧŶ��]
            [�������Ŀͬ����������״�����Ż����ص� O(n^2) �㷨������ú͹鲢������ͬ��ʱ�临�Ӷȡ�����Ȥ��ͬѧ��������ѧϰ��]
*   �ҵ�˼·
            �����ù鲢�����������Ը�����
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

    // ��·�ϲ�
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;
            continue;
        }

        // ��ߴ����ұߣ������������
        // tips: �������߶��Ѿ��ź����������g_mem[left_lo] ����g_mem[right_lo]��
        // Ҳ����ζ����ߴ�left_lo~left_hi ������g_mem[right_lo]
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

    // �ݹ��
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


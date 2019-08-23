/* ��Ŀ
            �ܲ�2
*   ����
            ����һ����������������ö�������n = 2^m ��Ҷ�ӣ�ÿ��Ҷ��
     ����һ�����֣��Ҵ������ҿ�ȥ����Щ����������һ��1 ��n �����С�
            ������ÿ����Ҷ�ڵ㶼����������ؽ������Һ��ӣ��ҽ���û��
     �Ⱥ�˳���Ҫ�󡣽������Ժ󣬴������ҿ�ȥ��Ҷ����ɵ���������
     ������1��n �����У�������Կ��ܷ����˸ı�Ŷ~            
            ������Ҫ���һ����ѵĽ���������ʹ��Ҷ����ɵ��������е���
     �����Ŀ����С��
*   �����ʽ
            ����ĵ�һ�а���һ�������� n�������������Ϊ2���ݴΡ�            
            ������1 �а���n ��������һ��1��n �����У����α�ʾ��ʼ״̬�£�
     �����ҿ�����Ҷ���ϵ��������С�
*   �����ʽ
            ���1 ��1 ������������С������Ը�����
*   ��������
            8
            3 1 6 2 8 7 4 5
*   �������
            3
*   ��������
            ���������һ��ʼ��������
             a
          /     \
        /         \
      b             c
    /   \         /   \
  d      e      f      g
 / \    / \    / \    / \
3   1  6   2  8   7  4   5
            ����һϵ�з�Ҷ�ڵ�����Һ��ӽ�����
            swap(left(c), right(c))
            swap(left(e), right(e))
            swap(left(d), right(d))
            swap(left(f), right(f))
            �õ����ŵķ�����
             a
          /     \
        /         \
      b             c
    /   \         /   \
  d      e      g      f
 / \    / \    / \    / \
1   3  2   6  4   5  7   8
            ��Ҷ����ɵ���������Ϊ
            1 3 2 6 4 5 7 8
            ����Ը���Ϊ3��������֤������������ŵġ�
*   ����
            ����20%�����ݣ�m��10��            
            ����40%�����ݣ�m��18��            
            ʣ��20%�����ݣ�m��20��
            ʱ�䣺2 sec
            �ռ䣺256 MB
*   �ҵ�˼·
            �鲢�������һӦ�á�
            ��ʵ�Ͷ�����һ���ϵ��û�У������У��ᵽ��������ΨһĿ�ľ�
     ��˵������������������Ԫ�ظ�����2 ���ݣ����Ҫ�ƶ���Ҳֻ����2
     ���ݵĸ���ȥ�ƶ���Щ��������2 ���ݣ�ֱ���뷨���Ƕ��֣���˵����
     ��ԣ�ֱ�Ӿ����鲢�����Ͽ���
            �����У��ܽ�����λ��ֻ�����������е�13/26/45/78 ��de/gf/bc ��Щ����
     ���ܽ���32/64/57/eg ������λ�á���Щ�ܽ�����λ����ʵ���ǹ鲢������
     ���������ߣ��Ƿ�Ҫ�������Ϳ���߷����ұߵ�����������ٻ���˵��
     �ұ߷ŵ���ߵ�����������١��������߱Ƚϼ�������Ե�ʱ���ǲ�
     ���ټ�����߻��ұ��Լ��ڲ�������Եģ���Ϊ�Ѿ�������ˣ����Կ�
     �����������Լ��ڲ������������Ա�֤���������ڶ�·�ϲ���ʱ����
     ���ټ�������Ը�����
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

typedef long long s64;

s64 g_inversions_cnt;
int g_n;
int *g_mem;
int *g_tmp;

s64 ivs_cnt(int left_lo, int left_hi, int right_lo, int right_hi)
{
    s64 tmp_cnt;

    tmp_cnt = 0;
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            left_lo++;
            continue;
        }
        right_lo++;
        tmp_cnt += left_hi - left_lo + 1;
    }

    return tmp_cnt;
}

void merge(int left_lo, int right_lo, int right_hi)
{
    s64 l_ivs_cnt, r_ivs_cnt;
    int start_idx, tmp_idx, left_hi;
 
    tmp_idx = left_lo;
    start_idx = tmp_idx;
    left_hi= right_lo - 1;

    /* ��Ϊ�������ʱ�޷�׼ȷ������ߵ�����ԣ��������ר��
       *   ���������߽��������ڼ���ԭ�����������ұߵ�����ԡ�
       */ 
    l_ivs_cnt = ivs_cnt(right_lo, right_hi, left_lo, left_hi);
    r_ivs_cnt = 0;
    
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;

            continue;
        }
        g_tmp[tmp_idx++] = g_mem[right_lo];
        right_lo++;

        // ��ߴ����ұߣ������ұ����������������
        r_ivs_cnt += left_hi - left_lo + 1;
    }

    // ��������ȿգ�������ʣ��
    while (left_lo <= left_hi) {
        g_mem[right_hi--] = g_mem[left_hi];
        left_hi--;
    }
    while (start_idx < tmp_idx) {
        g_mem[start_idx] = g_tmp[start_idx];
        start_idx++;
    }

    g_inversions_cnt += (l_ivs_cnt <= r_ivs_cnt) ? l_ivs_cnt: r_ivs_cnt;

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int mid;

    // �ݹ��
    if (lo == hi) {
        return;
    }

    mid = (lo + hi) / 2;
    merge_sort_by_recursion(lo, mid);
    merge_sort_by_recursion(mid+1, hi);
    merge(lo, mid+1, hi);

    return;
}

void process()
{
    merge_sort_by_recursion(1, g_n);

    printf("%lld\n", g_inversions_cnt);

    return;
}

void init()
{
    int i;

    scanf("%d", &g_n);
    getchar();

    g_inversions_cnt = 0;
    g_mem = new int[g_n+1];
    g_tmp = new int[g_n+1];
    for (i = 1; i <= g_n; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }

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

    process();

    end();

    return 0;
}


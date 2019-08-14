/* ��Ŀ
*          �ɼ�����
*  ����
            �� n ��ѧ�������ǵ�ѧ�ŷֱ��� 1,2,��,n����Щѧ����ѡ��
    �˵���ʦ���㷨ѵ��Ӫ�����ݽṹѵ��Ӫ�����ſγ̡�
            ѧ�ڽ����ˣ�����ѧ���Ŀγ��������ѹ���������������
    ������ [0,100] ֮����������ɺϵ��ǣ���������λͬѧ������
    �����ſεĳɼ�����ȫ��ͬ������ʦϣ������Щ���е�ѧ����
    �����ſγ̵��ֽܷ��н��������ر�أ������λͬѧ����
    ����ͬ���ǵ���ʦϣ�����㷨ѵ��Ӫ�÷ָ��ߵ�ͬѧ����ǰ�档
    ���������ᵽ���ɺϣ����ԣ����������Ϳ��Ա�֤û�в��е�
    ͬѧ�ˡ�
            ����ʦ������������񽻸����������̡����Ǵ��ĵ�����û��
    ������ʦ��Ҫ�󣬽�����ѧ����ѧ�Ž��������򡣵���ʦϣ��
    ֪�������̵��������У����ڶ�������ԡ�
            �����������ѧ�� (i,j) ���ԣ�i �������� j ǰ�棬����i ��Ӧ����
    �� j �ĺ��棬���Ǿͳ� (i,j) ��һ������ԡ�
            �����Ȱ����ʦ������ѧ������ȷ��˳������������ٸ�����
    ���̵Ĵ�������������Ե���Ŀ��
*  �����ʽ
            ��һ��һ������ n����ʾѧ���ĸ�����
            �� 2 �е��� n+1 �У�ÿ�� 2 ���ÿո�����ķǸ��������� i+1 �е�
    ���������α�ʾѧ��Ϊ i ��ͬѧ���㷨ѵ��Ӫ�����ݽṹѵ��Ӫ��
    �����ɼ���
*  �����ʽ
            ������� n+1 �С�
            ǰ n �б�ʾ��ȷ����������ÿ�� 4 ���ÿո�������������� i ��
    �������α�ʾ����Ϊ i ��ͬѧ��ѧ�š��ܷ֡��㷨ѵ��Ӫ�ɼ�������
    �ṹѵ��Ӫ�ɼ���
            �� n+1 ��һ����������ʾ���̵Ĵ�������������Ե���Ŀ��
*  ��������
            3
            95 85
            90 90
            100 99
*  �������
            3 199 100 99
            1 180 95 85
            2 180 90 90
            2
*  ��������
            ѧ��Ϊ 3 ��ͬѧ�ܷ�Ϊ 199������ߵģ�������Ӧ���ŵ�һ����
            ѧ��Ϊ 1 ��ͬѧ��Ȼ�ܷ���ѧ��Ϊ 2 ��ͬѧһ�£����������㷨ѵ
    ��Ӫ�ɼ����ߣ����������������¸�ʤһ�
            ԭ���������е��������ĿΪ 2 ����Щ����Էֱ�Ϊ (1,3) �� (2,3)��
*  ���ݷ�Χ
            ���� 25% �����ݣ���֤ n=3��
            ���� 50% �����ݣ���֤ n��10��
            �������� 25% �����ݣ���֤����ͬѧ���ܷ�������ͬ��
            ���� 100% �����ݣ���֤ n��5,000 ���ұ�֤�����ڳɼ���ȫ��ͬ��ѧ����
            ʱ�����ƣ�10 sec
            �ռ����ƣ�256 MB
*  ��ʾ
           [����ʹ��������������ѧ������������]
           [����������Ĺ����У�ÿ�ν�������ʹ�������Ŀ���� 1 ]
           [����������Ƴ�ʱ�临�Ӷ�Ϊ O(nlogn) ���㷨��]
*  �ҵ�˼·
           �ù鲢����������Եķ�����ʱ�临�Ӷ�ΪO(nlogn)
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

typedef struct score
{
    int algorithm_score;
    int datastructure_score;
    int sum;
}score_s;

int g_cnt;
int g_inversions_cnt;
score_s *g_mem;
int *g_arr; // ��g_mem������
int *g_tmp;

void merge(int left_lo, int right_lo, int right_hi)
{
    int left_hi, end_idx, tmp_idx;

    left_hi = right_lo - 1;
    end_idx = right_hi;
    tmp_idx = end_idx;

    // ��·�ϲ�
    // �������⣬�Ӵ�С����
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if ((g_mem[g_arr[left_hi]].sum < g_mem[g_arr[right_hi]].sum) ||
            ((g_mem[g_arr[left_hi]].sum == g_mem[g_arr[right_hi]].sum) && 
             (g_mem[g_arr[left_hi]].algorithm_score < g_mem[g_arr[right_hi]].algorithm_score))) {
            // ͳ�������(��ߵĶ�Ӧ�ô����ұߵģ������������)
            g_inversions_cnt += right_hi - right_lo + 1;

            g_tmp[tmp_idx--] = g_arr[left_hi];
            left_hi--;
            continue;
        }
        
        if ((g_mem[g_arr[left_hi]].sum > g_mem[g_arr[right_hi]].sum) ||
            ((g_mem[g_arr[left_hi]].sum == g_mem[g_arr[right_hi]].sum) &&
             (g_mem[g_arr[left_hi]].algorithm_score > g_mem[g_arr[right_hi]].algorithm_score))) {
            g_tmp[tmp_idx--] = g_arr[right_hi];
            right_hi--;
        }
    }

    // �ұ���ʣ�࣬����Ѿ����ˣ����ұ߿��������
    while (right_lo <= right_hi) {
        g_arr[left_lo++] = g_arr[right_lo];
        right_lo++;
    }
    while (tmp_idx < end_idx) {
        g_arr[end_idx] = g_tmp[end_idx];
        end_idx--;
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

void print_result()
{
    int i;

    for (i = 1; i <= g_cnt; i++) {
        printf("%d %d %d %d\n", 
            g_arr[i], g_mem[g_arr[i]].sum, 
            g_mem[g_arr[i]].algorithm_score, g_mem[g_arr[i]].datastructure_score);
    }

    printf("%d\n", g_inversions_cnt);
    return;
}

void merge_sort()
{
    int lo, hi;

    lo = 1;
    hi = g_cnt;
    merge_sort_by_recursion(lo, hi);
    print_result();

    return;
}

void init()
{
    int i;
    
    scanf("%d", &g_cnt);
    getchar();

    // ѧ�Ŵ�1 ��ʼ
    g_mem = new score_s[g_cnt+1];
    g_arr = new int[g_cnt+1];
    g_tmp = new int[g_cnt+1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d %d", &g_mem[i].algorithm_score, &g_mem[i].datastructure_score);
        getchar();
        g_mem[i].sum = g_mem[i].algorithm_score + g_mem[i].datastructure_score;

        g_arr[i] = i;
    }
    g_inversions_cnt = 0;

    return;
}

void end()
{
    delete[] g_mem;
    delete[] g_arr;
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

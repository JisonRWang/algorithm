/* ��Ŀ
            ������
*   ����
            С�ս����������ǡ�
            С�հ�������տ���һ��ƽ�棬���������������
     ÿ�����ǵ����꣬�� i �����ǵ�����Ϊ (x[i],y[i])��������
     ��ʵ����̫�����ˣ�С����֪��������ÿ�����ǣ���
     ���·������ǵ�������������ÿ�� i��С����Ҫ֪����
     �� j��i���� x[j]��x[i],y[j]��y[i] �� j ��������
*   �����ʽ
            ��һ��һ�������� n����ʾ���ǵ������������� n �У�
     ÿ������������ x[i],y[i]����ʾ�� i �����ǵ����ꡣ
*   �����ʽ
            ����� n �У�ÿ�����һ������������ʾ�� i ������
     ���·����ǵ�������
*   ��������1
            5
            1 1
            5 1
            7 1
            3 3
            5 5
*   �������
            0
            1
            2
            1
            3
*   ����
            ���� 30% �������� n��500��
            ���� 60% �������� n��8000��
            ���� 100% �������� n��3��10^5���������궼�� int ��Χ�ڣ�
     ������������ͬ�ĵ�����ͬ�����ꡣ
*   ��ʾ
            [����һ�¹鲢�������զ���ģ���ͻ����������]
            [����Ȥ��ͬѧ�ٶȶ�άƫ��~]
*   �ҵ�˼·
            һ��ʼ�����ÿ����ȶ�x ����һ����������������ϣ�����
     ��k ������ķ���ȥ�ж��ھ�����x ����������ϣ���ĳ��ĺ���
     ��x ������������У��õ��y ��������еڼ���������õ��Ľ�
     ����������������ϸ��������ʵ���ַ���������������졣
            �پ��Ǳ�����ʾ�Ĺ鲢������ķ�����������⡣
            �����Ƚ�����������x ������һ������Ȼ����y ����һ�ι鲢
     ������y ���鲢�����ʱ�����߻��Ұ���ڲ���x ��˳����
     �����ù��ģ���Ϊ�ڵݹ鵽��ײ��ʱ���Ѿ��������ˣ�����
     ��x ����һ��С���Ұ�ߵ�x ���꣬����ֻҪ֪��ÿ���������Щ
     ���y С���ұߵ�ǰ��ֵ�ͺ��ˡ�
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

#define CODI_X 0
#define CODI_Y 1

typedef struct point
{
    int cnt;
    int coordinate[2];
}point_s;

int g_cnt;
point_s *g_mem;
int *g_arr;
int *g_tmp;

void merge(int left_lo, int right_lo, int right_hi, int cord)
{
    int tmp_idx, start_idx, left_hi;

    tmp_idx = right_hi;
    start_idx = tmp_idx;
    left_hi = right_lo - 1;

    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[g_arr[left_hi]].coordinate[cord] <= g_mem[g_arr[right_hi]].coordinate[cord]) {
            /* ��x �����ʱ���������x ��ȵ��������y ����ĵ�
                     *  �ŵ����棬�����ڶ�y �����ʱ�����������벿�ֵ�
                     *  y �����Ұ벿�ֵ�y ����˵����ʱλ����벿�ֵĸõ��x 
                     *  һ��С���Ұ벿���Ǹ����x���������������x ��ȵ���
                     *  ������ʾ��������Ѿ�˵������������������ȫ��ͬ�ĵ㣬
                     *  �������x ��ͬ��y �϶���ͬ�����y ��ͬ��x �϶���ͬ��
                     */
            if (CODI_X == cord &&
                (g_mem[g_arr[left_hi]].coordinate[cord] == g_mem[g_arr[right_hi]].coordinate[cord]) &&
                (g_mem[g_arr[left_hi]].coordinate[CODI_Y] > g_mem[g_arr[right_hi]].coordinate[CODI_Y])) {
                    g_tmp[tmp_idx--] = g_arr[left_hi];
                    left_hi--;
                    continue;
            }

            /* ���Ǳ߽������
                     *   y ��ͬx ��ͬ: ��Ϊ�Ȱ�x �������Դ�ʱx С��һ��������
                     *   ��ô��������Ұ����û���
                     *   x ��ͬy ��ͬ: ��ȻӦ��������Ұ��
                     */ 
            if (CODI_Y == cord) {
                g_mem[g_arr[right_hi]].cnt += left_hi - left_lo + 1;
            }
            
            g_tmp[tmp_idx--] = g_arr[right_hi];
            right_hi--;
            continue;
        }

        /* ������x ��ʱ�򣬾ͱ�֤�˶���x ��ͬ���������y �������
              *   ���棬��������y ��ʱ������ߵ����˵����벿�ֵ�
              *   y һ�������Ұ벿�ֵ�y������x �϶������(ȷ�е�˵����ʱ
              *   ��ߵ�x һ��С���ұߵ�x)��
              */
        g_tmp[tmp_idx--] = g_arr[left_hi];
        left_hi--;
    }

    // ��������ȿգ����Ұ��ʣ��Ŀ���������
    while (right_lo <= right_hi) {
        g_arr[left_lo++] = g_arr[right_lo];
        right_lo++;
    }
    while (tmp_idx < start_idx) {
        g_arr[start_idx] = g_tmp[start_idx];
        start_idx--;
    }
    
    return;
}

void merge_sort(int lo, int hi, int cord)
{
    int mid;

    // �ݹ��
    if (lo == hi) {
        return;
    }

    mid = (lo + hi) / 2;
    merge_sort(lo, mid, cord);
    merge_sort(mid+1, hi, cord);
    merge(lo, mid+1, hi, cord);

    return;
}

void process()
{
    int i;
    
    merge_sort(1, g_cnt, CODI_X);
    merge_sort(1, g_cnt, CODI_Y);

    for (i = 1; i <= g_cnt; i++) {
        printf("%d\n", g_mem[i].cnt);
    }

    return;
}

void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    // ��1 ��ʼ
    g_mem = new point_s[g_cnt+1];
    g_arr = new int[g_cnt+1];
    g_tmp = new int[g_cnt+1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d %d", &g_mem[i].coordinate[CODI_X], &g_mem[i].coordinate[CODI_Y]);
        getchar();

        g_mem[i].cnt = 0;
        g_arr[i] = i;
    }

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

    process();

    end();

    return 0;
}


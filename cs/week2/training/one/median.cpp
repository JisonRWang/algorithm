/* ��Ŀ
            ��λ��
*   ����
            С�����ѧϰ����λ�������֪ʶ����֪��������
     һ����ʵ����������2n-1 �����������Ǵ�С���������
     ��n �����������2n-1 ��������λ����
             ���ڣ�С����������һ�����⣺����һ������Ϊ
     2n-1 �����У�ǰ2k-1(k=1,2,3...n) ��������λ�����Ƕ��٣�
*   �����ʽ
            ��һ��һ�������� n ����ʾ��һ������Ϊ2n-1 ������
            ������һ��2n-1 ��������������������У��ÿո������
*   �����ʽ
            ���n �У���i �б�ʾ������е�ǰ2n-1 ��������λ��
*   ��������
            3
            8 7 6 9 9
*   �������
            8
            7
            8
*   ����
            ����100% �����ݣ�n<=3*10^5
            �����������ݵ���ֵ���� int ��Χ�ڡ�
*   ��ʾ
            [ʹ�������ѷֱ𱣴�ǰһ��ͺ�һ��������]
*   �ҵ�˼·
            ������������Խ����ⷭ��Ϊ��ÿ�δ�ԭ��������
     ��ǰ2k-1 ����������2k-1 ��������λ����ÿ���ҳ�ǰ2k-1 
     ��������Ҫ�ȶ���Щ������Ȼ������ҳ���Ӧ����λ
     �������ÿ�ζ�������ʱ�临�ӶȾ͸��ˣ��ؼ�����
     ��һ�ַ������ܹ��������������й�����ֻ��һ�����
     ���԰�ÿ����Ҫ����λ���������������������������
     ����Ϊÿ��������ʱ���������򶼿�������2(k-1)-1 ����
     ʱ�Ѿ��źõ���
             ע��߽�����Ĵ����������λ����ͬ�����ж����
     ��ʱ����������������
            ���öѵķ�ʽ:
                    ˼����λ�������ʣ�����һ���Ѿ����������������
            ��λ�������(����������Ǵ�С�����˳��) ����һ��
            С����λ������λ�����������������λ�����ɴ˿��Խ�
            �������ѣ�����ѱ�����λ������С����λ���������Ѷ�
            ���������λ����С���ѱ�����λ�����������λ��������
            ����ѵĽڵ�����С���Ѷ�1��ÿ������λ����ʱ��ֻҪ
            ������ѵĶѶ���˭�Ϳ��ԡ�����������һ�����е���λ��
            ʱ����Ҫ����ǰ�����¼������������γ�һ���µ����У���
            ����������е���λ�����ؼ�������������þ���������
            ���ڵ������ѡ�
                    ��ʵ�������ù�����λ�����ߵ��������������������λ
            ����ߺ��ұߵľ���������������ò���֪����ֻҪ֪��˭��
            ��λ������ߣ�˭����λ�����ұ߼��ɡ�������λ�������ʣ�
            ��ÿ���¼����������γ������е�ʱ�򣬷ֱ��ж���������
            �;�������λ���Ĺ�ϵ��������λ���������ұߵ�С���ѣ�С
            ����λ������������Ĵ���ѣ���ʱ����ѵĶѶ���������
            �е���λ���������������������λ������������������
            �ұ�С���ѣ����˺�Ӧ�ô�С�����ٵ���һ���Ѷ�������Ĵ�
            ���ѣ��Ա�֤�����ѵĽڵ������ֵΪ1(�����- С����= 1����
            Ϊ����Ѱ�������λ����С���Ѳ�������λ��)�����������
            ��С����λ���������������ŵ����������У�Ȼ���ٵ���
            һ���Ѷ��������С���ѣ���ʱ�������ѵĶѶ�����������
            ����λ����
            �ؼ���:
                    ����ѽڵ���- С���ѽڵ���= 1��
                    ��϶ѵĹ��ܣ����ú���λ�������ʣ�����֪�����е�
            ��λ����ǰ���£����ú������λ���������ڲ�����������
            �ݵ�����£���������е���λ����
*   ����
            ����ȫ�����ʱ�临�Ӷȿ϶�������ȫ����Ӧ��˼�����
     ͨ������ȫ����͵ó����ս����
            ���ø������ݽṹ�����ʣ������Ƕѵ����ʣ������������
     ��������ʣ�˼������ȫ����ķ�����
            �����Ƕ��ִ����һ�����ͣ�����+ �ѣ�Ӧ�ó�Ϊ���������
     ��һ��˼·��
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

int g_cnt;
int* g_mem;
int* g_sheap; // С����
int* g_bheap; // ����ѣ�Ҫ������λ��

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
    
    // �ȴ���һ���������
    i = 1;
    insert_big_heap(g_mem[i]);
    printf("%d\n", g_bheap[1]);

    // 2k-1, k = 1,2,3...��
    // ��ʵ����ÿ�����������м���������ȥ����������
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

        /* ��֤cnt(big_heap) - cnt(small_heap) = 1        
              *   �����Ĳ�ֵֻ�����¼������: 3/1/-1
              *   �ֱ��Ӧ: ������������/ ����һ��һ��/ ������������
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

    // �ɴ˿�֪�������ݸ���һ���Ǹ�����
    g_cnt = tmp * 2 - 1;

    // ��1 ��ʼ
    g_mem = new int[g_cnt+1];

    /* ����ѣ�������λ����ߵ�ȫ������
       *   �����������λ������ö�����tmp-1 ������
       *   ������λ������tmp ����������Ϊg_bheap[0] ����
       *   ����нڵ�����������ܸ���Ϊtmp+1
       */
    g_bheap = new int[tmp+1];

    /* С���ѣ�������λ���ұߵ�ȫ������
       *   ��Ϊ������λ�������Զ�����tmp-1 ������
       *   ����Ϊg_sheap[0] ���ڴ���нڵ����������
       *   �ܸ���Ϊtmp
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

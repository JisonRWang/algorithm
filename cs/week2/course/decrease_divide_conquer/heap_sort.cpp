/* ������
*           ��Ϊѡ��������Ż������ ������֮
*/

#include <iostream>
#include <cstdio> 

using namespace std;

int g_cnt;

int* g_mem;
int* g_heap;

void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

int delete_heap_peak()
{
    int i, child, peak, heap_size;

    heap_size = g_heap[0];
    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_heap[child] <= g_heap[child+1]) {
            child++;
        }
        if (g_heap[i] >= g_heap[child]) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

void process()
{
    int i, val;

    // ��ϸ��������֮�ĸо�
    for (i = g_cnt; i > 0; i--) {
        // ����൱�ڼ��Ĺ���
        // �����ѡ�����򣬶������������Ż����������ֵ�Ĺ��̡�
        // ��ͨ������ȫ�����ҵ������ֵ�����ѡ�����򷴸�������
        // �����ֵ����ʡ�˴���ʱ�䡣
        val = delete_heap_peak();
        g_heap[i] = val;
    }

    /* ����Ѵ�����δ��ڴ�ĩβ��ǰ�ţ��������ʱ���ڴ濪ͷ��
       *   �������������Ȼ����С�������
       */
    for (i = 1; i <= g_cnt; i++) {
        printf("%d ", g_heap[i]);
    }
    printf("\n");

    return;
}

// �����
void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size>>1; i >= 1; i--) {
        for (j = i; (j<<1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_heap[child] <= g_heap[child+1]) {
                child++;
            }
            if (g_heap[j] >= g_heap[child]) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    // �ȵ����ֵ���ԭʼ���ݵ��ڴ�
    g_mem = new int[g_cnt+1];
    g_heap = g_mem;
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
        g_heap[i] = g_mem[i];
    }
    g_heap[0] = g_cnt;
    create_heap();

    return;
}

void end()
{
    delete[] g_mem;

    return;
}

int main()
{
    init();

    process();

    end();

    return 0;
}

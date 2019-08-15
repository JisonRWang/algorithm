/* 堆排序
*           作为选择排序的优化，体会 减而治之
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

    // 仔细体会减而治之的感觉
    for (i = g_cnt; i > 0; i--) {
        // 这就相当于减的过程
        // 相对于选择排序，堆排序所做的优化就是找最大值的过程。
        // 堆通过不完全排序找到了最大值，相比选择排序反复做排序
        // 找最大值，节省了大量时间。
        val = delete_heap_peak();
        g_heap[i] = val;
    }

    /* 上面把大的依次从内存末尾往前放，这里遍历时从内存开头往
       *   后遍历，所以仍然按从小到大输出
       */
    for (i = 1; i <= g_cnt; i++) {
        printf("%d ", g_heap[i]);
    }
    printf("\n");

    return;
}

// 大根堆
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

    // 既当堆又当存原始数据的内存
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

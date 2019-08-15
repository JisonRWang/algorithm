/* 题目
            排序
*   描述
            给出n个整数，将它们从小到大排序后输出。
*   输入格式
            第一行为一个正整数n，第二行为n 个整数。
*   输出格式
            输出一行n个整数，表示排序后的n个整数。
*   输入样例
            5
            5 4 2 3 -1
*   输出样例
            -1 2 3 4 5
*   限制
            对于前30%的数据，n ≤ 100，给出的n个整数的绝对值不超过10；
            对于前60%的数据，n ≤ 5000，给出的n个整数的绝对值不超过10^9；
            对于另20%的数据，n ≤ 500000，给出的n个整数的绝对值不超过10^5；
            对于100%的数据，n ≤ 500000，给出的n个整数的绝对值不超过10^9。
            时间：2 sec
            空间：256 MB
*   提示
            若使用cin、cout进行输入输出，则需在main 函数里的第一行
     加入ios::sync_with_stdio(false)，否则可能会超时。
            推荐使用scanf 和printf 进行输入输出。
            不妨使用各种排序算法进行测试。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

// 插入排序
// 有4 个测试例超时，不适用于大量数据
#if 0
int g_cnt;
int* g_mem;

void print_result()
{
    int i;

    for (i = 0; i < g_cnt; i++) {
        printf("%d ", g_mem[i]);
    }
    printf("\n");

    return;
}

void insertion_sort()
{
    int i, j, tmp;

    // tips: [0, j] 都是已经排好序的数列
    for (i = 0; i < g_cnt; i++) {
        for (j = i; j-1 >= 0; j--) {
            if (g_mem[j] >= g_mem[j-1]) {
                // 前面已经排好序，所以直接break
                break;
            }
            tmp = g_mem[j];
            g_mem[j] = g_mem[j-1];
            g_mem[j-1] = tmp;
        }
    }

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

    insertion_sort();
    print_result();

    end();
    
    return 0;
}
#endif

// 堆排序
// 10 个测试例中，最慢的一个用时140ms
#if 0
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
#endif

// 归并排序
// 10 个测试例中，最慢的一个用时140ms
#if 0
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
#endif

// 仿照<<数据结构与算法- C 语言描述>> 中的快排写法
// 10 个测试例中，最慢的一个用时120ms

/* left和right之间的跨度 */
#define    CUTOFF    (3)

int g_cnt;
int* g_mem;

void print_result()
{
    int i;

    for (i = 0; i < g_cnt; i++) {
        printf("%d ", g_mem[i]);
    }
    printf("\n");

    return;
}

/* 并不是所有的内联都会被展开，编译器会根据实际情况决定是把内联函数展开还是当做一个一般的函数， 
*  比如该内联函数，使用gcc -E 会发现预编译之后的该函数被当做一般的函数来处理了。
*/
static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

/* 插入排序，处理少量数据 */
void insertionsort(int *array, int len)
{
    int i, j;
    int tmp;
    
    for (i = 1; i < len; i++)
    {
        tmp = array[i];
        for (j = i; j - 1 >= 0; j--)
        {
            if (array[j - 1] > tmp)
            {
                array[j] = array[j - 1];
            }
            else
            {
                break;
            }
        }
        array[j] = tmp;
    }

    return ;
}

/* 三数中值定理获取中值，并将该中值与(right - 1)位置处的数据交换。
*  这个过程不要考虑任何外部处理流程，会把思路搞乱。该函数只要
*  实现上面所说的功能即可。
*/
int getmedian3(int *array, int left, int right)
{
    int center;

    /* 将left, right center三者按照left < center < right的顺序排列 */
    center = (left + right) / 2;
    if (array[left] > array[center])
    {
        swap(&array[left], &array[center]);
    }
    if (array[left] > array[right])
    {
        swap(&array[left], &array[right]);
    }
    if (array[center] > array[right])
    {
        swap(&array[center], &array[right]);
    }

    /* 将center与right - 1位置处的数据交换 */
    swap(&array[center], &array[right - 1]);
    
    return array[right - 1];
}

/* tips: 该函数内部并没有改变left和right本身的值 */
void quicksort(int *array, int left, int right)
{
    int i, j;
    int pivot;    
    
    /* 分治过程的“分”过程: left + CUTOFF 仍然达不到right 时
       *   就进行“分”处理 
       */
    if (left + CUTOFF <= right) 
    {
        /* 这个过程将中值放到(right - 1)位置，并且保证left 处
              *   的值小于该值，right处的值大于该值 
              */
        pivot = getmedian3(array, left, right);
    
        /* 因为right处的值一定大于pivot，所以这里j 从pivot 的位置
              *   开始即可，left 处的值小于pivot，(right - 1)处的值就是该值，
              *   所以循环条件直接++ 和--
              */
        i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot) {} /* 从左向右找大于pivot的数 */
            while (array[--j] > pivot) {} /* 从右向左找小于pivot的数 */
            if (i < j)
            {
                swap(&array[i], &array[j]);
            }
            else
            {
                break;
            }
        }
        
        /* 此时ij 交汇，并且i 位置处的数大于pivot，所以交换一下。
              *  交换之后，i处就是pivot，将array分成两段, i左面的小于pivot，
              *  i右面的大于pivot
              */
        swap(&array[i], &array[right - 1]);
        
        /* 这是“分”的本质过程 
              *  tips: 在递归过程中，array始终都是原来最初的那个地址，变
              *  化的仅仅是每次递归传入的left和right而已
              */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
    }
    else /* 递归的基本情况，分治过程的“治”过程: left + CUTOFF > right，说明left和right之间的数据量已经很少了，此时不要再“分”，而是要“治” */
    {
        /* 直接用插入排序把这几个数据处理掉 */
        insertionsort(array + left, right - left + 1);
    }
    
    return ;
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

    quicksort(g_mem, 0, g_cnt-1);
    print_result();

    end();
    return 0;
}


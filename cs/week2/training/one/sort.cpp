/* ��Ŀ
            ����
*   ����
            ����n�������������Ǵ�С��������������
*   �����ʽ
            ��һ��Ϊһ��������n���ڶ���Ϊn ��������
*   �����ʽ
            ���һ��n����������ʾ������n��������
*   ��������
            5
            5 4 2 3 -1
*   �������
            -1 2 3 4 5
*   ����
            ����ǰ30%�����ݣ�n �� 100��������n�������ľ���ֵ������10��
            ����ǰ60%�����ݣ�n �� 5000��������n�������ľ���ֵ������10^9��
            ������20%�����ݣ�n �� 500000��������n�������ľ���ֵ������10^5��
            ����100%�����ݣ�n �� 500000��������n�������ľ���ֵ������10^9��
            ʱ�䣺2 sec
            �ռ䣺256 MB
*   ��ʾ
            ��ʹ��cin��cout�������������������main ������ĵ�һ��
     ����ios::sync_with_stdio(false)��������ܻᳬʱ��
            �Ƽ�ʹ��scanf ��printf �������������
            ����ʹ�ø��������㷨���в��ԡ�
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

// ��������
// ��4 ����������ʱ���������ڴ�������
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

    // tips: [0, j] �����Ѿ��ź��������
    for (i = 0; i < g_cnt; i++) {
        for (j = i; j-1 >= 0; j--) {
            if (g_mem[j] >= g_mem[j-1]) {
                // ǰ���Ѿ��ź�������ֱ��break
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

// ������
// 10 ���������У�������һ����ʱ140ms
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

    // ��ϸ��������֮�ĸо�
    for (i = g_cnt; i > 0; i--) {
        // ����൱�ڼ��Ĺ���
        // �����ѡ�����򣬶������������Ż����������ֵ�Ĺ��̡�
        // ��ͨ������ȫ�����ҵ������ֵ�����ѡ�����򷴸�������
        // �����ֵ����ʡ�˴���ʱ�䡣
        val = delete_heap_peak();
        g_heap[i] = val;
    }

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
#endif

// �鲢����
// 10 ���������У�������һ����ʱ140ms
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
#endif

// ����<<���ݽṹ���㷨- C ��������>> �еĿ���д��
// 10 ���������У�������һ����ʱ120ms

/* left��right֮��Ŀ�� */
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

/* ���������е��������ᱻչ���������������ʵ����������ǰ���������չ�����ǵ���һ��һ��ĺ����� 
*  ���������������ʹ��gcc -E �ᷢ��Ԥ����֮��ĸú���������һ��ĺ����������ˡ�
*/
static inline void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

/* �������򣬴����������� */
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

/* ������ֵ�����ȡ��ֵ����������ֵ��(right - 1)λ�ô������ݽ�����
*  ������̲�Ҫ�����κ��ⲿ�������̣����˼·���ҡ��ú���ֻҪ
*  ʵ��������˵�Ĺ��ܼ��ɡ�
*/
int getmedian3(int *array, int left, int right)
{
    int center;

    /* ��left, right center���߰���left < center < right��˳������ */
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

    /* ��center��right - 1λ�ô������ݽ��� */
    swap(&array[center], &array[right - 1]);
    
    return array[right - 1];
}

/* tips: �ú����ڲ���û�иı�left��right�����ֵ */
void quicksort(int *array, int left, int right)
{
    int i, j;
    int pivot;    
    
    /* ���ι��̵ġ��֡�����: left + CUTOFF ��Ȼ�ﲻ��right ʱ
       *   �ͽ��С��֡����� 
       */
    if (left + CUTOFF <= right) 
    {
        /* ������̽���ֵ�ŵ�(right - 1)λ�ã����ұ�֤left ��
              *   ��ֵС�ڸ�ֵ��right����ֵ���ڸ�ֵ 
              */
        pivot = getmedian3(array, left, right);
    
        /* ��Ϊright����ֵһ������pivot����������j ��pivot ��λ��
              *   ��ʼ���ɣ�left ����ֵС��pivot��(right - 1)����ֵ���Ǹ�ֵ��
              *   ����ѭ������ֱ��++ ��--
              */
        i = left, j = right - 1;
        for (;;)
        {
            while (array[++i] < pivot) {} /* ���������Ҵ���pivot���� */
            while (array[--j] > pivot) {} /* ����������С��pivot���� */
            if (i < j)
            {
                swap(&array[i], &array[j]);
            }
            else
            {
                break;
            }
        }
        
        /* ��ʱij ���㣬����i λ�ô���������pivot�����Խ���һ�¡�
              *  ����֮��i������pivot����array�ֳ�����, i�����С��pivot��
              *  i����Ĵ���pivot
              */
        swap(&array[i], &array[right - 1]);
        
        /* ���ǡ��֡��ı��ʹ��� 
              *  tips: �ڵݹ�����У�arrayʼ�ն���ԭ��������Ǹ���ַ����
              *  ���Ľ�����ÿ�εݹ鴫���left��right����
              */
        quicksort(array, left, i - 1);
        quicksort(array, i + 1, right);
    }
    else /* �ݹ�Ļ�����������ι��̵ġ��Ρ�����: left + CUTOFF > right��˵��left��right֮����������Ѿ������ˣ���ʱ��Ҫ�١��֡�������Ҫ���Ρ� */
    {
        /* ֱ���ò���������⼸�����ݴ���� */
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


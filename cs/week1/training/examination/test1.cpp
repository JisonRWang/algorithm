/* ��Ŀ
*     �ܲ�1
*  ����
*     ����һ��1��n�����У����δӶ�β���뵽�����У����κ�ʱ���㶼���Ե������׻��β����������Ҫ�Ѷ�����ա�
*     �ʣ����ʹ�ó������е��ֵ�����������������С�
*  ����
*     ����ĵ�һ�а���һ�������� n ��
*     ������1�а��� n ��������һ��1�� n �����С�
*  ���
*     ���1�� n �����������������С�
*  ����1����
*     5
*     1 4 3 5 2
*  ����1���
*     5 3 4 2 1
*  ����1����
*     ���μ���1��4��3��5��2���������������Щ���������У�
*         4 3 2 5 1
*         4 3 5 2 1
*         �ȵȵȣ����ֵ���������
*         5 3 4 2 1
*  ����2
*     ��鿴�·��ļ��ڵ�sample2_input.txt��sample2_output.txt��
*  ����
*     ����30%�����ݣ� n = 200��
*     ����30%�����ݣ� n = 2000��
*     ����20%�����ݣ� n = 2 �� 10^5��
*     ʣ��20%�����ݣ� n = 2 �� 10^6 ��
*     ʱ�䣺2 sec
*     �ռ䣺256 MB
*  �ҵ�˼·
*     �ο� https://www.cnblogs.com/GXZlegend/p/8300939.html
*     ������ֵ��򣬿����Ӧ�þ���̰�ġ���n����������Ӧ��n��λ�ã��������������ֵ��������������ĿҪ��
������£���ÿ��λ�õ������
*     ��0��λ�ÿ϶��������������������Ǹ�������
*     �ܵ�������λ�ð���
*        ����ͷ
*        ����β
*        ʣ��û��ӵ������У���ǰ���Ǹ������Ա������������⣬�൱�ڸ���������ֳ��ӣ�
*     һ����ֻҪ���˶ӣ�Ҫ���ٳ�ȥ����Ҫ�����������ˣ�����ֻ�ܴӶ���ͷ�����β��ȥ������һ��Ҫ��֤�����ǰ
��ʣ���������ҵ������������磬����34125������5�����֮�󣬶�������3412��Ҫ�����4��ֻ���ȰѶ���ͷ3��������
����3��ʱ��3Ҳ�ͱ�����ˣ�����������ӵ���������53421
*     ʣ�������Ҫ���һ���ѣ�����ͷ������β���Ѷ������������Ƚϣ�����Ѷ���������ҶѶ�������һ���������
�������ǾͰ�ʣ�������е���������ӣ�ֱ�����˶Ѷ��Ǹ�����ֱ�������������ָ����򣬼���������̡�
*     �������ͷ�����β�����ֱ��������ɣ�Ȼ�����ͷ������β���Ѷ������Ƚ�
*     ����Ѷ�������Ѷ�����������Ѿ�ȫ����ӣ�����Ѷ����������Ҫ��������һ���ѣ�ѡ���µĶѶ������ɶѶ�
����λ��Ҫ����꣬��Ϊ�����λ�ã����ٲ���Ƚϣ���Ϊû��ʵ�ʵĶ��У�ֻ����ԭʼ������ʹ�ö���ͷβ����ָ����ѣ�
*     ����ͷ�����ߣ�����β�����ߣ����������Ϊ������ĵ�Ҫ����ȥ
*     ������뷨�ܵ�û������ÿ�ζ�����һ�ζѻ�ǳ���ʱ���ο������process_new()������̣�ֻ��Ҫ��һ�ζѣ�
��ʹ�ò��뷨���ѹ����У�ÿ����һ�����ݣ�������εĶѶ���¼�����������Ǵ�����β����ʼ��ǰͨ�����뷨�����ѵģ�
��˵���ǰ����ʼ��ӳ��Ӵ�������ʱ���ܹ�֪����ÿ��δ��ӵ����ݿ�ʼ��������ֵ��˭�����ֲ������˶��
�ظ��������ֵ�����⡣
*     ���
*        ����ⲻ��ο��������Ǹ���˵������ˮ���������������ԡ�
*     ����
*        ����ʽ���ѵķ���Ҳ�����õģ�����֪��ÿ�����ݴ���ļ�ʱ��ֵ
*        ��ǰ���󽨶ѣ�����֪���ӵ�ǰ����ʼ����ǰ���е�����������
*        �Ӻ���ǰ���ѣ�����֪���ӵ�ǰ����ʼ���������е�����������
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

// ��Ӧλ�õ����Ѿ�������ı��
#define MIN     -1

// ���������ܸ���
static int  g_cnt;

// �洢������������
static int* g_mem;

// ��0��Ԫ�ؼ�¼���нڵ�����
static int* g_heap;

// ����¼�����У�����ÿ����ʱ���Ӹ�����������ֵ���ڴ�����
static int* g_table;

// ����
static int* g_queue;
static int g_queue_head;
static int g_queue_tail;

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

// ����ѣ����Ϊg_mem�е�����
static void create_heap(int start_idx)
{
    int i, j, child, heap_size;

    // ����Ҫʹ�öѵ����ݿ�������
    for (i = start_idx; i <= g_cnt; i++) {
        // g_heap��1��ʼ
        g_heap[i - start_idx + 1] = i;
    }
    g_heap[0] = g_cnt - start_idx + 1;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_mem[g_heap[child]] <= g_mem[g_heap[child + 1]]) {
                child++;
            }
            if (g_mem[g_heap[j]] >= g_mem[g_heap[child]]) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

// ���������ƿ�֪��n��С����200�����Բ��ÿ���nС��3�ı߽����
// ���ַ�ʽ���ѣ�������54321���ֵ������У�����кܳ�����ǳ���ʱ
static void process()
{
    int i;
    int output_cnt = 0;
    bool tag_update_heap;
    int peak_idx, start_idx, queue_idx;

    start_idx = 1;
    tag_update_heap = true;
    while (output_cnt < g_cnt) {
        queue_idx = g_queue_tail;

        // TODO����ط������⣬���е�����������
        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail]) {
            queue_idx = g_queue_head;
        }

        if (start_idx <= g_cnt) {
            if (tag_update_heap) {
                create_heap(start_idx);
            }
            peak_idx = g_heap[1];
            if (g_queue[queue_idx] < g_mem[peak_idx]) {
                // peak_idx��ߵ�����ȫ�����
                for (i = start_idx; i < peak_idx; i++) {
                    g_queue[++g_queue_tail] = g_mem[i];
                }

                printf("%d", g_mem[peak_idx]);
                output_cnt++;
                if (output_cnt < g_cnt) { printf(" "); }

                start_idx = peak_idx + 1;
                tag_update_heap = true;

                continue;
            }
            tag_update_heap = false;
        }

        // �������ݺ���g_queue[x] = MIN���Ϳ�����g_queue_head == g_queue_tailʱ���������
        // �̲��ᵼ�� g_queue_head < g_queue_tail
        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail]) {
            printf("%d", g_queue[g_queue_head + 1]);
            output_cnt++;
            g_queue[g_queue_head + 1] = MIN;
            g_queue_head++;
        }
        else {
            printf("%d", g_queue[g_queue_tail]);
            output_cnt++;
            g_queue[g_queue_tail] = MIN;
            g_queue_tail--;
        }
        if (g_queue_head == g_queue_tail) {
            g_queue_head = 0;
            g_queue_tail = 0;
        }
        if (output_cnt < g_cnt) {
            printf(" ");
        }
    }

    return;
}

// �����
static void insert_heap(int mem_idx)
{
    int i, dad, heap_size;

    heap_size = g_heap[0];
    g_heap[++heap_size] = mem_idx;
    g_heap[0] = heap_size;

    // ����
    for (i = heap_size; i > 1; i = dad) {
        dad = i >> 1;

        if (g_mem[g_heap[i]] <= g_mem[g_heap[dad]]) {
            break;
        }
        swap_heap(dad, i);
    }

    return;
}

/* ���������е�ĩβ��ʼ�����ò���ķ�ʽ���ѣ�����¼ÿ������Ӧ�ĶѶ���������������һ����ʱ��
*  �ӵ�һ���������ÿһ������Ӧ�ĸ��Ժ�������ֵ�Ͷ����ˡ����������ֵ��ʱ�򣬿���ֱ�Ӳ��
*  ���������κε�������صĲ�����ΪʲôҪ��ĩβ��ʼ���ò���ķ�ʽ���ѣ���Ϊ������������ʱ��
*  �����������δ���ģ�ÿ����һ��������Ҫ֪����������ҵ����ֵ�Ƕ��٣����������ǰ������룬
*  �Ǿ�ֻ��֪�������֮ǰ������������ֵ�����Ա���Ӻ���ǰ���룬��������֪�����������ʼ����
*  �����ֵ��ʲô��
*/
static void record_max_value()
{
    int i;

    g_heap[0] = 0;
    for (i = g_cnt; i >= 1; i--) {
        insert_heap(i);
        g_table[i] = g_heap[1];
    }

    return;
}

static void process_new()
{
    int i;
    int out_cnt;
    int start_idx, queue_idx;

    record_max_value();

    out_cnt = 0;
    start_idx = 1;
    while (out_cnt < g_cnt) {
        queue_idx = 0;
        if (g_queue_head + 1 < g_queue_tail) { // ���в�Ϊ��
            queue_idx = g_queue_tail - 1;
            if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail - 1]) {
                queue_idx = g_queue_head + 1;
            }
        }

        if (start_idx <= g_cnt &&
            g_queue[queue_idx] < g_mem[g_table[start_idx]]) {
            // g_table[start_idx]���������ȫ�����
            for (i = start_idx; i < g_table[start_idx]; i++) {
                g_queue[g_queue_tail++] = g_mem[i];
            }
            printf("%d", g_mem[g_table[start_idx]]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }

            start_idx = g_table[start_idx] + 1;

            continue;
        }

        if (g_queue[g_queue_head + 1] > g_queue[g_queue_tail - 1]) {
            printf("%d", g_queue[g_queue_head + 1]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }
            g_queue[g_queue_head + 1] = MIN;
            g_queue_head++;
        }
        else {
            printf("%d", g_queue[g_queue_tail - 1]);
            if (++out_cnt != g_cnt) {
                printf(" ");
            }
            g_queue[g_queue_tail - 1] = MIN;
            g_queue_tail--;
        }
    }

    return;
}

static void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    // ��1��ʼ
    g_mem = new int[g_cnt + 1];
    g_heap = new int[g_cnt + 1];
    g_queue = new int[g_cnt + 2]; // ��0�������һ�����ǲ��涫����
    g_table = new int[g_cnt + 1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }

    // �������д�1��ʼ
    // g_queue_head + 1��ʵ�ʵĶ���ͷԪ��
    // g_queue_tail - 1��ʵ�ʵĶ���βԪ��
    // g_queue_head + 1 == g_queue_tail����ʾ���п�
    g_queue_head = 0;
    g_queue_tail = 1;
    g_queue[g_queue_head] = MIN;
    g_queue[g_queue_tail] = MIN;

    return;
}

static void end()
{
    delete[] g_mem;
    delete[] g_heap;
    delete[] g_queue;

    return;
}

void test1()
{
    init();

    //process();
    process_new();

    end();

    return;
}
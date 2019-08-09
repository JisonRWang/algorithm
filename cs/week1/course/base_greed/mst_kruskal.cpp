/* MST kruskal�㷨ʵ��
*     �����
*     ���鼯
*  Ҫ���ܹ��жϳ������ı��Ƿ���������ͨͼ
*  δ���Ľ�
*     ʹ��쳲�������ѡ��
*  ����
*     N  ��ʾ�ж�������
*     45 0 1    Ȩ�� ����� �����
*     ...��һ��N�б�ʾ����ıߵ�Ȩ���Լ���ɱߵĵ����ţ�
*  ����ŷ�Χ�� [0, 2*N)
*  ע��
*     ��������ݲ���֤һ������ͨͼ��������Ҫ�Լ������Ƿ���ͨ
*     ����ֻ��������Щ�ߣ�ûֱ�Ӹ�������Щ�㣬��ͬ�ı߿����в��ֵ����ظ���
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct point
{
    int rank;       // �ȣ����ڲ��鼯
    int dad_index;  // ���ڵ��ڴ�������Ҳ�Ǹ��ڵ�ĵ���ţ����ڲ��鼯 
}point_s;

typedef struct edge
{
    int pa_index;  // �ñ������ӵ���������ڴ�������Ҳ�ǵ�ĵ����
    int pb_index;
    int weight;    // �ߵ�Ȩ��
    bool chose;    // �Ƿ�ѡ����Ϊmst��һ����
}edge_s;

static int g_edge_cnt;
static int g_point_max_cnt; // �����ߵ�����£���ӵ�е�����ĸ���Ϊ��g_point_max_cnt = 2 * g_edge_cnt
static edge_s* g_edge_mem;
static point_s* g_point_mem;

// g_heap[0]��¼���нڵ�����
static int* g_heap;

static int find_set(int point_idx)
{
    // �ݹ��
    if (-1 == g_point_mem[point_idx].dad_index) {
        return point_idx;
    }

    // ·��ѹ��
    g_point_mem[point_idx].dad_index = find_set(g_point_mem[point_idx].dad_index);
    return g_point_mem[point_idx].dad_index;
}

static void set_union(int seta_root_idx, int setb_root_idx)
{
    if (g_point_mem[setb_root_idx].rank < g_point_mem[seta_root_idx].rank) {
        g_point_mem[setb_root_idx].dad_index = seta_root_idx;
        return;
    }

    g_point_mem[seta_root_idx].dad_index = setb_root_idx;
    if (g_point_mem[seta_root_idx].rank == g_point_mem[setb_root_idx].rank) {
        g_point_mem[setb_root_idx].rank++;
    }

    return;
}

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp_mem_idx;

    tmp_mem_idx = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp_mem_idx;

    return;
}

// С���ѣ����رߵ��ڴ�����
static int delete_heap_peak()
{
    int i, child, peak, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    // ����
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child+1]].weight) {
            child++;
        }
        if (g_edge_mem[g_heap[i]].weight <= g_edge_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// С���ѣ���С��������
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child+1]].weight) {
                child++;
            }
            if (g_edge_mem[g_heap[j]].weight <= g_edge_mem[g_heap[child]].weight) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

// Ҫ���Ƿ���ͨͼ�����
static void create_mst()
{
    int i;
    int tmp_edge_idx;
    int seta_rt_idx, setb_rt_idx;
    int point_cnt, accepted_edge_cnt;

    // ͳ�Ƶ�ǰ����ͼ����ӵ�еĵ�ĸ���
    point_cnt = 0;
    for (i = 0; i < g_point_max_cnt; i++) {
        if (-2 != g_point_mem[i].dad_index) {
            point_cnt++;
        }
    }

    accepted_edge_cnt = 0;

    // ��С�������ı�����ͼ�����е�ĸ�����Ӧ��ʽ�� edge_cnt = point_cnt - 1
    while (accepted_edge_cnt < point_cnt - 1) {
        tmp_edge_idx = delete_heap_peak();
        if (-1 == tmp_edge_idx) {
            break;
        }

        seta_rt_idx = find_set(g_edge_mem[tmp_edge_idx].pa_index);
        setb_rt_idx = find_set(g_edge_mem[tmp_edge_idx].pb_index);

        if (seta_rt_idx != setb_rt_idx) {
            set_union(seta_rt_idx, setb_rt_idx);
            g_edge_mem[tmp_edge_idx].chose = true;
            accepted_edge_cnt++;
        }
    }

    // ����ͨͼ
    if (accepted_edge_cnt < point_cnt - 1) {
        printf("����ͨͼ���޷���ȡ��С������\n");
        return;
    }

    // ��ͨͼ�����Ҽ��������С������
    for (i = 0; i < g_edge_cnt; i++) {
        if (!g_edge_mem[i].chose) {
            continue;
        }
        printf("edge: %d, pa: %d, pb: %d, weight: %d\n", 
            i, g_edge_mem[i].pa_index, g_edge_mem[i].pb_index, g_edge_mem[i].weight);
    }

    return;
}

static void init()
{
    int i;

    scanf("%d", &g_edge_cnt);
    getchar();

    g_edge_mem = new edge_s[g_edge_cnt];
    g_heap = new int[g_edge_cnt + 1];

    g_point_max_cnt = 2 * g_edge_cnt;
    g_point_mem = new point_s[g_point_max_cnt];
    for (i = 0; i < g_point_max_cnt; i++) {
        g_point_mem[i].dad_index = -2;
    }

    g_heap[0] = g_edge_cnt;
    for (i = 0; i < g_edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].weight, &g_edge_mem[i].pa_index, &g_edge_mem[i].pb_index);
        getchar();
        g_edge_mem[i].chose = false;

        // g_heap[0]��¼�����ܽڵ��������������λ�ü�¼����ÿ�������ڴ��е�����
        // ���ѭ���е�i��0��ʼ��������Ԫ�ش�1��ʼ
        g_heap[i + 1] = i;

        g_point_mem[g_edge_mem[i].pa_index].rank = 0;
        g_point_mem[g_edge_mem[i].pa_index].dad_index = -1;
        
        g_point_mem[g_edge_mem[i].pb_index].rank = 0;
        g_point_mem[g_edge_mem[i].pb_index].dad_index = -1;
    }

    return;
}

static void end()
{
    delete[] g_edge_mem;
    delete[] g_heap;
    delete[] g_point_mem;

    return;
}

void mst_kruskal()
{
    init();

    create_heap();
    create_mst();

    end();

    return;
}
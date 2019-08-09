/* MST prim�㷨ʵ��
*    prim�㷨��Ч�ʲ���kruskal�㷨
*    ����������ա��㷨���ۡ��н���
*    ����������ʹ�öѵķ�ʽ��ͬ��prim��ʹ�ö�ʱ��ÿ��ִ��deletePeak����֮ǰ��Ҫ���»ָ�һ�¶�����Ϊ
ÿ�θ��¿�߶���Ӱ�����еĶ���ṹ
*    �裬����������ʱ�������ڵļ���ΪA
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

#define INFINITY 0x7fffffff

typedef struct edge
{
    int weight;
    int pa_idx;
    int pb_idx;
}edge_s;

typedef struct point
{
    bool in_heap;   // ��¼��ǰ���Ƿ��ڶ���
    int  weight;    // ��¼�õ㣨�ڶ��У��뼯��A�еĵ���ɵĿ���У�Ȩ����С�Ŀ�ߵ�Ȩ��
    int  dad_idx;   // ����õ����Ȩ����С�Ŀ�ߵĵ���ڴ��������������A��
}point_s;

// ͳ�Ƶ�ǰͼ�е�ĸ�������������û��ֱ�Ӹ��ߵ�ĸ�����������Ҫ�Լ������ж��ٸ���
static int g_point_cnt;

// һά���鵱��ά����ʹ�ã���¼������֮����ڽӹ�ϵ��Ԫ��ֵΪ�ߵ�Ȩ��
static int* g_point_rel;

// �洢��������ڴ�
static point_s* g_point_mem;

// С���ѣ���¼���������ڴ��е���������0��Ԫ�ؼ�¼���нڵ����
static int* g_heap;

static void swap_heap(int heap_dad_idx, int heap_child_idx) 
{
    int tmp_mem_idx;

    tmp_mem_idx = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp_mem_idx;

    return;
}

// С����
static void recover_heap_order()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = (heap_size >> 1); i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_point_mem[g_heap[child]].weight >= g_point_mem[g_heap[child + 1]].weight) {
                child++;
            }
            if (g_point_mem[g_heap[j]].weight <= g_point_mem[g_heap[child]].weight) {
                break;
            }
            swap_heap(j, child);
        }
    }

    return;
}

static int delete_heap_peak()
{
    int peak;
    int i, child, heap_size;

    // ���нڵ�����ݻᱻ�޸ģ����ÿ��delete_peak֮ǰ���������»ָ�����
    recover_heap_order();

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;
    g_point_mem[peak].in_heap = false;

    // ���ˣ�С���ѣ�
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_point_mem[g_heap[child]].weight >= g_point_mem[g_heap[child + 1]].weight) {
            child++;
        }
        if (g_point_mem[g_heap[i]].weight <= g_point_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// By prim
static void create_mst()
{
    int i, offset;
    int tmp_mem_idx;
    int tmp_heap_idx;

    // ͵�������Ӷ���ȡ���ĵ������ηŵ��������ĩβ���Ա���������g_heap[0]��ʱ����g_point_cnt
    tmp_heap_idx = g_heap[0]; 

    // ���ѡȡһ������Ϊ��ʼ
    tmp_mem_idx = g_heap[1];
    g_point_mem[tmp_mem_idx].weight = 0;

    // ���д�������е�
    while (g_heap[0] > 0) {
        tmp_mem_idx = delete_heap_peak();

        // �ж��Ƿ�Ϊ��ͨͼ
        // ÿ�δӶ���ȡ��һ����֮�󣬶�����¶�����������뼯��A�γɿ�ߵĵ����СȨ�ء������������ͨͼ��
        // ��ô���п϶�Ҫ�е��Ȩ�ز�Ϊ�������������˴Ӷ���ȡ���ĵ��Ȩ��Ϊ����󣬾�˵���������A��
        // �κ�һ���㶼û�б����ӣ�������ͨ������޷�������С������
        if (INFINITY == g_point_mem[tmp_mem_idx].weight) {
            printf("����ͨͼ\n");
            return;
        }

        g_heap[tmp_heap_idx--] = tmp_mem_idx;

        // �Ӷ���ȡ��һ������뵽A�󣬸��¶�����õ����ڵ����СȨ��
        offset = tmp_mem_idx * g_point_cnt;
        for (i = 0; i < g_point_cnt; i++) {
            // ����tmp_mem_idx���б����������ڶ��еĵ�
            // tips: ֻ�ж��еĵ������A�еĵ��γɿ�ߣ��������A�еĵ㣬��ɻ�
            if (0 == g_point_rel[offset + i] ||
                false == g_point_mem[i].in_heap) {
                continue;
            }

            // �ڶ����ҵ����ʵĵ㣬���¸õ���A�Ŀ�ߵ���СȨ��
            if (g_point_mem[i].weight > g_point_rel[offset + i]) {
                g_point_mem[i].weight = g_point_rel[offset + i];
                g_point_mem[i].dad_idx = tmp_mem_idx;
            }
        }
    }

    // ���
    for (i = g_point_cnt; i > 0; i--) {
        // ��ʼ��û��Ȩ��Ҳû�и��ڵ㣬û��Ҫ���
        if (-1 == g_point_mem[g_heap[i]].dad_idx) {
            continue;
        }
        printf("weight: %d, pa: %d, pb: %d\n", 
            g_point_mem[g_heap[i]].weight, g_heap[i], g_point_mem[g_heap[i]].dad_idx);
    }

    return;
}

// ͳ�Ƶ�ĸ���
static int count_points(edge_s* edge_arr, int edge_cnt)
{
    int* point_arr;
    int i, point_cnt, tmp_cnt;

    tmp_cnt = edge_cnt << 1;
    point_arr = new int[tmp_cnt];
    for (i = 0; i < tmp_cnt; i++) {
        point_arr[i] = 0;
    }

    for (i = 0; i < edge_cnt; i++) {
        point_arr[edge_arr[i].pa_idx]++;
        point_arr[edge_arr[i].pb_idx]++;
    }

    point_cnt = 0;
    for (i = 0; i < tmp_cnt; i++) {
        if (0 == point_arr[i]) {
            continue;
        }
        point_cnt++;
    }

    delete[] point_arr;

    return point_cnt;
}

static void init()
{
    int tmp;
    edge_s* edge_arr;
    int i, edge_cnt, tmp_pa, tmp_pb;

    scanf("%d", &edge_cnt);
    getchar();

    edge_arr = new edge_s[edge_cnt];
    for (i = 0; i < edge_cnt; i++) {
        scanf("%d %d %d", &edge_arr[i].weight, &edge_arr[i].pa_idx, &edge_arr[i].pb_idx);
        getchar();
    }

    g_point_cnt = count_points(edge_arr, edge_cnt);

    tmp = g_point_cnt * g_point_cnt;
    g_point_rel = new int[tmp];
    for (i = 0; i < tmp; i++) {
        g_point_rel[i] = 0;
    }
    for (i = 0; i < edge_cnt; i++) {
        tmp_pa = edge_arr[i].pa_idx;
        tmp_pb = edge_arr[i].pb_idx;

        // ����ͼ����Ҫ˫������
        g_point_rel[tmp_pa * g_point_cnt + tmp_pb] = edge_arr[i].weight;
        g_point_rel[tmp_pb * g_point_cnt + tmp_pa] = edge_arr[i].weight;
    }

    g_heap = new int[g_point_cnt + 1];
    g_point_mem = new point_s[g_point_cnt];
    for (i = 0; i < g_point_cnt; i++) {
        g_heap[i + 1] = i;

        g_point_mem[i].in_heap = true;        // ��ʼ״ֱ̬���ڶ���
        g_point_mem[i].weight = INFINITY;     // �൱�������
        g_point_mem[i].dad_idx = -1;          // û�и��ڵ㣨A��û�п�����ýڵ������СȨ�ؿ�ߵĽڵ㣩
    }
    g_heap[0] = g_point_cnt;

    delete[] edge_arr;

    return;
}

static void end()
{
    delete[] g_point_rel;
    delete[] g_point_mem;
    delete[] g_heap;

    return;
}

void mst_prim()
{
    init();

    create_mst();

    end();

    return;
}
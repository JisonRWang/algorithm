/* ��Ŀ
*     ��·����
*  ����
*     Z���� n �����к� m ��˫���·��ÿ����·������������ͬ�ĳ��У���֤���г���֮�䶼����
ͨ����Щ��·���ÿ����·����һ�����������ƣ���������ͨ��������·�Ļ�����������������·
�ı�Ŵ� 1 �� m ���ɺϵ��ǣ����е�·������������ǡ�ö���������ͬ��
*     ���ڣ�Ҫ��ѡ����������·�������������ɸ��ٹ�·������������Ҫ��
*        ���г���֮�䶼����ͨ�����ٹ�·���
*        ���������������� u,v ���㹻�����Ļ���˾����ֻ���������ٹ�·���� u ���� v �ܹ�װ�ػ���
������������뾭���������·���� u ���� v �ܹ�װ�ػ���ġ����������ȡ����㹻������˾��ֻ��ע����
��������������·��
*     �������ǰ���£�Ҫ��ѡ���ĵ�·��Ŀ�������١�
*     ����Ҫ��ѡ����Щ��·�����ɸ��ٹ�·������ж��ַ������������һ�֣���
*  ����
*     ��һ�� 2 ���ÿո���������� n,m ���ֱ��ʾ������Ŀ����·��Ŀ��
*     �� 2 �е��� m+1 �У�ÿ�� 2 ���ÿո���������� u,v ����һ���� u �� v ��˫���·���� i+1 �еĵ�·�ı��Ϊ i ��
*     ע��
*        ����ֻ��֤���������ӵĳ�����ͬ�ĵ�·���Ի�����������֤������������ȫ��ͬ�ıߣ��رߣ�
*  ���
*     ��һ��һ������ k ����ʾ�����ɸ��ٹ�·�ĵ�·����
*     ������ k ��ÿ��һ����������С�����������ѡ���ĵ�·�ı�š�
*  ��������
*     3 3
*     1 2
*     2 3
*     1 3
*  �������
*     2
*     2
*     3
*  ���ݷ�Χ
*     ���� 20% �����ݣ���֤ n��5��m��10��
*     ���� 60% �����ݣ���֤ n��1,000��m��5,000��
*     ���� 100% �����ݣ���֤ n��200,000��m��400,000��
*     ʱ�����ƣ�10 sec
*     �ռ����ƣ�256 MB
*  ��ʾ
*     [��ʾ1����Ŀ����ж��ַ�����]
*     [��ʾ2��k �Ƿ�һ��Ϊ n-1 �أ���Ҳ����˵��ѡ���ĵ�·�Ƿ�ǡ�ù�����һ��������]
*     [��ʾ3����������С��������ʲô��ϵ�أ�]
*  �ҵ�����
*     �Ի�����һ�����г�����������һ������Ȼ���ֻص��������У������ر���ʲô��˼��
*     �ڶ���Ҫ����ʲô��˼����˵��ʲô���ҵ�����ǣ����ȣ���·�������ɸ��ٹ�·ǰ���
�������ǲ���ģ�����uv֮����ֱ��ͨ·����·����ֱ��ͨ·��������С����·����ô�Ͳ��ܽ�����ֱ��ͨ·����Ϊ���ٹ�·��
��Ӧ�ý�uv�����������;�ĵ�·������Ϊ���ٹ�·��������ĿҪ��Ӧ�ó���Ϊ��ѡ��������������֮���ܹ�������������
�ĵ�·����ʱ���ɵ�����������С�������ķ��棬��������������������������ĵ�·Ҫ�����ɸ��ٹ�·����
*     ���������ܷ�֤һ�����㹻�����ı���ͨ�������У����Ƿ�����û��һ��·��ͨĳ�����е����������Ŀ������Ӧ
�ò�������������롣
*  �ҵ�˼·
*     uv֮���·��;��Ȼÿ��·����������أ���������ʵ������������·���ϵ���С���ؾ�����
*     �����о��������Ҫ��֤ÿ������֮�䶼����ͨ�����ٹ�·����Ǿ�˵��һ��Ҫ�ɸ��ٹ�·��ͨ���е���Щ���У�
���ܹ���������ֻ������������������Ϊ��ѡ���ĵ�·һ���ṹ��һ����������
*     ������Ѿ�˵���ˣ�����ͨͼ������һ����������
*     ÿ���ߵ�Ȩ�ض���ͬ�����Կ϶�ֻ��һ�ַ���
*     �������������
*     ֱ����kruskal�㷨���������������
*     n���㣬m���ߣ���֤����ͨͼ����������Լ�������Ҫ��
*        ����һ���ڴ棬�����еı�
*        ����һ���ڴ棬�����еĵ�
*        ����һ���ڴ棬��Ϊ�ѣ����д��
*        ʹ�ò��鼯���鿴���Ƿ���ͬһ������
*        ʹ�ô���ѣ������ĺ���ı߷ŵ���ĩβ
*        ��һ��������¼���������ıߵ�����
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct point
{
    int dad_idx;
    int rank;
}point_s;

// �ߵ�Ȩ�ؾ��Ǳ����ڴ��е�����
typedef struct edge
{
    int pa_idx;   // �����ڴ��е�����
    int pb_idx;
}edge_s;

static point_s* g_point_mem;
static edge_s* g_edge_mem;
static int* g_heap; // ��0��Ԫ�ؼ�¼���нڵ����

static int g_edge_cnt;
static int g_point_cnt;

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

//TODO �������ջ�������
static int set_find(int point_idx)
{
    // �ݹ��
    if (point_idx == g_point_mem[point_idx].dad_idx) {
        return point_idx;
    }

    g_point_mem[point_idx].dad_idx = set_find(g_point_mem[point_idx].dad_idx);
    return g_point_mem[point_idx].dad_idx;
}

// ���Ⱥϲ�
static void set_union(int set_root_a, int set_root_b)
{
    if (g_point_mem[set_root_a].rank < g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_a].dad_idx = set_root_b;
        return;
    }

    g_point_mem[set_root_b].dad_idx = set_root_a;
    if (g_point_mem[set_root_a].rank == g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_a].rank++;
    }

    return;
}

// �����
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

    // ���ˣ�����ѣ�
    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_heap[child] <= g_heap[child + 1]) {
            child++;
        }
        if (g_heap[i] >= g_heap[child]) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// �����������������Ŀ�Ѿ���֤����ͨͼ
static void create_mbt()
{
    int i, heap_idx;
    int ac_edge_cnt;
    int edge_mem_idx;
    int root_a, root_b;

    // ͵���������ñ����ηŵ��������ڴ��ĩβ�����ı������
    heap_idx = g_edge_cnt;

    ac_edge_cnt = 0;
    while (ac_edge_cnt < g_point_cnt - 1) {
        // ��ͨͼ���϶���֧���������Բ����ж�edge_mem_idx�Ƿ�Ϊ-1
        edge_mem_idx = delete_heap_peak();
        root_a = set_find(g_edge_mem[edge_mem_idx].pa_idx);
        root_b = set_find(g_edge_mem[edge_mem_idx].pb_idx);

        if (root_a == root_b) {
            continue;
        }
        set_union(root_a, root_b);
        ac_edge_cnt++;
        g_heap[heap_idx--] = edge_mem_idx;
    }

    // ���
    printf("%d\n", ac_edge_cnt);
    for (i = heap_idx + 1; i <= g_edge_cnt; i++) {
        printf("%d\n", g_heap[i]);
    }

    return;
}

// �����
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            // �ߵ�Ȩ�ؾ��Ǳ����ڴ��е�������g_heap��ľ��Ǳߵ�����������ֱ�ӱȾͺ�
            if (child < heap_size &&
                g_heap[child] <= g_heap[child + 1]) {
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

static void init()
{
    int i;

    scanf("%d %d", &g_point_cnt, &g_edge_cnt);
    getchar();

    g_point_mem = new point_s[g_point_cnt + 1]; // �����п����������Ŵӵ�1����ʼ��
    g_edge_mem = new edge_s[g_edge_cnt + 1];    // �����п������ߵ���Ŵӵ�1����ʼ��
    g_heap = new int[g_edge_cnt + 1];

    for (i = 0; i <= g_point_cnt; i++) {
        g_point_mem[i].dad_idx = i;
        g_point_mem[i].rank = 0;
    }

    g_heap[0] = g_edge_cnt;
    for (i = 1; i <= g_edge_cnt; i++) {
        scanf("%d %d", &g_edge_mem[i].pa_idx, &g_edge_mem[i].pb_idx);
        getchar();
        g_heap[i] = i;
    }

    return;
}

static void end()
{
    delete[] g_point_mem;
    delete[] g_edge_mem;
    delete[] g_heap;

    return;
}

void road_upgrade()
{
    init();

    create_heap();
    create_mbt();

    end();

    return;
}
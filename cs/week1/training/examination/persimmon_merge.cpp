/* ��Ŀ
*      ���Ӻϲ�
*   ����
*      �ֵ��˳������ļ��ڡ�С��Ĺ�԰����n�������������Ϊ1��n���ʼ����Щ������֮�䶼û�е�·������
С�����ڹ滮���� m ���м�����޽�˫���·������������ m  ����Ԫ��(u,v,w) ��ʾ����ʾ�ڱ��Ϊu �� ���Ϊv
��������֮���޽���·��Ҫ���� w Ԫ��
*      С������������·�󣬽��ܹ�ֱ�ӻ���ͨ����·���ӵ�����������Ϊһ���Ӽ������ң����ڻ��ֳ���ÿһ��
�Ӽ���������Ӽ��е������������ϳ�������������һ��������
*      С������һ����Ҫ�õ� k ���������������������С����·�����Ƕ��١�
*   ����
*      �� 1 ������������ n ��m ��k ���������Ŀ������
*      ������ m �У�ÿ����������u ��v ��w ������ÿ�������޽��ĵ�·����������������
*   ���
*      ���һ��һ����������ʾС����·����С���ѡ�
*      ���С��������ζ��������� k ��������������6�11 ��
*   ��������1
*      4 4 2
*      1 2 3
*      2 3 1
*      4 2 1
*      3 4 2
*   �������1
*      2
*   ����1����
*      �� 2��3 �� 2��4 ֮���޽���·��
*      �������ǾͿ��Խ��������������� 2 ��������
*   ����
*      ����30%�����ݣ�1��n��100,1��m��1000��
*      ����100%�����ݣ�1��n��10000,1��m��100000,1��k��10,1��u,v��n,0��w��10000��
*   ��ʾ
*      [��΢��һ��kruskal�㷨������]
*   �ҵ�˼·
*      ��Ŀ����
*          ��n���㣬���1~n���滮��m���ߣ�ÿ��������Ԫ��(u,v,w)��ʾ��uv�ǵ��ţ�w�Ǳߵ�Ȩ�ء�
*          û˵�ǲ�����ͨͼ��Ҫ���Ƿ���ͨ�����
*              ���Ҫ1������������һ����û���κα����ӣ��Ǵ�ʱ��Ӧ�����-1
*          n���㣬m���ߣ�����Ϊk�����ϣ�ÿ�����϶���һ����С��������k�����ϻ���֮�䲻�ܺϲ�
*          ��������k������Ȩֵ֮��
*      �������Ϻϲ��������һ�����ϣ�����һ�����ϣ���ÿ���������Ϻϲ������ϸ�������һ
*      �ʼ��ʱ��n���㣬����nƬɭ�֣�ÿƬɭ����ֻ��һ������һƬɭ�־���һ������
*      ͨ����·���ӵĲ�ͬ����������һƬɭ��
*      k > n������ÿƬɭ��ֻ��һ������Ҳ�޷�����kƬɭ�֣���ʱ����-1
*      k == n��ÿƬɭ��ֻ��һ������ǡ�ù��������kƬɭ�֣�����Ҫ�κε�·���ӣ���ʱ����0
*      k < n����ʱ���п��ܷ���-1������k=1������ȫ��ͨͼ���򷵻�-1
*            ��Ȼ����kruskal�㷨�ķ�ʽȥ�ϲ���ֻ����ÿ�κϲ���ͳ��һ�µ�ǰ�ļ��ϸ�������ɭ�ָ�������
�������k���������ɭ�ֵ�Ȩ�ؼ�Ϊ�𰸡�
*      ��ʵ������ʱ�򣬿��԰���Ƭɭ�ֿ�����һ������ɵ�ɭ�֣�����������еĿ�߶���Ϊ��һ�����Ŀ�ߣ�
����뷨��prim�㷨�к���Ч��������kruskal�㷨�в���ȫ���ã���Ϊkruskal�㷨Ҫ���ǳɻ������⣬�Ǿͱ���
����ɭ�������е��ˡ�
*            ��Ϊÿ�κϲ��������ϣ��������һ�����ϣ����Ե�k<nʱ��ͨ���𲽺ϲ��������ϣ���ÿ�μ���һ��
������ʹ�ܼ��ϸ��������������յ���k����ȻҪ���������м��ϵ�Ȩ�ؼ������ܺ���С��Ҳ����ζ��ÿ�κϲ�����
���ϵ�ʱ���������������ϵı���С���������ܱ�֤�ڼ����ܼ��ϸ�����ͬʱ�������ڲ���Ȩ����С��
*      ������˵��������Ȼ��ʵ��kruskal�㷨��ֻ����ÿ�κϲ����ϣ���Ҫͳ�Ƶ�ǰ�ܼ��ϸ�����
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct point
{
    int rank;
    int dad_idx;
}point_s;

typedef struct edge
{
    int pa;
    int pb;
    int weight;
}edge_s;

// �ܼ��ϸ�������ʼֵΪȫ���ĵ�ĸ�������Ϊ��ʼʱÿ���������һ�����ϣ�ɭ�֣�
static int g_set_cnt;

// �����ڴ��е���Ŵ�1��ʼ
static point_s* g_point_mem;

// �����ڴ��е���Ŵ�1��ʼ
static edge_s* g_edge_mem;

// ��0��Ԫ�ؼ�¼�����ܽڵ����
static int* g_heap;

static int g_k;

static void flush_input_data(int edge_cnt)
{
    int i, tmp_a, tmp_b, tmp_c;

    for (i = 0; i < edge_cnt; i++) {
        scanf("%d %d %d", &tmp_a, &tmp_b, &tmp_c);
        getchar();
    }

    return;
}

static void swap_heap(int heap_dad_idx, int heap_child_idx)
{
    int tmp;

    tmp = g_heap[heap_child_idx];
    g_heap[heap_child_idx] = g_heap[heap_dad_idx];
    g_heap[heap_dad_idx] = tmp;

    return;
}

static int set_find(int point_idx)
{
    // �ݹ��
    if (point_idx == g_point_mem[point_idx].dad_idx) {
        return point_idx;
    }

    g_point_mem[point_idx].dad_idx = set_find(g_point_mem[point_idx].dad_idx);
    return g_point_mem[point_idx].dad_idx;
}

static void set_union(int set_root_a, int set_root_b)
{
    if (g_point_mem[set_root_a].rank > g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_b].dad_idx = set_root_a;
        return;
    }

    g_point_mem[set_root_a].dad_idx = set_root_b;
    if (g_point_mem[set_root_a].rank == g_point_mem[set_root_b].rank) {
        g_point_mem[set_root_b].rank++;
    }

    return;
}

// С����
static int delete_heap_peak()
{
    int i, peak, child, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_heap[1] = g_heap[heap_size--];
    g_heap[0] = heap_size;

    for (i = 1; (i << 1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child + 1]].weight) {
            child++;
        }
        if (g_edge_mem[g_heap[i]].weight <= g_edge_mem[g_heap[child]].weight) {
            break;
        }
        swap_heap(i, child);
    }

    return peak;
}

// С����
static void create_heap()
{
    int i, j, child, heap_size;

    heap_size = g_heap[0];
    for (i = heap_size >> 1; i >= 1; i--) {
        for (j = i; (j << 1) <= heap_size; j = child) {
            child = j << 1;

            if (child < heap_size &&
                g_edge_mem[g_heap[child]].weight >= g_edge_mem[g_heap[child + 1]].weight) {
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

static void process()
{
    int set_cnt;
    int edge_idx;
    int sum_weight;
    int root_a, root_b;

    sum_weight = 0;
    set_cnt = g_set_cnt;
    while (set_cnt > g_k) {
        edge_idx = delete_heap_peak();
        if (-1 == edge_idx) {
            break;
        }

        root_a = set_find(g_edge_mem[edge_idx].pa);
        root_b = set_find(g_edge_mem[edge_idx].pb);
        if (root_a == root_b) {
            continue;
        }

        // ÿ���������Ϻϲ����ܼ��ϸ���������һ��
        set_union(root_a, root_b);
        set_cnt--;
        sum_weight += g_edge_mem[edge_idx].weight;
    }

    if (set_cnt != g_k) {
        printf("-1\n");
        return;
    }

    printf("%d\n", sum_weight);
    return;
}

static int init()
{
    int i, edge_cnt;

    scanf("%d %d %d", &g_set_cnt, &edge_cnt, &g_k);
    getchar();

    if (g_set_cnt < g_k) {
        flush_input_data(edge_cnt);
        return -1;
    }
    if (g_set_cnt == g_k) {
        flush_input_data(edge_cnt);
        return 0;
    }

    g_point_mem = new point_s[g_set_cnt + 1];
    for (i = 1; i <= g_set_cnt; i++) {
        g_point_mem[i].dad_idx = i;
        g_point_mem[i].rank = 0;
    }

    g_edge_mem = new edge_s[edge_cnt + 1];
    g_heap = new int[edge_cnt + 1];
    for (i = 1; i <= edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].pa, &g_edge_mem[i].pb, &g_edge_mem[i].weight);
        getchar();

        g_heap[i] = i;
    }
    g_heap[0] = edge_cnt;

    return 1;
}

static void end()
{
    delete[] g_point_mem;
    delete[] g_edge_mem;
    delete[] g_heap;

    return;
}

void persimmon_merge()
{
    int tmp;

    tmp = init();
    if (1 != tmp) {
        printf("%d\n", tmp);
        return;
    }

    create_heap();
    process();

    end();

    return;
}
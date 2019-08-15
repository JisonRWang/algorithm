/* ��Ŀ
            ���·
*   ����
            ����һ�� n ����������Ȩͼ���ڵ�ı�Ŵ� 1 �� n��
     ��� S �� T �����·�����ȡ�
*   �����ʽ
            ��һ�� 4 ���� n,m,S,T���ֱ��ʾ��������������㡢�յ㡣
            ������ m �У�ÿ�� 3 �������� u,v,w������һ�� u �� v ��˫��ߣ���ȨΪ w��
            ��֤ 1<=u,v<=n��
*   �����ʽ
            ���һ��һ����������ʾ S �� T �����·��
*   ��������
            7 11 5 4
            2 4 2
            1 4 3
            7 2 2
            3 4 3
            5 7 5
            7 3 3
            6 1 1
            6 3 4
            2 4 3
            5 6 3
            7 2 1
*   �������
            7
*   ����
            ���⹲���� 12 �����Ե㡣
            ����ǰ 10 �����Ե㣬��֤ n<=2500��m<=6200��
     ����ÿ������ w<=1000���ⲿ���������ݶȡ�
            �������е� 12 �����Ե㣬��֤ n<=100,000��m<=250,000��
            ʱ�䣺4 sec
            �ռ䣺256 MB
*   ��ʾ
            [������ Dijkstra �㷨��ģ����ϰ�⡣]
            [ʹ�����ص� Dijkstra �㷨����ͨ��ǰ 10 �����Ե㡣]
            [ʹ�öѻ�__std::priority_queue__�Ż��� Dijkstra �㷨����ͨ�����в��Ե㡣]
*   �ҵ�˼·
            ������ԭ����dijkstra �㷨Ҫ�򵥣���Ϊԭʼ��dijkstra �㷨���ڽ��
     ��Դ���·�����⣬ͼ������ģ��������Ҫ����dijkstra �㷨����һ��
     ����ͼ������������·�������Ҵ����⿴��һ�����ҵ����·����
     ��ͼ�϶�����ͨ�ģ����Ա���ǳ��򵥡�
            Ψһ���ѵ��ǣ���ʾ�����Կ�����������ͼ�����رߵġ�
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

#define INFINITY 0x7fffffff

typedef struct adjoining_point
{
    int id;         // �ڽӵ���ڴ�����
    int weight;     // ���ڽӵ������ı�Ȩ
    struct adjoining_point *next;
}adjoining_point_s;

typedef struct point
{
    bool in_heap;
    int dad;
    int weight;  // ���Ա�ʾΪ���������Ȩ�أ�Ҳ���������·���е�Ȩ��
    int heap_loc; // ��¼�õ��ڶ��е�λ�ã�����������
    adjoining_point_s *ap; // ����õ����ڵ����е�
}point_s;

typedef struct edge
{
    int pa;
    int pb;
    int weight;
}edge_s;

int g_point_cnt;
int g_edge_cnt;
int g_src_point;
int g_dst_point;

edge_s* g_edge_mem;
point_s* g_adjoining_table; // ���򱣴����е��Լ�ÿ�����Լ��������ڽӵ�
int* g_heap; // ֻ��¼�����ڴ��е�����

int g_idx; // ��g_ap_mem ���ʹ�ã��൱�ڷ����ڴ�
adjoining_point_s* g_ap_mem; // �洢������Ҫ�������ڽӵ�

/* С����
*   Ҫ������;Ų�����ĵ�����ڶ��е�λ��
*   �����Ƿ��ڶ��еı��
*/
int delete_heap_peak()
{
    int i, child, peak, tmp, heap_size;

    heap_size = g_heap[0];
    if (heap_size <= 0) {
        return -1;
    }

    peak = g_heap[1];
    g_adjoining_table[peak].in_heap = false;
    g_heap[1] = g_heap[heap_size];
    g_adjoining_table[g_heap[heap_size]].heap_loc = 1;
    g_heap[0] = --heap_size;

    for (i = 1; (i<<1) <= heap_size; i = child) {
        child = i << 1;

        if (child < heap_size &&
            g_adjoining_table[g_heap[child]].weight >= g_adjoining_table[g_heap[child+1]].weight) {
            child++;
        }
        if (g_adjoining_table[g_heap[i]].weight <= g_adjoining_table[g_heap[child]].weight) {
            break;
        }

        tmp = g_heap[child];
        g_heap[child] = g_heap[i];
        g_heap[i] = tmp;

        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[child]].heap_loc = child;
    }

    return peak;
}

/* С����
*   ���ĳ���������
*   ��Ҫ������;Ų�����ĵ�����ڶ��е�λ��
*/
void percolate_up(int heap_loc)
{
    int i, dad, tmp;

    for (i = heap_loc; (i>>1) >= 1; i = dad) {
        dad = i >> 1;
        if (g_adjoining_table[g_heap[i]].weight >= g_adjoining_table[g_heap[dad]].weight) {
            break;
        }

        tmp = g_heap[i];
        g_heap[i] = g_heap[dad];
        g_heap[dad] = tmp;

        g_adjoining_table[g_heap[i]].heap_loc = i;
        g_adjoining_table[g_heap[dad]].heap_loc = dad;
    }

    return;
}

void shortest_path_process()
{
    int tmp_idx, tmp_weight;
    adjoining_point_s *cur, *next;

    if (g_src_point == g_dst_point) {
        printf("0\n");
        return;
    }

    // ��ʼ�����
    g_adjoining_table[g_src_point].weight = 0;
    percolate_up(g_adjoining_table[g_src_point].heap_loc);

    while (1) {
        tmp_idx = delete_heap_peak();
        if (-1 == tmp_idx) {
            printf("Over!\n");
            return;
        }
        if (tmp_idx == g_dst_point) {
            printf("%d\n", g_adjoining_table[tmp_idx].weight);
            return;
        }

        // �����ڽ���(���û���κ��ڽ��㣬�Ǿ��Ƿ���ͨͼ)
        cur = g_adjoining_table[tmp_idx].ap;
        while (NULL != cur) {
            next = cur->next;
            if (!g_adjoining_table[cur->id].in_heap) {
                cur = next;
                continue;
            }
            /* tips: cur->weight ��ʾ�����߱����Ȩ��
                    *   g_adjoining_table[cur->id].weight ��ʾ���ڽ��㵱ǰ��Ȩ��
                    */
            tmp_weight = g_adjoining_table[tmp_idx].weight + cur->weight;
            if (tmp_weight < g_adjoining_table[cur->id].weight) {
                g_adjoining_table[cur->id].weight = tmp_weight;
                g_adjoining_table[cur->id].dad = tmp_idx;
                percolate_up(g_adjoining_table[cur->id].heap_loc);
            }

            cur = next;
        }
    }

    return;
}

void config_adjoining_point(int tmp_point, int tmp_ap, int weight)
{
    adjoining_point_s *next;

    next = g_adjoining_table[tmp_point].ap;
    g_adjoining_table[tmp_point].ap = g_ap_mem + g_idx;
    g_idx++;

    g_adjoining_table[tmp_point].ap->id = tmp_ap;
    g_adjoining_table[tmp_point].ap->weight = weight;
    g_adjoining_table[tmp_point].ap->next = next;

    return;
}

void create_adjoining_table()
{
    int i;
    int tmp_a, tmp_b, tmp_w;

    // �������еıߣ����������ڽӱ�
    for (i = 0; i < g_edge_cnt; i++) {
        tmp_a = g_edge_mem[i].pa;
        tmp_b = g_edge_mem[i].pb;
        tmp_w = g_edge_mem[i].weight;

        // ��Ϊ������ͼ�����������㶼Ҫ����
        config_adjoining_point(tmp_a, tmp_b, tmp_w);
        config_adjoining_point(tmp_b, tmp_a, tmp_w);
    }

    return;
}

void init()
{
    int i;

    scanf("%d %d %d %d", &g_point_cnt, &g_edge_cnt, &g_src_point, &g_dst_point);
    getchar();

    g_edge_mem = new edge_s[g_edge_cnt];
    for (i = 0; i < g_edge_cnt; i++) {
        scanf("%d %d %d", &g_edge_mem[i].pa, &g_edge_mem[i].pb, &g_edge_mem[i].weight);
        getchar();
    }

    // �����Ŵ�1 ��ʼ
    g_adjoining_table = new point_s[g_point_cnt+1];
    g_heap = new int[g_point_cnt+1];
    for (i = 1; i <= g_point_cnt; i++) {
        g_heap[i] = i;

        g_adjoining_table[i].in_heap = true;
        g_adjoining_table[i].dad = i;
        g_adjoining_table[i].weight = INFINITY;
        g_adjoining_table[i].heap_loc = i;
        g_adjoining_table[i].ap = NULL;
    }
    g_heap[0] = g_point_cnt;

    // ÿ���������㣬��Ϊ����ͼ������׼��2*g_edge_cnt �����������ڽӱ�
    g_idx = 0;
    g_ap_mem = new adjoining_point_s[2*g_edge_cnt];
    create_adjoining_table();
    
    return;
}

void end()
{
    delete[] g_edge_mem;
    delete[] g_adjoining_table;
    delete[] g_heap;
    delete[] g_ap_mem;

    return;
}

int main() 
{
    init();

    shortest_path_process();

    end();

    return 0;
}

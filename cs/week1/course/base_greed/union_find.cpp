/* ���鼯
*      Union
*        ������
*      Find
*        ʹ��·��ѹ��
*      ʹ��·��ѹ��ʱ�����ϵ��ȵ�ֵ��Ȼ����Ϊ·��ѹ��֮ǰ���Ǹ�ֵ
*/

#include <iostream>
#include <cstdio> // ������ȷ������visual studio����ʽ�������Ϳɶ���

using namespace std;

typedef struct point
{
    int index; // ���㵱ǰ���ڴ��е�����
    int rank;  // ��
    int dad_index;
}point_s;

static int g_N;
static int g_mem_index;
static point_s* g_memory;

// ���ظ��ڵ�����
int Find(point_s* cur_point)
{
    // �ݹ��
    if (-1 == cur_point->dad_index) {
        return cur_point->index;
    }

    // ʹ��·��ѹ����������
    cur_point->dad_index = Find(g_memory + cur_point->dad_index);
    return cur_point->dad_index;
}

// ���غϲ�֮��ļ��ϵĸ��ڵ�
point_s* Union(point_s* set_a_root, point_s* set_b_root)
{
    if (set_b_root->rank < set_a_root->rank) {
        set_b_root->dad_index = set_a_root->index;
        return set_a_root;
    }

    set_a_root->dad_index = set_b_root->index;
    if (set_a_root->rank == set_b_root->rank) {
        set_b_root->rank++;
    }
    return set_b_root;
}

static void init()
{
    int i;

    g_N = 7;
    g_mem_index = 0;
    g_memory = new point_s[g_N];

    for (i = 0; i < g_N; i++) {
        g_memory[i].index = i;
        g_memory[i].rank = 0;
        g_memory[i].dad_index = -1;
    }

    return;
}

static void end()
{
    delete[] g_memory;

    return;
}

void Union_Find()
{
    int i;
    point_s* tmp_set_root[10];

    init();

    // �ϲ�56
    tmp_set_root[0] = Union(g_memory + 5, g_memory + 6);
    printf("�ϲ�56\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // �ϲ�34
    tmp_set_root[1] = Union(g_memory + 3, g_memory + 4);
    printf("�ϲ�34\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // �ϲ�12
    tmp_set_root[2] = Union(g_memory + 1, g_memory + 2);
    printf("�ϲ�12\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // �ϲ�0��12
    tmp_set_root[3] = Union(g_memory + 0, tmp_set_root[2]);
    printf("�ϲ�0��12\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // ����012
    printf("Find 0: %d\n", Find(g_memory + 0));
    printf("Find 1: %d\n", Find(g_memory + 1));
    printf("Find 2: %d\n", Find(g_memory + 2));
    printf("--------------------------------------------------\n");

    // �ϲ�01234
    tmp_set_root[4] = Union(tmp_set_root[1], tmp_set_root[3]);
    printf("�ϲ�01234\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // ����3
    printf("Find 3: %d\n", Find(g_memory + 3));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // �ϲ�0123456
    tmp_set_root[5] = Union(tmp_set_root[0], tmp_set_root[4]);
    printf("�ϲ�0123456\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // ����6
    printf("Find 6: %d\n", Find(g_memory + 6));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // ����5
    printf("Find 5: %d\n", Find(g_memory + 5));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    end();

    return;
}
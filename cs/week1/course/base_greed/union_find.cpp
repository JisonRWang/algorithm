/* 并查集
*      Union
*        按秩求并
*      Find
*        使用路径压缩
*      使用路径压缩时，集合的秩的值仍然保留为路径压缩之前的那个值
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

typedef struct point
{
    int index; // 本点当前在内存中的索引
    int rank;  // 秩
    int dad_index;
}point_s;

static int g_N;
static int g_mem_index;
static point_s* g_memory;

// 返回根节点索引
int Find(point_s* cur_point)
{
    // 递归基
    if (-1 == cur_point->dad_index) {
        return cur_point->index;
    }

    // 使用路径压缩，不管秩
    cur_point->dad_index = Find(g_memory + cur_point->dad_index);
    return cur_point->dad_index;
}

// 返回合并之后的集合的根节点
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

    // 合并56
    tmp_set_root[0] = Union(g_memory + 5, g_memory + 6);
    printf("合并56\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 合并34
    tmp_set_root[1] = Union(g_memory + 3, g_memory + 4);
    printf("合并34\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 合并12
    tmp_set_root[2] = Union(g_memory + 1, g_memory + 2);
    printf("合并12\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 合并0和12
    tmp_set_root[3] = Union(g_memory + 0, tmp_set_root[2]);
    printf("合并0和12\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 查找012
    printf("Find 0: %d\n", Find(g_memory + 0));
    printf("Find 1: %d\n", Find(g_memory + 1));
    printf("Find 2: %d\n", Find(g_memory + 2));
    printf("--------------------------------------------------\n");

    // 合并01234
    tmp_set_root[4] = Union(tmp_set_root[1], tmp_set_root[3]);
    printf("合并01234\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 查找3
    printf("Find 3: %d\n", Find(g_memory + 3));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 合并0123456
    tmp_set_root[5] = Union(tmp_set_root[0], tmp_set_root[4]);
    printf("合并0123456\n");
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 查找6
    printf("Find 6: %d\n", Find(g_memory + 6));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    // 查找5
    printf("Find 5: %d\n", Find(g_memory + 5));
    for (i = 0; i < g_N; i++) {
        printf("g_memory[%d]: index=%d, rank=%d, dad_index=%d\n",
            i, g_memory[i].index, g_memory[i].rank, g_memory[i].dad_index);
    }
    printf("--------------------------------------------------\n");

    end();

    return;
}
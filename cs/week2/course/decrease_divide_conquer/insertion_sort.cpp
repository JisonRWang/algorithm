/* 插入排序
*           是一种online 的排序算法
*           少量数据的排序推荐用这种，方便快捷，好写
*           该算法最重要的性质就是将新数据插入到一个已经排好序的
     数列中，这比选择排序或冒泡排序那种在无序数列中选择数据并
     浪费了已排序数列的算法要高效的多，关键就是该算法能够利用
     前面已经排好序的数列。虽然该算法上届和选择排序或冒泡排序
     相同，但平均时间复杂度是不同的。
*/

#include <iostream>
#include <cstdio> 

using namespace std;

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

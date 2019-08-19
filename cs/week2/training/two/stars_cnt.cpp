/* 题目
            数星星
*   描述
            小粽今晚在数星星。
            小粽把整个天空看作一个平面，她测出了她看见的
     每个星星的坐标，第 i 颗星星的坐标为 (x[i],y[i])。光数星
     星实在是太无聊了，小粽想知道，对于每颗星星，其
     左下方的星星的数量，即对于每个 i，小粽想要知道满
     足 j≠i，且 x[j]≤x[i],y[j]≤y[i] 的 j 的数量。
*   输入格式
            第一行一个正整数 n，表示星星的数量。接下来 n 行，
     每行两个正整数 x[i],y[i]，表示第 i 颗星星的坐标。
*   输出格式
            输出共 n 行，每行输出一个正整数，表示第 i 颗星星
     左下方星星的数量。
*   输入样例1
            5
            1 1
            5 1
            7 1
            3 3
            5 5
*   输出样例
            0
            1
            2
            1
            3
*   限制
            对于 30% 的数据有 n≤500；
            对于 60% 的数据有 n≤8000；
            对于 100% 的数据有 n≤3×10^5，所有坐标都在 int 范围内，
     不存在两个不同的点有相同的坐标。
*   提示
            [回想一下归并求逆序对咋做的？你就会做这个题辣]
            [有兴趣的同学百度二维偏序~]
*   我的思路
            一开始我想用快排先对x 轴做一遍排序，在这个基础上，用找
     第k 大的数的方法去判断在经过以x 排序的序列上，在某点的横坐
     标x 的左面的序列中，该点的y 是这个序列第几大的数，得到的结
     果就是所求结果。仔细想来，其实这种方法与蛮力求解无异。
            再就是本题提示的归并求逆序的方法来做这道题。
            还是先将整个数列以x 坐标做一遍排序，然后以y 再做一次归并
     排序。以y 做归并排序的时候，左半边或右半边内部的x 的顺序已
     经不用关心，因为在递归到最底层的时候已经处理完了；左半边
     的x 坐标一定小于右半边的x 坐标，所以只要知道每次左边有哪些
     点的y 小于右边当前的值就好了。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

#define CODI_X 0
#define CODI_Y 1

typedef struct point
{
    int cnt;
    int coordinate[2];
}point_s;

int g_cnt;
point_s *g_mem;
int *g_arr;
int *g_tmp;

void merge(int left_lo, int right_lo, int right_hi, int cord)
{
    int tmp_idx, start_idx, left_hi;

    tmp_idx = right_hi;
    start_idx = tmp_idx;
    left_hi = right_lo - 1;

    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[g_arr[left_hi]].coordinate[cord] <= g_mem[g_arr[right_hi]].coordinate[cord]) {
            /* 对x 排序的时候，如果遇到x 相等的情况，则将y 更大的点
                     *  放到右面，这样在对y 排序的时候，如果出现左半部分的
                     *  y 大于右半部分的y ，则说明此时位于左半部分的该点的x 
                     *  一定小于右半部分那个点的x，而不会出现两个x 相等的情
                     *  况。提示，题干中已经说明不存在两个坐标完全相同的点，
                     *  即，如果x 相同则y 肯定不同；如果y 相同则x 肯定不同。
                     */
            if (CODI_X == cord &&
                (g_mem[g_arr[left_hi]].coordinate[cord] == g_mem[g_arr[right_hi]].coordinate[cord]) &&
                (g_mem[g_arr[left_hi]].coordinate[CODI_Y] > g_mem[g_arr[right_hi]].coordinate[CODI_Y])) {
                    g_tmp[tmp_idx--] = g_arr[left_hi];
                    left_hi--;
                    continue;
            }

            /* 考虑边界的问题
                     *   y 相同x 不同: 因为先按x 排序，所以此时x 小的一定在左半边
                     *   那么这里输出右半边是没错的
                     *   x 相同y 不同: 仍然应该先输出右半边
                     */ 
            if (CODI_Y == cord) {
                g_mem[g_arr[right_hi]].cnt += left_hi - left_lo + 1;
            }
            
            g_tmp[tmp_idx--] = g_arr[right_hi];
            right_hi--;
            continue;
        }

        /* 由于排x 的时候，就保证了对于x 相同的情况，让y 更大的排
              *   右面，所以在排y 的时候，如果走到这里，说明左半部分的
              *   y 一定大于右半部分的y，并且x 肯定不相等(确切的说，此时
              *   左边的x 一定小于右边的x)。
              */
        g_tmp[tmp_idx--] = g_arr[left_hi];
        left_hi--;
    }

    // 如果左半边先空，则将右半边剩余的拷贝到左半边
    while (right_lo <= right_hi) {
        g_arr[left_lo++] = g_arr[right_lo];
        right_lo++;
    }
    while (tmp_idx < start_idx) {
        g_arr[start_idx] = g_tmp[start_idx];
        start_idx--;
    }
    
    return;
}

void merge_sort(int lo, int hi, int cord)
{
    int mid;

    // 递归基
    if (lo == hi) {
        return;
    }

    mid = (lo + hi) / 2;
    merge_sort(lo, mid, cord);
    merge_sort(mid+1, hi, cord);
    merge(lo, mid+1, hi, cord);

    return;
}

void process()
{
    int i;
    
    merge_sort(1, g_cnt, CODI_X);
    merge_sort(1, g_cnt, CODI_Y);

    for (i = 1; i <= g_cnt; i++) {
        printf("%d\n", g_mem[i].cnt);
    }

    return;
}

void init()
{
    int i;

    scanf("%d", &g_cnt);
    getchar();

    // 从1 开始
    g_mem = new point_s[g_cnt+1];
    g_arr = new int[g_cnt+1];
    g_tmp = new int[g_cnt+1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d %d", &g_mem[i].coordinate[CODI_X], &g_mem[i].coordinate[CODI_Y]);
        getchar();

        g_mem[i].cnt = 0;
        g_arr[i] = i;
    }

    return;
}

void end()
{
    delete[] g_mem;
    delete[] g_arr;
    delete[] g_tmp;

    return;
}

int main()
{
    init();

    process();

    end();

    return 0;
}


/* 题目
*          成绩排序
*  描述
            有 n 名学生，它们的学号分别是 1,2,…,n。这些学生都选修
    了邓老师的算法训练营、数据结构训练营这两门课程。
            学期结束了，所有学生的课程总评都已公布，所有总评分
    数都是 [0,100] 之间的整数。巧合的是，不存在两位同学，他们
    这两门课的成绩都完全相同。邓老师希望将这些所有的学生按
    这两门课程的总分进行降序排序，特别地，如果两位同学的总
    分相同，那邓老师希望把算法训练营得分更高的同学排在前面。
    由于上面提到的巧合，所以，这样排名就可以保证没有并列的
    同学了。
            邓老师将这个排序任务交给了他的助教。可是粗心的助教没有
    理解邓老师的要求，将所有学生按学号进行了排序。邓老师希望
    知道，助教的排序结果中，存在多少逆序对。
            如果对于两个学生 (i,j) 而言，i 被排在了 j 前面，并且i 本应被排
    在 j 的后面，我们就称 (i,j) 是一个逆序对。
            请你先帮邓老师把所有学生按正确的顺序进行排名，再告诉他
    助教的错误排名中逆序对的数目。
*  输入格式
            第一行一个整数 n，表示学生的个数。
            第 2 行到第 n+1 行，每行 2 个用空格隔开的非负整数，第 i+1 行的
    两个数依次表示学号为 i 的同学的算法训练营、数据结构训练营的
    总评成绩。
*  输出格式
            输出包含 n+1 行。
            前 n 行表示正确的排序结果，每行 4 个用空格隔开的整数，第 i 行
    的数依次表示排名为 i 的同学的学号、总分、算法训练营成绩、数据
    结构训练营成绩。
            第 n+1 行一个整数，表示助教的错误排名中逆序对的数目。
*  样例输入
            3
            95 85
            90 90
            100 99
*  样例输出
            3 199 100 99
            1 180 95 85
            2 180 90 90
            2
*  样例解释
            学号为 3 的同学总分为 199，是最高的，所以他应该排第一名。
            学号为 1 的同学虽然总分与学号为 2 的同学一致，但是他的算法训
    练营成绩更高，所以在排名规则下更胜一筹。
            原错误排名中的逆序对数目为 2 ，这些逆序对分别为 (1,3) 和 (2,3)。
*  数据范围
            对于 25% 的数据，保证 n=3。
            对于 50% 的数据，保证 n≤10。
            对于另外 25% 的数据，保证所有同学的总分两两不同。
            对于 100% 的数据，保证 n≤5,000 ，且保证不存在成绩完全相同的学生。
            时间限制：10 sec
            空间限制：256 MB
*  提示
           [可以使用起泡排序将所有学生进行排名。]
           [在起泡排序的过程中，每次交换都会使逆序对数目减少 1 ]
           [这道题可以设计出时间复杂度为 O(nlogn) 的算法。]
*  我的思路
           用归并排序求逆序对的方法，时间复杂度为O(nlogn)
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

typedef struct score
{
    int algorithm_score;
    int datastructure_score;
    int sum;
}score_s;

int g_cnt;
int g_inversions_cnt;
score_s *g_mem;
int *g_arr; // 存g_mem的索引
int *g_tmp;

void merge(int left_lo, int right_lo, int right_hi)
{
    int left_hi, end_idx, tmp_idx;

    left_hi = right_lo - 1;
    end_idx = right_hi;
    tmp_idx = end_idx;

    // 二路合并
    // 按照题意，从大到小排序
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if ((g_mem[g_arr[left_hi]].sum < g_mem[g_arr[right_hi]].sum) ||
            ((g_mem[g_arr[left_hi]].sum == g_mem[g_arr[right_hi]].sum) && 
             (g_mem[g_arr[left_hi]].algorithm_score < g_mem[g_arr[right_hi]].algorithm_score))) {
            // 统计逆序对(左边的都应该大于右边的，否则就是逆序)
            g_inversions_cnt += right_hi - right_lo + 1;

            g_tmp[tmp_idx--] = g_arr[left_hi];
            left_hi--;
            continue;
        }
        
        if ((g_mem[g_arr[left_hi]].sum > g_mem[g_arr[right_hi]].sum) ||
            ((g_mem[g_arr[left_hi]].sum == g_mem[g_arr[right_hi]].sum) &&
             (g_mem[g_arr[left_hi]].algorithm_score > g_mem[g_arr[right_hi]].algorithm_score))) {
            g_tmp[tmp_idx--] = g_arr[right_hi];
            right_hi--;
        }
    }

    // 右边有剩余，左边已经空了，将右边拷贝到左边
    while (right_lo <= right_hi) {
        g_arr[left_lo++] = g_arr[right_lo];
        right_lo++;
    }
    while (tmp_idx < end_idx) {
        g_arr[end_idx] = g_tmp[end_idx];
        end_idx--;
    }

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int median;

    // 递归基
    if (lo == hi) {
        return;
    }

    median = (lo + hi) / 2;
    merge_sort_by_recursion(lo, median);
    merge_sort_by_recursion(median+1, hi);
    merge(lo, median+1, hi);

    return;
}

void print_result()
{
    int i;

    for (i = 1; i <= g_cnt; i++) {
        printf("%d %d %d %d\n", 
            g_arr[i], g_mem[g_arr[i]].sum, 
            g_mem[g_arr[i]].algorithm_score, g_mem[g_arr[i]].datastructure_score);
    }

    printf("%d\n", g_inversions_cnt);
    return;
}

void merge_sort()
{
    int lo, hi;

    lo = 1;
    hi = g_cnt;
    merge_sort_by_recursion(lo, hi);
    print_result();

    return;
}

void init()
{
    int i;
    
    scanf("%d", &g_cnt);
    getchar();

    // 学号从1 开始
    g_mem = new score_s[g_cnt+1];
    g_arr = new int[g_cnt+1];
    g_tmp = new int[g_cnt+1];
    for (i = 1; i <= g_cnt; i++) {
        scanf("%d %d", &g_mem[i].algorithm_score, &g_mem[i].datastructure_score);
        getchar();
        g_mem[i].sum = g_mem[i].algorithm_score + g_mem[i].datastructure_score;

        g_arr[i] = i;
    }
    g_inversions_cnt = 0;

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

    merge_sort();

    end();

    return 0;
}

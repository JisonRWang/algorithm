/* 题目
            周测2
*   描述
            给定一个满二叉树，即这棵二叉树有n = 2^m 个叶子，每个叶子
     上有一个数字，且从左往右看去，这些数字序列是一个1 到n 的排列。
            二叉树每个非叶节点都能任意次数地交换左右孩子，且交换没有
     先后顺序的要求。交换完以后，从左往右看去，叶子组成的数字序列
     （仍是1到n 的排列）的逆序对可能发生了改变哦~            
            现在你要求出一种最佳的交换方案，使得叶子组成的数字序列的逆
     序对数目尽量小。
*   输入格式
            输入的第一行包含一个正整数 n，这个正整数必为2的幂次。            
            接下来1 行包含n 个整数，一个1到n 的排列，依次表示初始状态下，
     从左到右看到的叶子上的数字序列。
*   输出格式
            输出1 行1 个整数，即最小的逆序对个数。
*   输入样例
            8
            3 1 6 2 8 7 4 5
*   输出样例
            3
*   样例解释
            这个二叉树一开始是这样的
             a
          /     \
        /         \
      b             c
    /   \         /   \
  d      e      f      g
 / \    / \    / \    / \
3   1  6   2  8   7  4   5
            经过一系列非叶节点的左右孩子交换：
            swap(left(c), right(c))
            swap(left(e), right(e))
            swap(left(d), right(d))
            swap(left(f), right(f))
            得到最优的方案：
             a
          /     \
        /         \
      b             c
    /   \         /   \
  d      e      g      f
 / \    / \    / \    / \
1   3  2   6  4   5  7   8
            其叶子组成的数字序列为
            1 3 2 6 4 5 7 8
            逆序对个数为3。可以验证这个方案是最优的。
*   限制
            其中20%的数据，m≤10；            
            另外40%的数据，m≤18；            
            剩下20%的数据，m≤20。
            时间：2 sec
            空间：256 MB
*   我的思路
            归并排序的又一应用。
            其实和二叉树一点关系都没有，本题中，提到二叉树的唯一目的就
     是说明给定的输入数列中元素个数是2 的幂，如果要移动，也只能以2
     的幂的个数去移动这些数。看到2 的幂，直接想法就是二分，又说到逆
     序对，直接就往归并排序上靠。
            本题中，能交换的位置只有诸如样例中的13/26/45/78 或de/gf/bc 这些，而
     不能交换32/64/57/eg 这样的位置。这些能交换的位置其实就是归并排序中
     的左右两边，是否要交换，就看左边放在右边的左面逆序对少还是说将
     右边放到左边的左面逆序对少。左右两边比较计算逆序对的时候，是不
     会再计算左边或右边自己内部的逆序对的，因为已经计算过了，所以可
     将左右两边自己内部的数据排序，以保证左右两边在二路合并的时候能
     快速计算逆序对个数。
*/

#include <iostream>
#include <cstdio> 
    
using namespace std;

typedef long long s64;

s64 g_inversions_cnt;
int g_n;
int *g_mem;
int *g_tmp;

s64 ivs_cnt(int left_lo, int left_hi, int right_lo, int right_hi)
{
    s64 tmp_cnt;

    tmp_cnt = 0;
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            left_lo++;
            continue;
        }
        right_lo++;
        tmp_cnt += left_hi - left_lo + 1;
    }

    return tmp_cnt;
}

void merge(int left_lo, int right_lo, int right_hi)
{
    s64 l_ivs_cnt, r_ivs_cnt;
    int start_idx, tmp_idx, left_hi;
 
    tmp_idx = left_lo;
    start_idx = tmp_idx;
    left_hi= right_lo - 1;

    /* 因为左右相等时无法准确计算左边的逆序对，因此这里专门
       *   将左右两边交换，用于计算原来左边相对于右边的逆序对。
       */ 
    l_ivs_cnt = ivs_cnt(right_lo, right_hi, left_lo, left_hi);
    r_ivs_cnt = 0;
    
    while (left_lo <= left_hi && right_lo <= right_hi) {
        if (g_mem[left_lo] <= g_mem[right_lo]) {
            g_tmp[tmp_idx++] = g_mem[left_lo];
            left_lo++;

            continue;
        }
        g_tmp[tmp_idx++] = g_mem[right_lo];
        right_lo++;

        // 左边大于右边，对于右边来讲，出现逆序对
        r_ivs_cnt += left_hi - left_lo + 1;
    }

    // 如果右面先空，左面有剩余
    while (left_lo <= left_hi) {
        g_mem[right_hi--] = g_mem[left_hi];
        left_hi--;
    }
    while (start_idx < tmp_idx) {
        g_mem[start_idx] = g_tmp[start_idx];
        start_idx++;
    }

    g_inversions_cnt += (l_ivs_cnt <= r_ivs_cnt) ? l_ivs_cnt: r_ivs_cnt;

    return;
}

void merge_sort_by_recursion(int lo, int hi)
{
    int mid;

    // 递归基
    if (lo == hi) {
        return;
    }

    mid = (lo + hi) / 2;
    merge_sort_by_recursion(lo, mid);
    merge_sort_by_recursion(mid+1, hi);
    merge(lo, mid+1, hi);

    return;
}

void process()
{
    merge_sort_by_recursion(1, g_n);

    printf("%lld\n", g_inversions_cnt);

    return;
}

void init()
{
    int i;

    scanf("%d", &g_n);
    getchar();

    g_inversions_cnt = 0;
    g_mem = new int[g_n+1];
    g_tmp = new int[g_n+1];
    for (i = 1; i <= g_n; i++) {
        scanf("%d", &g_mem[i]);
        getchar();
    }

    return;
}

void end()
{
    delete[] g_mem;
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


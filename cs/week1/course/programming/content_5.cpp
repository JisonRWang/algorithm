/* 题目：
*  八皇后问题
*     在国际象棋的棋盘上，放置8个皇后（棋子），使皇后两两之间互不攻击。
*  所谓互不攻击，是指任何两个皇后都要满足：
*     不在棋盘的同一行
*     不在棋盘的同一列
*     不在棋盘的同一对角线（提示，对角线有两条）
*  求解怎么放以及有多少种放置的方法
*  8*8的棋盘
     __ __ __ __ __ __ __ __ 
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
    |__|__|__|__|__|__|__|__|
     
*  我的思路（和老师的所谓回溯方法相同）：
*      与跳马、分书问题的原理完全相同，使用深度优先+递归的方式，把所有合适的结果都找出来。这里唯一一个难点是如何判断落点的合法性，这个直接参考
*  老师给的那种方法即可。剩下的就是深度优先+递归的实现：先在（1，1）位置放置，然后进入递归，在（2，y）处找到最近的一个合法落点位置，然后进入递
*  归，在（3，y）位置找一个最近的合法落点位置，以此类推，直到找到（8，y）的一个最近的合法落点位置，输出结果，然后继续在（8，y）处找其他所有合法
*  落点位置，直到把（8，y）处的全找到，然后这层递归结束，回到（7，y）这层递归，在这层找到这层的下一个合法位置，然后再进入（8，y）处寻找所有的
*  （8，y）的合法位置并输出，等到把（7，y）的所有合法位置都找到后，就可以返回到上一层即（6，y）位置去完成这个过程，以此类推到（1，y）位置。
*  老师的所谓非回溯方法：
*      与分书问题的方法完全相同，就是记录一个临时分配方案而已。
*  我的数据结构和原理：
*      棋盘左下角在坐标轴(1,1)，右上角在(8,8)
*      对角线有两种，斜率分别为1和-1，斜率相同时，不同的对角线截距不同
*      每种斜率都有15条对角线（例如，斜率为1时，从点(8,1)到点(1,8)有15条对角线）
*      斜率为1，截距范围[-7,7]，斜率为-1时，截距范围[2,16]
*      斜率为1，对角线上点的可表示为y-x=截距，斜率为-1，对角线上的点可表示为y+x=截距
*      同一条对角线上的点，y-x或y+x的值（截距）都相同，所以可以以此判定是否在同一条对角线上
*      因为斜率相同，所以可在同一斜率下，用不同的截距来区分不同的对角线
*      建立以截距为索引的一维数组，元素值为该对角线是否已经有皇后
*      因为截距有负值，所以应加一个偏移量，使其能够成为数组索引
*      斜率为1的对角线，偏移量为7；斜率为-1的对角线，可以不使用偏移量
*      棋盘中共有8行，建立一个一维数组，表示每一行是否已经有皇后
*      算法是逐列放置皇后的，天然不会在同一列放置皇后，所以不用检查每一列是否已经有皇后
*/

#include <iostream>

using namespace std;

#define ROW 9
#define COL 9

typedef struct Point
{
    int x;
    int y;
}Point_s;

// 第0个没用，1~8个皇后固定放在1~8列，每次变换的只有行，所以这里直接初始化好x，算法里就不用再管了
// 例如，第1个皇后固定放在第1列，考察的仅仅是第1个皇后可以被放在哪些行
static Point_s g_queens_loc[9] = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0} };

static int g_chess_row[ROW] = { 0 }; // 第0个元素没用
static int g_intercept_offset = 7; // 截距为负值时使用的偏移量
static int g_positive_diagonal[15] = { 0 }; // 斜率1，15条对角线，下标范围[0,14]
static int g_negative_diagonal[17] = { 0 }; // 斜率-1，15条对角线，下标范围[2,16]，前两个元素浪费

// 检查横纵以及两条对角线上是否有其他皇后
bool safe_location(Point_s cur_loc)
{
    // 行
    if (1 == g_chess_row[cur_loc.y]) {
        return false;
    }

    if (1 == g_positive_diagonal[cur_loc.y - cur_loc.x + g_intercept_offset]) {
        return false;
    }

    if (1 == g_negative_diagonal[cur_loc.y + cur_loc.x]) {
        return false;
    }

    return true;
}

// queen_num [1,8] 表示8个皇后的序号，也是下标
void queen_laid(int& sum, int queen_num)
{
    int i;
    Point_s tmp_p;

    // 递归基
    if (9 == queen_num) {
        sum++;
        cout << "第" << sum << "种放置方法： ";
        for (i = 1; i <= 8; i++) {
            cout << "(" << g_queens_loc[i].x << "," << g_queens_loc[i].y << ")";
        }
        cout << endl;
        return;
    }

    // 第i个queen就在第i列找合适的行去放，这里是遍历行（即，找合适的行）
    for (i = 1; i < ROW; i++) {
        tmp_p.x = queen_num;
        tmp_p.y = i;
        if (safe_location(tmp_p)) {
            g_queens_loc[queen_num].y = tmp_p.y;
            g_chess_row[tmp_p.y] = 1;
            g_positive_diagonal[tmp_p.y-tmp_p.x+g_intercept_offset] = 1;
            g_negative_diagonal[tmp_p.y+tmp_p.x] = 1;

            queen_laid(sum, queen_num + 1);

            g_queens_loc[queen_num].y = 0;
            g_chess_row[tmp_p.y] = 0;
            g_positive_diagonal[tmp_p.y - tmp_p.x + g_intercept_offset] = 0;
            g_negative_diagonal[tmp_p.y + tmp_p.x] = 0;
        }
    }
    return;
}

// 设置棋盘坐标左下角为(1,1)，右上角为(8,8)
void eight_queens()
{
    int sum;

    sum = 0;
    // 皇后范围：[1,8]
    queen_laid(sum, 1);
    
    return;
}
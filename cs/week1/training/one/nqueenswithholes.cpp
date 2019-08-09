/* 题目
*     带洞N皇后问题
*  描述
*     N皇后问题是一个经典的问题，其目标是在一个N*N的棋盘上的每一行放置1个皇后，
并使其不能互相攻击（同一行、同一列、同一斜线上的皇后都会自动攻击）。
*     现在，我们将棋盘上的一些位置挖洞，挖洞的位置不能放置棋子。此时，问一共有多少种可能的放置方法？
*  输入格式
*     输入第一行有一个整数N，表示棋盘大小。 接下来会有N行，每行有N个被空格隔开的整数，
表示该棋盘位置是否有洞。（0为正常，1为有洞）。
*  输出格式
*     输出一行，包含一个整数，表示当前N皇后的放置方案数。
*  样例输入
*     4
*     1 1 0 1
*     0 0 0 0
*     0 0 0 0
*     0 0 0 0
*  样例输出
*     1
*  数据范围
*     1 <= N <= 10
*  时间限制：1 s
*  空间限制：512 MB
*/

#include <iostream>
#include <cstdio> // 必须明确包含，visual studio会隐式包含降低可读性

using namespace std;

#define ROW 11
#define COL ROW

typedef struct Point
{
    int x;
    int y;
}Point_s;

// 记录棋盘输入行列数
static int N;

// 棋盘从(1,1)开始，好理解一些
static char(*g_holes_table)[COL] = nullptr;

static Point_s g_queens_loc[COL] = { {0,0},{1,0},{2,0},{3,0},{4,0},{5,0},
                                         {6,0},{7,0},{8,0},{9,0},{10,0} };

static int g_chess_row[ROW] = { 0 }; // 第0个元素没用
static int g_intercept_offset = 9; // 截距为负值时使用的偏移量
static int g_positive_diagonal[19] = { 0 }; // 斜率1，19条对角线，下标范围[0,18]
static int g_negative_diagonal[21] = { 0 }; // 斜率-1，19条对角线，下标范围[2,20]，前两个元素浪费

// 检查横纵以及两条对角线上是否有其他皇后，并且检查是否有洞
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

    // 是否有洞
    if (1 == g_holes_table[cur_loc.x][cur_loc.y]) {
        return false;
    }

    return true;
}

// queen_num [1,10] 表示最多10个皇后的序号，也是棋盘的列下标（因为是逐列放皇后的）
void queen_laid(int& sum, int queen_num)
{
    int i;
    Point_s tmp_p;

    // 递归基，放置完最后一个皇后，还要再往下走一层，实际在上一步就已经结束了
    if (N+1 == queen_num) {
        sum++;
        return;
    }

    // 第i个queen就在第i列找合适的行去放，这里是遍历行（即，找合适的行）
    for (i = 1; i <= N; i++) {
        tmp_p.x = queen_num;
        tmp_p.y = i;
        if (safe_location(tmp_p)) {
            g_queens_loc[queen_num].y = tmp_p.y;
            g_chess_row[tmp_p.y] = 1;
            g_positive_diagonal[tmp_p.y - tmp_p.x + g_intercept_offset] = 1;
            g_negative_diagonal[tmp_p.y + tmp_p.x] = 1;

            queen_laid(sum, queen_num + 1);

            g_queens_loc[queen_num].y = 0;
            g_chess_row[tmp_p.y] = 0;
            g_positive_diagonal[tmp_p.y - tmp_p.x + g_intercept_offset] = 0;
            g_negative_diagonal[tmp_p.y + tmp_p.x] = 0;
        }
    }
    return;
}

void data_input()
{
    int i, j, tmp;

    // 不检查输入数据合法性
    scanf("%d", &N);
    if (N <= 0) {
        cout << "Wrong input: N = " << N << endl;
        return;
    }

    for (i = 1; i <= N; i++) {
        // 从(1,1)开始输入，行和列的第0项都没用
        for (j = 1; j <= N; j++) {
            scanf("%d", &tmp);
            g_holes_table[i][j] = (char)tmp;
        }
    }

    return;
}

static void init()
{
    int i, j;
    
    g_holes_table = new char[ROW][COL];
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            g_holes_table[i][j] = 0;
        }
    }

    return;
}

static void end()
{
    delete[] g_holes_table;

    return;
}

void n_queens_with_holes()
{
    int sum;

    init();

    data_input();
    
    sum = 0;
    queen_laid(sum, 1);
    cout << sum;

    end();

    return;
}
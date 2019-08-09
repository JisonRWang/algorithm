/* 题目：
*     跳马问题
*     在半张中国象棋的棋盘上，一只马从左下角跳到右上角，只允许
*     往右跳，不允许往左跳，问：能有多少种跳步方案？
*  要求：
*     输出方案数和各方案的具体跳法 
     __ __ ._ __ __ __ ._ __ . end
    |__|__|__|__|._|__|__|__|
    |__|._|__|__|__|__|__|._|
    |__|__|__|__|__|__|__|__|
    |._|__|__|__|__|__|__|__|
    start
*  分析：
*     数字化棋盘，使位置可计算，start处坐标为(0,0)，end处坐标为(8,4)
*     数字化跳法，使操作可计算，共四种跳法：(x+1, y+2)，(x+2,y+1)，(x+2,y-1)，(x+1,y-2)
*  思路：
*     遍历当前所有可能的跳法
*  优化：
*     不同的方案可能会有交点存在，如果可以在第一次计算某个点的时候，就把以该点为起点，到终点的所有方案数和方案内容做记录，那么当其他点
*  走到这个点时，就可以不用再往下计算，而直接使用该点的记录即可。
*  该优化方法的局限：
*     计算总的方案数可以很快，但是列出每一种方案的具体走法就很麻烦，相当于是把棋盘上所有正确的点都找出来，然后再遍历每一种走法，这个需要
*  用图论的深度优先去搞，倒不如直接用老师给的方法，每次就直接把具体的方案打印出来。如果再把从每一个点开始的所有步骤都记录下来，那使用的
*  内存就太多了，与节省的时间相比不划算。
*/

#include <iostream>
#include <memory.h>

using namespace std;

typedef struct Step
{
    int dx;
    int dy;
}Step_s;

/*
typedef struct Point
{
    // 从该点出发（以该点为起点）所拥有的方案数
    int num;

    // 该点坐标
    int x;
    int y;

    // 以该点为起点的所有有效方案中，可能经过的临近点的坐标（不论方案数有多少种，从该点出发最多也只有四种选择，只追踪临近的这四个点即可）
    Step_s avail_point[4];  // 因为只有四种走法，所以下一个可行的点最多只有四个
}Point_s;
*/

void horse_jumping(/*Point_s* point_arr, */Step_s* path, Step_s* dstep, int x, int y, int steps, int& sum)
{
    int i = 0;

    path[steps].dx = x;
    path[steps].dy = y;

    // 递归基
    if (8 == x && 4 == y) {
        sum++;
        
        cout << "第" << sum << "种方案： ";
        for (i = 0; i <= steps; i++) {
            cout << "(" << path[i].dx << ", " << path[i].dy << ")";
        }
        cout << endl;

        return;
    }

    // 校验
    if (x < 0 || 8 < x || y < 0 || 4 < y) {
        return;
    }

    for (i = 0; i < 4; i++) {
        // 从这里可以很明显的看出，递归是深度优先的体现！！！
        horse_jumping(path, dstep, x+dstep[i].dx, y+dstep[i].dy, steps+1, sum);
    }
    return;
}

void horse_jumping_on_chessboard()
{
    int sum = 0;
    //Point_s* point_arr = nullptr;
    Step_s path[100]; // 100 只是个估计值
    Step_s dstep[4] = { {1,2},{2,1},{2,-1},{1,-2} };
    // TODO new失败情况处理
    // 题目所限制区域内，共有点9*5=45个
    //point_arr = new Point_s[45];
    //memset(point_arr, 0xFF, sizeof(Point_s)*45);

    horse_jumping(path, dstep, 0, 0, 0, sum);
    cout << "total: " << sum << endl;

    //delete[] point_arr;

    return;
}
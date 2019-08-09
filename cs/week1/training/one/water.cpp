/* 题目：
*     分水问题
*  描述：
*     有A、B和C三个杯子，容量依次为80ml、50ml和30ml。
*  现在A杯中装满了80ml的水，B和C都是空杯。A中的水可以倒入B杯或C杯中，
*  反之，B和C也可以往A中倒，还可以互相倒来倒去。为了计量，对于某一个杯子而言，
*  不是被倒满，就是被倒空。也就是说，要么倒水的杯子空了，要么被倒水的杯子满了，
*  这次倒水操作才会停止。请你编一个程序，将原来的80ml的酒分别倒入A和B两个杯子中，
*  各有40ml。输出每一步的操作。
*  输入格式：
*     没有输入
*  输出格式：
*     第一行输出一个整数n，表示步骤的数量。
*     之后有n行，每行表示一个操作，包含两个字母 x 和 y，表示将 x 杯的酒，倒入y中。
*     输出任意可行方案即可。
*  样例输入：
*     无
*  样例输出：
*     4
*     A B
*     A C
*     B A
*     C B
*  注释：
*     时间限制，1 s
*     空间限制，512 MB
*     样例输出仅用于解释输出格式，非答案。
*  在此样例输出描述的方案为：
*     一共有4步
*     最初状态：（A:80, B:0, C:0）
*     A 倒入 B。（A:30, B:50, C:0)
*     A 倒入 C。（A:0, B:50, C:30)
*     B 倒入 A。（A:50, B:0, C:30)
*     C 倒入 B。（A:50, B:30, C:0)
*     最终，A中有50ml，B中有30ml，C中有0ml，不符合题目要求，故非正确答案。
*  思路：
*     将A、B、C三个杯子抽象到三维直角坐标系中，(A,B,C)即(x,y,z)
*     A、B、C各自的范围确定了一个三维六面体空间，边界为(80,50,30)
*     A开始有80ml酒，即在坐标系中，初始点坐标为(80,0,0)
*     分酒结果为A分40ml，B分40ml，即结束点坐标为(40,40,0)
*     整个问题抽象为从(80,0,0)走到(40,40,0)的步骤
*     avail_capacity = min(max_capacity(x or y or z) - cur_capacity(x or y or z), poured_capacity)
*     poured_capacity = poured_capacity - avail_capacity
*     下次倒水，有三种选择，A->BC or B->AC or C->AB
*     将当前步骤数和“从哪个杯子倒水”统一起来
*     每一步只能从一个杯子向另一个杯子倒水，不能同时向两个杯子倒水
*  安全准则：
*     x+y+z = 80
*     0<=x<=80,0<=y<=50,0<=z<=30
*     倒水即“减”，倒水时必须保证有水
*     每一步操作之后的结果，都不能与之前任何一步的操作结果相同，即(x,y,z)的值相同
*
*/

#include <iostream>

using namespace std;

#define MAX_STEPS 50

enum Glass
{
    GA = 0,
    GB,
    GC,

    GLASS_MAX
};

typedef struct State
{
    char glass[GLASS_MAX];
}State_s;

typedef struct Step
{
    char from;
    char to;
}Step_s;

static char g_max_capacity[GLASS_MAX] = { 80, 50, 30 };
static char g_glass_name[GLASS_MAX] = { 'A', 'B', 'C' };
static Step_s g_steps[MAX_STEPS]; // 第0个元素没用

// 查重。因为等分水时，任何一次分水的结果肯定都是10的倍数，所以这里直接将范围缩小10倍
// 注意0<=x<=80,0<=y<=50,0<=z<=30应该对应的下标
static char repeat[8+1][5+1][3+1] = { {{0}} };

void std_out(char step)
{
    char i;

    cout << (int)step << endl;
    for (i = 1; i <= step; i++) {
        cout << g_glass_name[g_steps[i].from] << " " << g_glass_name[g_steps[i].to];
        if (i < step) {
            cout << endl;
        }
    }

    return;
}

void my_out(int& sum, char step)
{
    char i;

    cout << "第" << sum << "种方案： " << endl;
    for (i = 1; i <= step; i++) {
        cout << g_glass_name[g_steps[i].from] << " " << g_glass_name[g_steps[i].to] << endl;
    }

    return;
}

bool update_state(char src, char dst, State_s prev_state, State_s& cur_state)
{
    char i;
    char src_cap, dst_cap, dst_max_cap;

    src_cap = prev_state.glass[src];
    dst_cap = prev_state.glass[dst];
    dst_max_cap = g_max_capacity[dst];

    // 没水可以倒出来
    if (src_cap <= 0) {
        return false;
    }

    // 目标容器已满
    if (dst_cap == dst_max_cap) {
        return false;
    }

    for (i = 0; i < GLASS_MAX; i++) {
        if (i != src && i != dst) {
            cur_state.glass[i] = prev_state.glass[i];
            break;
        }
    }
    if (src_cap <= dst_max_cap - dst_cap) {
        cur_state.glass[src] = 0;
        cur_state.glass[dst] = dst_cap + src_cap;
    }
    else {
        cur_state.glass[src] = src_cap - (dst_max_cap - dst_cap);
        cur_state.glass[dst] = dst_max_cap;
    }

    // 查重
    if (1 == repeat[cur_state.glass[0]/10][cur_state.glass[1]/10][cur_state.glass[2]/10]) {
        return false;
    }

    return true;
}

// 每一step，包含“从哪个杯子分水”和“分到了哪个杯子”，并且只允许向一个杯子分水
// 入参携带了上一个状态，当前step要基于上一个step的state去做操作
void pouring_water(int& sum, char step, State_s prev_state)
{
    char i, j;
    State_s cur_state;

    if (step < 0 || step >= MAX_STEPS) {
        cout << "Fatal error: out of range. Step: " << step << endl;
        return;
    }

    // 递归基（与过河问题类似，真正的最后一步是进入递归基的前一步）
    if (40 == prev_state.glass[GA] &&
        40 == prev_state.glass[GB] &&
        0 == prev_state.glass[GC]) {
        sum++;

        std_out(step-1);
        //my_out(sum, step-1);
        return;
    }

    // 遍历三个杯子，从每个杯子中分水，from i to j
    for (i = 0; i < GLASS_MAX; i++) {
        for (j = 0; j < GLASS_MAX; j++) {
            if (i == j) {
                continue;
            }
            if (update_state(i, j, prev_state, cur_state)) {
                g_steps[step].from = i;
                g_steps[step].to = j;
                repeat[cur_state.glass[0] / 10][cur_state.glass[1] / 10][cur_state.glass[2] / 10] = 1;
                pouring_water(sum, step+1, cur_state);
                repeat[cur_state.glass[0] / 10][cur_state.glass[1] / 10][cur_state.glass[2] / 10] = 0;
                
                // 符合OJ要求，如果要看自己的输出，注释掉这个判断
                if (1 == sum) {
                    return;
                }
            }
        }
    }
}

void separating_water()
{
    int sum;
    char i, step;
    State_s cur_state;

    for (i = 0; i < MAX_STEPS; i++) {
        g_steps[i].from = -1;
        g_steps[i].to = -1;
    }

    sum = 0;
    cur_state.glass[GA] = 80;
    cur_state.glass[GB] = 0;
    cur_state.glass[GC] = 0;
    repeat[8][0][0] = 1;

    // step 从1开始
    pouring_water(sum, 1, cur_state);

    return;
}
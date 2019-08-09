/* 题目：
*  人鬼渡河问题
*  目标：
*     将东岸的3人3鬼用一只小船安全转移到西岸，希望摆渡次数尽可能少。
*  条件：
*     船的容量有限，一次最多只能坐2人（或2鬼或1人1鬼）
*     无论在东岸还是西岸，一旦鬼数多于人数，则人将被鬼吃掉
*     怎样渡河的大权掌握在人的手中
*  注意：
*     空船是无法移动的，要么人驾船，要么鬼驾船
*  说明：
*     划船的时间忽略不计，船一靠岸则将船与岸视为一体，人和鬼即使还没有下船也视为已经上岸
*  任务：
*     编程求出渡河方案
*  思路：
*     关键是构建模型，将其转换成图论所需的坐标点模型，然后根据深度优先原则去递归的求解。
      要想东西两岸都的人鬼数安全，则东岸的人鬼数必须是下面坐标轴中显示出来的点
      (monster of east) 
         3.__|__|__.
         2.__|__.__.
         1.__.__|__.
         0.__|__|__.
          0  1  2  3  (human of east)
*     东岸的人鬼数只有是以上坐标轴中的点(.)时，才能保证东西两岸同时不会有人被鬼吃掉
*     整个问题可以抽象为从坐标(3,3)走到坐标(0,0)的方法数，并且不能经过以下6个点(2,0)(2,1)(2,3)(1,0)(1,2)(1,3)
*     这6个点(2,0)(2,1)(2,3)(1,0)(1,2)(1,3)的状态要么表示东岸有人会被吃，要么表示西岸有人会被吃
*     只要东岸的人鬼数状态不经过这6个点，那一定可以保证东西两岸的人鬼数状态都正常
*     船每次可以运输人鬼的操作如下(x:human, y:ghost)：(2,0)(1,0)(1,1)(0,1)(0,2)
*     东--（操作）-->西：东边的人鬼数状态，通过上面五种操作中的某一个操作，到达另一个正确点（即，不是那6个点就行）
*     西--（操作）-->东：西边的人鬼数状态，通过上面五种操作中的某一个操作，到达另一个正确点（即，不是那6个点就行）
*     安全操作准则：
*         任何时刻，不允许经过那6个点
*         从东到西或从西到东后，执行完操作之后的人鬼数状态不能与前面任何一次同向操作之后的人鬼数状态相同
*     将东西岸抽象为数学模型：（站在东岸的角度来思考）
*         从东岸到西岸，即从东岸把人送走，即“减”人鬼数的过程
*         从西岸到东岸，即从西岸把人送来，即“加”人鬼数的过程
*         彻底抛开东西岸的概念，只思考“减”“加”轮流交替进行的情况
*     整个问题的数学模型：
*         初始状态为(3,3)，结束状态为(0,0)
*         操作动作只能五选一
*         加减轮流交替进行，首次为减
*         操作结果要符合安全准则
*     安全准则的数学模型：
*         0<=x<=3, 0<=y<=3 
*         操作结果不允许为以下6个点(2,0)(2,1)(2,3)(1,0)(1,2)(1,3)
*         本次“加”之后的结果不能与之前任何一次“加”之后的结果相同
*         本次“减”之后的结果不能与之前任何一次“减”之后的结果相同
*/

#include <iostream>

using namespace std;

typedef struct Point
{
    int x;
    int y;
}Point_s;

// 将操作与该操作导致的结果打包成一个步骤，这点才是梳理清整个算法的关键
// 记录在当前步骤所执行的操作（只记录操作的索引）以及该操作所产生的结果
typedef struct Step
{
    int opt_index;   // 记录“操作”索引
    Point_s state;   // 使用 ((-1) ^ (步骤奇偶)) * g_opt[opt_index] 操作后的结果
}Step_s;

#define STEPS_MAX 100  // 估计出来的，不可能达到这个数
#define OPT_MAX 5      // 五种操作步骤
#define ILLEGAL_POINTS_COUNT 6 // 非法点的个数

static Step_s *g_path = nullptr;
static Point_s g_opt[OPT_MAX] = { {2,0},{1,0},{1,1},{0,1},{0,2} };
static Point_s g_illegal_point[ILLEGAL_POINTS_COUNT] = { {2,0},{2,1},{2,3},{1,0},{1,2},{1,3} };

bool safe_opt(int step)
{
    int i, x, y;

    x = g_path[step].state.x;
    y = g_path[step].state.y;

    if (x < 0 || x > 3 || y < 0 || y > 3) {
        return false;
    }

    for (i = 0; i < ILLEGAL_POINTS_COUNT; i++) {
        if (x == g_illegal_point[i].x && y == g_illegal_point[i].y) {
            return false;
        }
    }

    // 从第二步开始才涉及是否与上一次的同向操作结果是否一致的问题
    if (1 < step) {
        // 优化：这里可以将每个方向走过的坐标位置记录到表里，查重的时候直接查表即可，就不用这样循环查找了
        for (i = step-2; i >= 0; i -= 2) {
            if (x == g_path[i].state.x && y == g_path[i].state.y) {
                return false;
            }
        }
    }

    return true;
}

/* step 从1开始，代表本层递归所对应的步骤，所以当本步骤的操作结果是(0,0)时，并不会进入递归基，而是会
*  进入下一层递归，因此递归基所判断的其实是上一步的状态是否为(0,0)
*/
void across_river(int& sum, int step)
{
    int i;
    int dir = -1;

    // 检查step是否越界
    if (step < 1 || step >= STEPS_MAX) {
        cout << "Fatal: out of range. step = " << step << endl;
        return;
    }

    // 递归基
    if (0 == g_path[step-1].state.x &&
        0 == g_path[step-1].state.y) {
        sum++;
        cout << "第" << sum << "种方法： (" << g_path[0].state.x << ", " << g_path[0].state.y << ")";

        // 进入递归基的step是实际最后一步step的下一步，所以循环条件是小于而不是小于等于
        for (i = 1; i < step; i++) {
            dir = (0 == i % 2) ? 1 : -1;
            // 输出“操作”动作
            cout << "<" << dir * g_opt[g_path[i].opt_index].x << ", " << dir * g_opt[g_path[i].opt_index].y << ">";
            // 输出操作结果
            cout << "(" << g_path[i].state.x << ", " << g_path[i].state.y << ")";
        }
        cout << endl;
        return;
    }

    // 对“操作”动作进行遍历
    dir = (0 == step % 2) ? 1: -1;
    for (i = 0; i < OPT_MAX; i++) {
        g_path[step].opt_index = i;
        g_path[step].state.x = g_path[step - 1].state.x + dir * g_opt[g_path[step].opt_index].x;
        g_path[step].state.y = g_path[step - 1].state.y + dir * g_opt[g_path[step].opt_index].y;
        if (safe_opt(step)) {
            across_river(sum, step+1);
        }
    }

    return;
}

void humans_monsters_across_river()
{
    int i, sum;

    // g_path[0]即初始状态，(3,3)
    g_path = new Step_s[STEPS_MAX];

    // 初始化成-1是为了当step为1时，不会从递归基直接退出递归
    for (i = 0; i < STEPS_MAX; i++) {
        g_path[i].opt_index = -1;
        g_path[i].state.x = -1;
        g_path[i].state.y = -1;
    }

    sum = 0;
    // (3,3)视为第0步产生的结果
    g_path[0].state.x = 3;
    g_path[0].state.y = 3;
    across_river(sum, 1);

    delete[] g_path;
    return;
}
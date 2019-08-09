/* 题目：
*      过河问题
*  描述：
*      农夫(Human)过河。一个农夫带着一只狼(Wolf)，一只羊(Sheep)和一些菜(Vegetable)过河。
*  河边只有一条船，由于船太小，只能装下农夫和他的一样东西。在无人看管的情况下，狼要吃羊，
*  羊要吃菜，请问农夫如何才能使三样东西平安过河?
*  输入格式：
*      没有输入
*  输出格式：
*      输出一行，为最终的过河方式，方案格式为：过河人员、回来人员、过河人员、回来人员、...、过河人员。
*      过去和回来的人员之间，用空格隔开。
*      以四个生物英文的首字母代指对应的生物(H->Human,W->Wolf,S->Sheep,V->Vegetable)
*      输出任意可行方案即可。
*  样例输入：
*      无
*  样例输出：
*      HS H HW H
*  注释：
*      时间限制，1 s
*      空间限制，512 MB
*      样例输出仅用于解释输出格式，非答案。
*  此样例输出描述的方案为：
*      人和羊过去，人回来，人和狼过去，人回来，此时对岸狼把羊吃了，不符合题目要求，故非正确答案。
*  我的思路：
*      设置“东西”两岸，初始状态在东岸，可用如下坐标表示状态(H,W,S,V)，1-->存在；0-->不存在
*      将(H,W,S,V)抽象为4bit二进制数，可表示的数据范围为[0,15]
*      其中某一岸不允许出现的状态为(0,1,1,1)(0,1,1,0)(0,0,1,1)
*      以上三个4bit二进制数的反码是(1,0,0,0)(1,0,0,1)(1,1,0,0)，反码就是同一时间对岸的状态
*      所以，就某一岸来讲，一共有6种不允许出现的状态，即(0,1,1,1)(0,1,1,0)(0,0,1,1)(1,0,0,0)(1,0,0,1)(1,1,0,0)
*      只要保证某一岸不出现以上6种状态，那么一定可以保证另一岸的状态也是安全的
*      渡河时，每次运送的动作为以下几种(1,1,0,0)(1,0,1,0)(1,0,0,1)(1,0,0,0)
*      既然只要某一岸不出现那6种情况，另一岸就是安全的，那么就可以直接将问题抽象为只考虑一岸
*      从某一岸送走东西，即“减”的过程；从某一岸运来东西，即“加”的过程
*      整个问题的数学模型（只站在起始状态那一岸去思考）：
*          状态范围[0,15]，初始状态为15，结束状态为0
*          考察的问题即，在安全条件下，从初始状态值15通过交替进行加减操作最终成为结束状态值0
*          第一次操作为“减”
*          状态方程，15-a+b-c+d-e...-n = 0，其中，a,b,c,d...n的可选值为(1,1,0,0)(1,0,1,0)(1,0,0,1)(1,0,0,0)
*          操作动作(1,1,0,0)==>12, (1,0,1,0)==>10, (1,0,0,1)==>9, (1,0,0,0)==>8
*          禁止状态(0,1,1,1)==>7, (0,1,1,0)==>6, (0,0,1,1)==>3, (1,0,0,0)==>8, (1,0,0,1)==>9, (1,1,0,0)==>12
*          安全状态模型：
*              操作结果（即完成一个操作之后的状态）范围[0,15]
*              每次的操作结果不能为以下6个值：7,6,3,8,9,12
*              本次“加”之后的结果不能与之前任何一次“加”之后的结果相同
*              本次“减”之后的结果不能与之前任何一次“减”之后的结果相同
*              执行“加”动作时（即上一个状态+当前操作），两个参与计算的4bit二进制数的每一bit都不能同时为1（
同时为1表示对应位的东西已经存在并且当前操作又会增加一个该东西，比如已经有狼了，结果操作的动作是又加了一只狼
，而本题中，人狼羊菜都是唯一的）
*              执行“减”动作时（即上一个状态-当前操作），当作为减数的那一bit为1时，作为被减数的那一bit也必须
为1（对于某一位来讲，只能有如下情况，1-1或1-0或0-0，而不能是0-1，在本题中代表的含义就是某一种东西存在的情况下，
送走这个东西，比如1-1表示有狼的时候，送走狼，0-1表示没狼的时候送走狼，这是没意义的，1-0表示有狼但是不送走）。
*/

#include <iostream>

using namespace std;

#define STEP_MAX       100 // 估计值
#define INIT_STATE_VAL 15
#define END_STATE_VAL  0

typedef struct Step
{
    char opt_index; // 记录操作动作的索引
    char state_val; // 记录操作动作的结果
}Step_s;

// 索引对应(H,W,S,V)中的bit
static char g_illegal_val[6] = { 3,6,7,8,9,12 };
// 索引是合法值
static const char* g_legal_val_name[INIT_STATE_VAL+1] = {"END", "V", "S", "SV", "W",
                                                       "WV", "WS", "WSV", "H", "HV",
                                                       "HS", "HSV", "HW", "HWV", "HWS", "HWSV"};
static char g_opt[4] = { 8,9,10,12 };
static const char* g_opt_name[4] = {"H","HV","HS","HW"}; // 与g_opt的下标完全对应，用于输出
static Step_s* g_path = nullptr;

void std_out(int step)
{
    char i;

    // 按题目示例要求，只输出操作动作，直接从第1步的操作值开始输出，到最后一步的操作值
    for (i = 1; i <= step; i++) {
        cout << g_opt_name[g_path[i].opt_index];
        if (i < step) {
            cout << " ";
        }
    }
    //cout << endl;

    return;
}

void my_out(int sum, int step)
{
    char i, dir;

    cout << "第" << sum << "种方案： ";
    cout << g_legal_val_name[g_path[0].state_val] << " ";
    for (i = 1; i <= step; i++) {
        dir = (0 == i % 2) ? 1 : -1;
        (1 == dir) ? (cout << "+") : (cout << "-");
        cout << g_opt_name[g_path[i].opt_index] << " ";
        cout << g_legal_val_name[g_path[i].state_val] << " ";
    }
    cout << endl;

    return;
}

bool safe_opt(int step)
{
    char tmp, tmp_prev, tmp_opt;
    char i, dir, cur_opt, cur_state_val, prev_state_val;

    dir = (0 == step % 2) ? 1 : -1;
    prev_state_val = g_path[step - 1].state_val;
    cur_opt = g_opt[g_path[step].opt_index];

    // 要保证cur_opt的低四位和prev_state_val的低四位，对应的每一位都不能同时为1
    if ((1 == dir) && 
        (0 != (prev_state_val & cur_opt))) {
        return false;
    }
    if (-1 == dir) {
        // cur_state_val = prev_state_val - cur_opt，不可能为负
        if (prev_state_val < cur_opt) {
            return false;
        }
        // 保证每一位做差时，都不会出现0-1的情况
        tmp = 1;
        for (i = 0; i < 4; i++) {
            tmp_prev = prev_state_val & tmp;
            tmp_opt = cur_opt & tmp;
            if (tmp_prev < tmp_opt) {
                return false;
            }

            tmp <<= 1;
        }
    }

    cur_state_val = g_path[step].state_val;
    if (cur_state_val < 0 || cur_state_val > INIT_STATE_VAL) {
        return false;
    }

    for (i = 0; i < 6; i++) {
        if (cur_state_val == g_illegal_val[i]) {
            return false;
        }
    }

    // 检查重复，注意，i>=0是为了检查是否会与初始状态的值相同
    for (i = step-2; i >= 0; i -= 2) {
        if (cur_state_val == g_path[i].state_val) {
            return false;
        }
    }

    return true;
}

void across_river(int& sum, int step)
{
    char i, dir;

    // 真正的步骤至少从1开始，第0步表示初始状态且没有操作动作，第1步才有操作动作以及操作结果
    if (step < 1 || step >= STEP_MAX) {
        cout << "Fatal error: out of range. The step is " << step << endl;
        return;
    }

    // 递归基（与人鬼渡河问题类似，该判断语句的step是真正最后一步的下一步）
    if (0 == g_path[step-1].state_val) {
        sum++;

        std_out(step-1);
        //my_out(sum, step-1);

        return;
    }

    // 遍历操作动作
    dir = (0 == step % 2) ? 1 : -1;
    for (i = 0; i < 4; i++) {
        g_path[step].opt_index = i;
        g_path[step].state_val = g_path[step - 1].state_val + dir * g_opt[g_path[step].opt_index];
        if (safe_opt(step)) {
            across_river(sum, step+1);
        }
        
        // 为提交OJ，如果求全部方案，将这个判断去掉即可
        if (1 == sum) {
            return;
        }
    }

    return;
}

void animals_across_river()
{
    int i, sum;

    g_path = new Step_s[STEP_MAX];
    for (i = 0; i < STEP_MAX; i++) {
        g_path[i].opt_index = -1;
        g_path[i].state_val = -1;
    }

    sum = 0;
    g_path[0].state_val = INIT_STATE_VAL;
    across_river(sum, 1);

    delete[] g_path;
    return;
}